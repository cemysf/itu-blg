#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("cem");

int major=0, minor=0;
dev_t device_no=0;

int initModule(void)
{
	device_no=MKDEV(major, minor);

	//register_chrdev_region(device_no, 1, "range");		//
	alloc_chrdev_region(&device_no, minor, 1, "range");
	major=MAJOR(device_no);

	printk(KERN_ALERT "blg413 prj3 - init module\n"); 
	printk(KERN_ALERT "blg413 prj3 - my major:%d minor: %d\n", major, minor);
	
	return 0;
}

void exitModule(void)
{
	unregister_chrdev_region(device_no, 1);
	printk(KERN_ALERT "blg413 prj3 - exit module\n"); 
}

module_init(initModule);
module_exit(exitModule);

