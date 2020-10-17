#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/init.h>

#include <linux/kernel.h>	
#include <linux/slab.h>		
#include <linux/fs.h>		
#include <linux/errno.h>	
#include <linux/types.h>	
#include <linux/proc_fs.h>
#include <linux/fcntl.h>	
#include <linux/seq_file.h>
#include <linux/cdev.h>

#include <asm/switch_to.h>	
#include <asm/uaccess.h>	

#include "range_ioctl.h"

#define RANGE_MAJOR 0
#define RANGE_NR_DEVS 2
#define RANGE_START 0
#define RANGE_END 10
#define RANGE_STEP 1
#define RANGE_COUNTER 0
#define RANGE_EOF_MODE 1
#define RANGE_ROTATE 0
#define RANGE_IS_EOF 0

int range_major = RANGE_MAJOR;
int range_minor = 0;
int range_nr_devs = RANGE_NR_DEVS;
int range_start_1 = RANGE_START;
int range_end_1 = RANGE_END;
int range_start_2 = RANGE_START;
int range_end_2 = RANGE_END;
int range_step_1 = RANGE_STEP;
int range_step_2 = RANGE_STEP;
int range_counter = RANGE_COUNTER;
int range_eof_mode = RANGE_EOF_MODE;
int range_rotate = RANGE_ROTATE;
int range_is_eof =  RANGE_IS_EOF;

module_param(range_major, int, S_IRUGO);
module_param(range_minor, int, S_IRUGO);
module_param(range_nr_devs, int, S_IRUGO);
module_param(range_start_1, int, S_IRUGO);
module_param(range_end_1, int, S_IRUGO);
module_param(range_start_2, int, S_IRUGO);
module_param(range_end_2, int, S_IRUGO);
module_param(range_step_1, int, S_IRUGO);
module_param(range_step_2, int, S_IRUGO);
module_param(range_counter, int, S_IRUGO);
module_param(range_eof_mode, int, S_IRUGO);
module_param(range_rotate, int, S_IRUGO);

MODULE_AUTHOR("Group-28");
MODULE_LICENSE("Dual BSD/GPL");

struct range_dev {
    struct semaphore sem;
    struct cdev cdev;
    int counter, step, start, end, rotate, eof_mode, Is_eof, device_no;
    int *seq_array;
};

struct range_dev *range_devices;

int next_number(int counter, int start, int end, int step){
	if(counter + step > end){
		if(counter == end) return start;
		return counter + step - end + start;
	}
	if(counter + step < start){
		if(counter == start) return end;
		return end + counter - step - start;
	}
	return counter+step;
}

int range_open(struct inode *inode, struct file *filp)
{
    struct range_dev *dev;
	dev = container_of(inode->i_cdev, struct range_dev, cdev);
	filp->private_data = dev;
	dev->Is_eof=range_is_eof;
	dev->rotate = range_rotate;
	dev->eof_mode = range_eof_mode;
	if(dev->device_no == 1){
		dev->start = range_start_1;
		dev->counter = range_counter;
		dev->step = range_step_1;
		dev->end = range_end_1;
	}
	else{
		dev->start = range_start_2;
		dev->counter = range_counter;
		dev->step = range_step_2;
		dev->end = range_end_2;
	}
    return 0;
}


int range_release(struct inode *inode, struct file *filp)
{
    return 0;
}


ssize_t range_read(struct file *filp, char __user *buf, size_t count,
                   loff_t *f_pos)
{
    struct range_dev *dev = filp->private_data;
    ssize_t retval = 0;
    int tmp, i;
	

    if (down_interruptible(&dev->sem))
        return -ERESTARTSYS;
	
	if(dev->eof_mode && dev->Is_eof){
		retval = 0;
		goto out;
	}
	
	if(dev->start > dev->end || dev->step > (dev->end-dev->start))return -EINVAL;
	
	if(dev->start > dev->counter || dev->end < dev->counter){
		if(!dev->rotate){
			dev->counter = dev->start;
			range_counter = dev->counter;
		}
		else{
			dev->counter = dev->end;
			range_counter = dev->counter;
		}
	}
	
	tmp = count/sizeof(int);
	
	if(!dev->rotate && dev->eof_mode){
		if((tmp-1)*dev->step+dev->counter > dev->end){ 
			tmp = (dev->end - dev->counter)/dev->step +1;
			dev->Is_eof = 1;
		}
		if((tmp-1)*dev->step+dev->counter < dev->start){
			tmp = (dev->counter - dev->start)/(-1*dev->step) + 1;
			dev->Is_eof = 1;
		}
	}

	if(dev->rotate && dev->eof_mode){
		if(-1*(tmp-1)*dev->step+dev->counter > dev->end){ 
			tmp = (dev->end - dev->counter)/dev->step +1;
			dev->Is_eof = 1;
		}
		if(-1*(tmp-1)*dev->step+dev->counter < dev->start){
			tmp = (dev->counter - dev->start)/(-1*dev->step) + 1;
			dev->Is_eof = 1;
		}
	}
	
	if(tmp == 1){
		dev->seq_array = kmalloc(sizeof(int), GFP_KERNEL);
		*(dev->seq_array) = dev->counter;
		if(!dev->rotate) dev->counter = next_number(dev->counter, dev->start, dev->end, dev->step);
		else dev->counter = next_number(dev->counter, dev->start, dev->end, -1*dev->step);
		if(dev->counter > dev->end || dev->counter < dev->start) dev->Is_eof = 1;
		retval = sizeof(int);
		goto sent;
	}
	
	if(!dev->rotate){
		dev->seq_array = kmalloc(tmp * sizeof(int), GFP_KERNEL);
		for(i=0;i<tmp;i++){
			dev->seq_array[i] = dev->counter;
			dev->counter = next_number(dev->counter, dev->start, dev->end, dev->step);
		}
	}
	else{
		dev->seq_array = kmalloc(tmp * sizeof(int), GFP_KERNEL);
		for(i=0;i<tmp;i++){
			dev->seq_array[i] = dev->counter;
			dev->counter = next_number(dev->counter, dev->start, dev->end, -1*dev->step);
		}		
	}
	retval = tmp*sizeof(int);
  
 sent:  
    if (copy_to_user(buf, dev->seq_array, retval)) {
        retval = -EFAULT;
        goto out;
    }
    
    kfree(dev->seq_array);

  out:
	range_is_eof = dev->Is_eof;
	range_counter = dev->counter;
    up(&dev->sem);
    return retval;
}


long range_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{

	int err = 0, tmp;
	int retval = 0;

	if (_IOC_TYPE(cmd) != RANGE_IOC_MAGIC) return -ENOTTY;
	if (_IOC_NR(cmd) > RANGE_IOC_MAXNR) return -ENOTTY;

	if (_IOC_DIR(cmd) & _IOC_READ)
		err = !access_ok(VERIFY_WRITE, (void __user *)arg, _IOC_SIZE(cmd));
	else if (_IOC_DIR(cmd) & _IOC_WRITE)
		err =  !access_ok(VERIFY_READ, (void __user *)arg, _IOC_SIZE(cmd));
	if (err) return -EFAULT;

	switch(cmd) {
	  case RANGE_GET_STEP_SIZE_1:

		retval = __put_user(range_step_1, (int __user *)arg);
		break;

	  case RANGE_SET_STEP_SIZE_1:
		if (! capable (CAP_SYS_ADMIN))
			return -EPERM;
		tmp = range_step_1;
		retval = __get_user(range_step_1, (int __user *)arg);
		if(!range_step_1){
			range_step_1 = tmp;
			return -EINVAL;
		}
		break;
		
	  case RANGE_GET_STEP_SIZE_2:

		retval = __put_user(range_step_2, (int __user *)arg);
		break;

	  case RANGE_SET_STEP_SIZE_2:
		if (! capable (CAP_SYS_ADMIN))
			return -EPERM;
		tmp = range_step_2;
		retval = __get_user(range_step_2, (int __user *)arg);
		if(!range_step_2){
			range_step_2 = tmp;
			return -EINVAL;
		}
		break;

	  case RANGE_GET_COUNTER:

		retval = __put_user(range_counter, (int __user *)arg);
		break;

	  case RANGE_SET_COUNTER:
		if (! capable (CAP_SYS_ADMIN))
			return -EPERM;
		
		range_is_eof = 0;
		retval = __get_user(range_counter, (int __user *)arg);
		break;

	  case RANGE_SET_ROTATE_MODE:
		if (! capable (CAP_SYS_ADMIN))
			return -EPERM;
			
		retval = __get_user(range_rotate, (int __user *)arg);	
		break;

	  case RANGE_SET_EOF_MODE:
		if (! capable (CAP_SYS_ADMIN))
			return -EPERM;
			
		retval = __get_user(range_eof_mode, (int __user *)arg);
		break;
			
	  case RANGE_GET_START_1:

		retval = __put_user(range_start_1, (int __user *)arg);
		break;

	  case RANGE_SET_START_1:
		if (! capable (CAP_SYS_ADMIN))
			return -EPERM;
			
		retval = __get_user(range_start_1, (int __user *)arg);
		break;
	  case RANGE_GET_START_2:

		retval = __put_user(range_start_2, (int __user *)arg);
		break;

	  case RANGE_SET_START_2:
		if (! capable (CAP_SYS_ADMIN))
			return -EPERM;
			
		retval = __get_user(range_start_2, (int __user *)arg);
		break;
	  case RANGE_GET_END_1:

		retval = __put_user(range_end_1, (int __user *)arg);
		break;

	  case RANGE_SET_END_1:
		if (! capable (CAP_SYS_ADMIN))
			return -EPERM;
			
		retval = __get_user(range_end_1, (int __user *)arg);
		break;
	  case RANGE_GET_END_2:

		retval = __put_user(range_end_2, (int __user *)arg);
		break;

	  case RANGE_SET_END_2:
		if (! capable (CAP_SYS_ADMIN))
			return -EPERM;
			
		retval = __get_user(range_end_2, (int __user *)arg);
		break;
		
	  default:
		return -ENOTTY;
	}
	return retval;
}

struct file_operations range_fops = {
    .owner =    THIS_MODULE,
    .read =     range_read,
    .open =     range_open,
    .release =  range_release,
    .unlocked_ioctl =  range_ioctl,
};


void range_cleanup_module(void)
{
    int i;
    dev_t devno = MKDEV(range_major, range_minor);

    if (range_devices) {
        for (i = 0; i < range_nr_devs; i++) {
            cdev_del(&range_devices[i].cdev);
        }
    kfree(range_devices);
    }

    unregister_chrdev_region(devno, range_nr_devs);
    printk(KERN_ALERT "blg413e prj3 - (INFO) exit module devno:%d, major:%d\n",devno, range_major);
}


int range_init_module(void)
{
    int result, i;
    int err;
    dev_t devno = 0;
    struct range_dev *dev;

    if (range_major) {
        devno = MKDEV(range_major, range_minor);
        result = register_chrdev_region(devno, range_nr_devs, "range");
    } else {
        result = alloc_chrdev_region(&devno, range_minor, range_nr_devs,
                                     "range");
        range_major = MAJOR(devno);
    }
    if (result < 0) {
        printk(KERN_WARNING "range: can't get major %d\n", range_major);
        return result;
    }

    printk(KERN_ALERT "blg413e prj3 - (INFO) initialized devno:%d, major:%d\n" ,devno, range_major);

    range_devices = kmalloc(range_nr_devs * sizeof(struct range_dev),
                            GFP_KERNEL);
    if (!range_devices) {
        result = -ENOMEM;
        goto fail;
    }
    memset(range_devices, 0, range_nr_devs * sizeof(struct range_dev));

    for (i = 0; i < range_nr_devs; i++) {
        dev = &range_devices[i];
        dev->device_no = i+1;
        dev->Is_eof=range_is_eof;
        if(dev->device_no == 1){
			dev->start = range_start_1;
			dev->end = range_end_1;
			dev->step = range_step_1;
		}
		else{	
			dev->start = range_start_2;
			dev->end = range_end_2;
			dev->step = range_step_2;
		}
        dev->counter = range_counter;
        dev->rotate = range_rotate;
        dev->eof_mode = range_eof_mode;
        sema_init(&dev->sem,1);
        devno = MKDEV(range_major, range_minor + i);
        cdev_init(&dev->cdev, &range_fops);
        dev->cdev.owner = THIS_MODULE;
        dev->cdev.ops = &range_fops;
        err = cdev_add(&dev->cdev, devno, 1);
        if (err)
            printk(KERN_NOTICE "Error %d adding range%d", err, i);
        else
        	printk(KERN_ALERT "blg413e prj3 - (INFO) cdev index:%d added\n", i);
    }

    return 0;

  fail:
    range_cleanup_module();
    return result;
}

module_init(range_init_module);
module_exit(range_cleanup_module);
