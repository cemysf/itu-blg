#include <linux/syscalls.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <asm/errno.h>

asmlinkage long set_casper(pid_t pid, int value)
{
	if(value != 0 && value != 1 && value != 2 && value != 3)
	{
		return -EINVAL;
	}

	struct task_struct *p;
	read_lock(&tasklist_lock);
	p=find_task_by_vpid(pid);
	if(p == NULL)
	{
		read_unlock(&tasklist_lock);
		return -ESRCH;
	}
	read_unlock(&tasklist_lock);
	write_lock_irq(&tasklist_lock);
	p->casper = value;
	write_unlock_irq(&tasklist_lock);

	return 0;
}