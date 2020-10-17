#include <fcntl.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <string.h>
#include "range_ioctl.h"

void print_menu()
{
	system("clear");
	printf("1 : Get step size\n");
	printf("2 : Set step size\n");
	printf("3 : Get counter\n");
	printf("4 : Set counter\n");
	printf("5 : Set rotate mode\n");
	printf("6 : Set eof mode\n");
	printf("7 : Get starting value of device 1\n");
	printf("8 : Set starting value of device 1\n");
	printf("9 : Get starting value of device 2\n");
	printf("10: Set starting value of device 2\n");
	printf("11: Get ending value of device 1\n");
	printf("12: Set ending value of device 1\n");
	printf("13: Get ending value of device 2\n");
	printf("14: Set ending value of device 2\n");
	printf("0 : Exit\n");
	printf("Select one: ");
}

int main()
{
    int fd, arg, retval, select, value, loop;
    char path[] = "/dev/range0";

    fd = open(path, O_RDONLY);
    if(fd < 0)
    {
    	printf("Error: cannot open %s\n", path);
    	return -1;
    }

    loop = 1;

    while(loop)
    {
		print_menu();
    	scanf("%d", &select);

	    switch(select)
	    {
	    	case 0:
	    		loop = 0;
	    		break;

		 	case 1:
			    retval = ioctl(fd, RANGE_GET_STEP_SIZE, &arg);
			    if(retval)
			    	printf("Error :%s\n", strerror(errno));
			    else
			    	printf("RANGE_GET_STEP_SIZE: %d\n", arg);
			    getchar();
			break;

		 	case 2:
		 		printf("Value: ");
		 		scanf("%d", &value);
			    retval = ioctl(fd, RANGE_SET_STEP_SIZE, &value);
			    if(retval)
			    	printf("Error :%s\n", strerror(errno));
			    else
			    	printf("RANGE_SET_STEP_SIZE: %d\n", value);
			    getchar();
			break;

			case 3:
		    	retval = ioctl(fd, RANGE_GET_COUNTER, &arg);
		    	if(retval)
		    		printf("Error :%s\n", strerror(errno));
		    	else
			    	printf("RANGE_GET_COUNTER: %d\n", arg);
			    getchar();
			break;

		 	case 4:
		 		printf("Value: ");
		 		scanf("%d", &value);
			    retval = ioctl(fd, RANGE_SET_COUNTER, &value);
			    if(retval)
			    	printf("Error :%s\n", strerror(errno));
			    else
			    	printf("RANGE_SET_COUNTER: %d\n", value);
			    getchar();
			break;

			case 5:
		 		printf("Value: ");
		 		scanf("%d", &value);
			    retval = ioctl(fd, RANGE_SET_ROTATE_MODE, &value);
			    if(retval)
			    	printf("Error :%s\n", strerror(errno));
			    else
			    	printf("RANGE_SET_ROTATE_MODE: %d\n", value);
			    getchar();
			break;

			case 6:
		 		printf("Value: ");
		 		scanf("%d", &value);
			    retval = ioctl(fd, RANGE_SET_EOF_MODE, &value);
			    if(retval)
			    	printf("Error :%s\n", strerror(errno));
			    else
			    	printf("RANGE_SET_EOF_MODE: %d\n", value);
			    getchar();
			break;
			
			case 7:
		    	retval = ioctl(fd, RANGE_GET_START_1, &arg);
		    	if(retval)
		    		printf("Error :%s\n", strerror(errno));
		    	else
			    	printf("RANGE_GET_START_1: %d\n", arg);
			    getchar();
			break;

			case 8:
		 		printf("Value: ");
		 		scanf("%d", &value);
			    retval = ioctl(fd, RANGE_SET_START_1, &value);
			    if(retval)
			    	printf("Error :%s\n", strerror(errno));
			    else
			    	printf("RANGE_SET_START_1: %d\n", value);
			    getchar();
			break;

			case 9:
		    	retval = ioctl(fd, RANGE_GET_START_2, &arg);
		    	if(retval)
		    		printf("Error :%s\n", strerror(errno));
		    	else
			    	printf("RANGE_GET_START_2: %d\n", arg);
			    getchar();
			break;

			case 10:
		 		printf("Value: ");
		 		scanf("%d", &value);
			    retval = ioctl(fd, RANGE_SET_START_2, &value);
			    if(retval)
			    	printf("Error :%s\n", strerror(errno));
			    else
			    	printf("RANGE_SET_START_2: %d\n", value);
			    getchar();
			break;

			case 11:
		    	retval = ioctl(fd, RANGE_GET_END_1, &arg);
		    	if(retval)
		    		printf("Error :%s\n", strerror(errno));
		    	else
			    	printf("RANGE_GET_END_1: %d\n", arg);
			    getchar();
			break;

			case 12:
		 		printf("Value: ");
		 		scanf("%d", &value);
			    retval = ioctl(fd, RANGE_SET_END_1, &value);
			    if(retval)
			    	printf("Error :%s\n", strerror(errno));
			    else
			    	printf("RANGE_SET_END_1: %d\n", value);
			    getchar();
			break;

			case 13:
		    	retval = ioctl(fd, RANGE_GET_END_2, &arg);
		    	if(retval)
		    		printf("Error :%s\n", strerror(errno));
		    	else
			    	printf("RANGE_GET_END_2: %d\n", arg);
			    getchar();
			break;

			case 14:
		 		printf("Value: ");
		 		scanf("%d", &value);
			    retval = ioctl(fd, RANGE_SET_END_2, &value);
			    if(retval)
			    	printf("Error :%s\n", strerror(errno));
			    else
			    	printf("RANGE_SET_END_2: %d\n", value);
			    getchar();
			break;			

			default:
				printf("Invalid option\n");
				break;
		}
		getchar();

	}

    return 0;
}
