#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#define NR_set_casper 355

int main(int argc, char **argv)
{
	int val = atoi(argv[1]), pid=getpid();
	
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
	
	while(1){};
	

	return 0;
}
