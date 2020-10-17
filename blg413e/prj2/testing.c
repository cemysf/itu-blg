#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#define NR_set_casper 355

int main(int argc, char **argv)
{
	if(argc!=3 || geteuid() != 0)
	{
		printf("usage: sudo ./executable pid value\n");
		return -1;
	}
	int pid = atoi(argv[1]), val=atoi(argv[2]);
	
	printf("casper value %d, pid %d\n",val, pid);

	long result = syscall(NR_set_casper, pid, val);

	printf("syscall result:%ld \n ",result);
	if(result == 0)
		printf("Success\n");
	else
	{
		printf("Error: ");
		if(errno== EINVAL)
			printf("Invalid value\n");
		if(errno==ESRCH)
			printf("Process not found\n");
	}

	return 0;
}
