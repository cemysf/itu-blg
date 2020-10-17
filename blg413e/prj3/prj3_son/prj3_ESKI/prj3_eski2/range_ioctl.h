#ifndef __RANGE_H
#define __RANGE_H

#include <linux/ioctl.h>

#define RANGE_IOC_MAGIC  'k'
#define RANGE_GET_STEP_SIZE 	_IOR(RANGE_IOC_MAGIC,  0, int)
#define RANGE_SET_STEP_SIZE		_IOW(RANGE_IOC_MAGIC,  1, int)
#define RANGE_GET_COUNTER		_IOR(RANGE_IOC_MAGIC,  2, int)
#define RANGE_SET_COUNTER		_IOW(RANGE_IOC_MAGIC,  3, int)
#define RANGE_SET_ROTATE_MODE	_IOW(RANGE_IOC_MAGIC,  4, int)
#define RANGE_SET_EOF_MODE		_IOW(RANGE_IOC_MAGIC,  5, int)
#define RANGE_IOC_MAXNR 5

#endif
