#include <stdio.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>

///  Data definitions  ///
#define SHMEM_SIZE 10
#define DELAY 1             // Delay for reading/writing operations

key_t key;                  // Key of shared memory, assigned in main
int shmid;                  // Shared memory id
char *shm_pointer, *shm_traverse;

static volatile int loop_bool = 1;  // Loop control for reading/writing operations


///  Functions  ///
// Interrupt handler for main loop
void loop_intHandler()
{
    loop_bool = 0;
}

int main()
{
    key = ftok(".", 'a');       // Key generation depends on current location in filesystem

    // Access segment
    shmid = shmget(key, SHMEM_SIZE, 0666);
    if(shmid == -1)
    {
        printf("ERROR:'%s' while odd writer accesing segment\n", strerror(errno));
        return -1;
    }
    printf(" Odd writer accessed segment (key=%ld, shmid=%d)\n", key, shmid);


    // Attach segment
    shm_pointer = shmat(shmid, NULL, 0);
    if(shm_pointer == (char*) -1)
    {
        printf("ERROR:'%s' while odd writer attaching segment\n",strerror(errno));
        return -1;
    }
    printf(" Odd writer attached segment, pointer is %p\n\n", shm_pointer);


    // Write values in loop
    printf("Ctrl-c to exit\n");
    shm_traverse = shm_pointer;
    int i=1;                                    // Starting from 1 for odd indexes
    while(loop_bool)
    {
        signal(SIGINT, loop_intHandler);        // controlling loop with interrupt

        shm_traverse = shm_pointer + (i % SHMEM_SIZE);
        *shm_traverse = (i%77) + '0';           // writing a character to memory cell

        printf("(Odd writer) write '%c' in index %d\n", *shm_traverse, i%SHMEM_SIZE);

        sleep(DELAY);                           // Loop delay

        i += 2;
    }


    // Detach segment
    if(shmdt(shm_pointer) == -1)
    {
        printf("ERROR:'%s' while odd writer detaching segment\n",strerror(errno));
        return -1;
    }
    printf("\n odd writer detached segment\n");


    return 0;
}
