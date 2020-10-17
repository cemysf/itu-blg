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
	printf("0 : Exit\n");
	printf("Select one: ");
}

int main()
{
    int fd, arg, retval, select, value, loop;
    char path[] = "/dev/range1";

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

			default:
				printf("Invalid option\n");
				break;
		}
		getchar();

	}

    return 0;
}
