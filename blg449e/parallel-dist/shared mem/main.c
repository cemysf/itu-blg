#include <stdio.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <errno.h>
#include <string.h>
#include <signal.h>

#define SHMEM_SIZE 10
key_t key;      //key for shared memory, assigned in main
static volatile int loop_bool = 1;

// Interrupt handler for main loop
void loop_intHandler()
{
    loop_bool = 0;
}

int main()
{
    int shmid;
    key = ftok(".", 'a');

    // Create a shared memory segment
    shmid = shmget(key, SHMEM_SIZE, IPC_CREAT|IPC_EXCL|0666);
    if(shmid == -1)
    {
        printf("ERROR:'%s' while creating new segment\n", strerror(errno));
        return -1;
    }
    printf("Shared mem segment created (key=%ld, shmid=%d)\n", key, shmid);

    printf("Ctrl-c to mark shared memory as deleted \n", key, shmid);
    while(loop_bool)
        signal(SIGINT, loop_intHandler);

    // Mark shared memory segment to delete
    if(shmctl(shmid, IPC_RMID, NULL) == -1)
    {
        printf("ERROR:'%s' while marking segment as deleted\n", strerror(errno));
        return -1;
    }
    printf("Shared mem segment marked as deleted (key=%ld, shmid=%d)\n", key, shmid);




    return 0;
}
