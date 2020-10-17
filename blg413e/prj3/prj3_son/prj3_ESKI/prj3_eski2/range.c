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
#define RANGE_INDEX 0
#define RANGE_EOF_MODE 0
#define RANGE_ROTATE 0
#define RANGE_IS_EOF 0

int range_major = RANGE_MAJOR;
int range_minor = 0;
int range_nr_devs = RANGE_NR_DEVS;
int range_start = RANGE_START;
int range_end = RANGE_END;
int range_step = RANGE_STEP;
int range_counter = RANGE_COUNTER;
int range_index = RANGE_INDEX;
int range_eof_mode = RANGE_EOF_MODE;
int range_rotate = RANGE_ROTATE;
int range_is_eof =  RANGE_IS_EOF;

module_param(range_major, int, S_IRUGO);
module_param(range_minor, int, S_IRUGO);
module_param(range_nr_devs, int, S_IRUGO);
module_param(range_start, int, S_IRUGO);
module_param(range_end, int, S_IRUGO);
module_param(range_step, int, S_IRUGO);
module_param(range_counter, int, S_IRUGO);
module_param(range_index, int, S_IRUGO);
module_param(range_eof_mode, int, S_IRUGO);
module_param(range_rotate, int, S_IRUGO);

MODULE_AUTHOR("Group-28");
MODULE_LICENSE("Dual BSD/GPL");

struct range_dev {
    struct semaphore sem;
    struct cdev cdev;
    int counter, step, start, end, index, rotate, eof_mode, Is_eof;
};

struct range_dev *range_devices;

int range_open(struct inode *inode, struct file *filp)
{
    struct range_dev *dev;

    dev = container_of(inode->i_cdev, struct range_dev, cdev);
    filp->private_data = dev;
	dev->Is_eof=range_is_eof;
	dev->start = range_start;
	dev->step = range_step;
	dev->end = range_end;
	dev->counter = range_counter;
	dev->rotate = range_rotate;
	dev->eof_mode = range_eof_mode;
	dev->index = range_index;

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

    if (down_interruptible(&dev->sem))
        return -ERESTARTSYS;
	
	if(dev->eof_mode && dev->Is_eof) goto out;
	
    if (copy_to_user(buf, &dev->counter, sizeof(int))) {
        retval = -EFAULT;
        goto out;
    }
    if(!dev->rotate){
		if(dev->counter + dev->step > dev->end){
			if(dev->eof_mode){
				dev->Is_eof = 1;
			}
			else{
				if(!(dev->end-dev->start)%dev->step)dev->counter=dev->start;
				else dev->counter = dev->counter + dev->step - dev->end;
			}
		}
		else dev->counter = dev->counter + dev->step;
		dev->index++;
	}
	else{
		if(dev->counter - dev->step < dev->start){
			if(dev->eof_mode){
				dev->Is_eof = 1;
			}
			else{
				if(!(dev->end-dev->start)%dev->step)dev->counter=dev->end;
				else dev->counter = dev->end + dev->counter - dev->step;
			}
		}
		else dev->counter = dev->counter - dev->step;
		dev->index++;
	}
	retval = sizeof(int);
  out:
    up(&dev->sem);
    return retval;
}


long range_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{

	int err = 0;
	int retval = 0;

	if (_IOC_TYPE(cmd) != RANGE_IOC_MAGIC) return -ENOTTY;
	if (_IOC_NR(cmd) > RANGE_IOC_MAXNR) return -ENOTTY;

	if (_IOC_DIR(cmd) & _IOC_READ)
		err = !access_ok(VERIFY_WRITE, (void __user *)arg, _IOC_SIZE(cmd));
	else if (_IOC_DIR(cmd) & _IOC_WRITE)
		err =  !access_ok(VERIFY_READ, (void __user *)arg, _IOC_SIZE(cmd));
	if (err) return -EFAULT;

	switch(cmd) {
	  case RANGE_GET_STEP_SIZE:

		retval = __put_user(range_step, (int __user *)arg);
		break;

	  case RANGE_SET_STEP_SIZE	:
		if (! capable (CAP_SYS_ADMIN))
			return -EPERM;
			
		retval = __get_user(range_step, (int __user *)arg);
		break;

	  case RANGE_GET_COUNTER:

		retval = __put_user(range_counter, (int __user *)arg);
		break;

	  case RANGE_SET_COUNTER:
		if (! capable (CAP_SYS_ADMIN))
			return -EPERM;
			
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
        dev->Is_eof=range_is_eof;
        dev->start = range_start;
        dev->step = range_step;
        dev->end = range_end;
        dev->counter = range_counter;
        dev->rotate = range_rotate;
        dev->eof_mode = range_eof_mode;
        dev->index = range_index;
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