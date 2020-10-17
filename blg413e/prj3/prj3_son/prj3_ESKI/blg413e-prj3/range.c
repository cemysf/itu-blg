#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/kdev_t.h>
#include <linux/cdev.h>
#include <linux/slab.h>
#include <linux/errno.h>
#include <linux/uaccess.h>
#include <linux/kernel.h>

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("cem");

int major=0;
int minor=0;
int count=1;
dev_t device_no=0;
int return_val=0;	// return 0 if nothing goes wrong..


struct range_dev{
	struct cdev cdev;
	int step, start, end, counter, index;
	struct semaphore sem;
	char array[1000];
	/// TODO: diğer datalar..

};
struct range_dev *device_ptr;



int range_open(struct inode *inode, struct file *filp)
{
    struct range_dev *dev;

    dev = container_of(inode->i_cdev, struct range_dev, cdev);
    filp->private_data = dev;

    return 0;
}


int range_release(struct inode *inode, struct file *filp)
{
    return 0;
}

ssize_t range_read(struct file *filp, int __user *buf, size_t count)
{
    struct range_dev *dev = filp->private_data;
    ssize_t retval = 0;

    if (down_interruptible(&dev->sem))
        return -ERESTARTSYS;
    
    sprintf(dev->array+dev->index,"%d",dev->counter);

    if (copy_to_user(buf, dev->array, strlen(dev->array))) {
        retval = -EFAULT;
        goto out;
    }
    printk(KERN_ALERT "blg413e prj3 - (INFO) range_read, counter=%d array=%s\n", dev->counter, dev->array);
	if(dev->counter + dev->step > dev->end)
		dev->counter = dev->counter + dev->step - dev->end;
	else dev->counter = dev->counter + dev->step;
	dev->index++;
	
  out:
    up(&dev->sem);
    return retval;
}

/// ioctlFunct

struct file_operations fops = {
	.owner = THIS_MODULE,
	.open = range_open,
	.release = range_release,
	// TODO: fonksiyonlar yazılacak
	.read = range_read,
//	.ioctl = ioctlFunct,
};


static void rangeSetup(int index)
{
	int devno=MKDEV(major, minor+index);
	int err_no;

	cdev_init(&device_ptr->cdev, &fops);
	device_ptr->cdev.ops = &fops;
	device_ptr->cdev.owner = THIS_MODULE;
	sema_init(&device_ptr->sem,1);

	err_no = cdev_add(&device_ptr->cdev, devno, 1);
	if (err_no!=0)
		printk(KERN_ALERT "blg413e prj3 - (ERROR:%d) cannot add range no:%d\n",err_no, index);
	else
		printk(KERN_ALERT "blg413e prj3 - (INFO) cdev index:%d added\n", index);

}

int initModule(void)
{
	int i;					// loop iterator
	printk(KERN_ALERT "blg413e prj3 - (INFO) initializing module\n"); 

	// dynamically allocate device numbers
	// device_no: holds the first number in allocation (if allocation is successfull)
	// minor: requested first minor (usually 0)
	// count: total number of continious device numbers requested
	return_val= alloc_chrdev_region(&device_no, minor, count, "range");
	major=MAJOR(device_no);
	if (return_val!=0)
	{
		printk(KERN_ALERT "blg413e prj3 - (ERROR:%d) cannot initialize module\n",return_val);
		return return_val;
	}
	
	device_ptr = kmalloc(count * sizeof(struct range_dev), GFP_KERNEL);
	if (device_ptr==NULL)
	{
		return_val = -ENOMEM;
		printk(KERN_ALERT "blg413e prj3 - (ERROR:%d) cannot allocate memory\n",return_val);	
		return return_val;
	}

	
	for(i=0; i<count; i++)
	{
		rangeSetup(i);
	}
	device_ptr->start=0;
	device_ptr->end=4;
	device_ptr->step=2;
	device_ptr->counter=0;
	device_ptr->index = 0;

	printk(KERN_ALERT "blg413e prj3 - (INFO) initialized devno:%d, major:%d\n" ,device_no, major);	
	return return_val;
}

void exitModule(void)
{
	dev_t devno = MKDEV(major, minor);
	int i;
	
	if(device_ptr!=NULL)
	{
		for(i=0; i< count; i++)
			cdev_del(&device_ptr[i].cdev);
		kfree(device_ptr);
	}
	
	
	unregister_chrdev_region(devno, count);
	printk(KERN_ALERT "blg413e prj3 - (INFO) exit module devno:%d, major:%d\n",devno, major); 
}

module_init(initModule);
module_exit(exitModule);

