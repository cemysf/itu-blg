///
/// BLG 449 Prog in Parallel&Dist. Sys. Prog
/// Hw - shared memory
/// Cem Yusuf Aydoğdu -15120251
/// 29/02/2016
/// 

///
/// Usage: Run main.c before running run writer_odd.c,
/// writer_even.c, reader_odd.c, reader_even.c files.
///

///! IMPORTANT NOTE: Because ninova only accepts 
///! a single c file, this file contains five files:
///! main.c
///! writer_odd.c
///! writer_even.c
///! reader_odd.c 
///! reader_even.c


///////////////////////////
/// BEGIN FILE:main.c /////
///////////////////////////


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


///////////////////////////
/// END FILE:main.c ///////
///////////////////////////


//////////////////////////////////
/// BEGIN FILE:writer_even.c /////
//////////////////////////////////
/*

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
        printf("ERROR:'%s' while even writer accesing segment\n", strerror(errno));
        return -1;
    }
    printf(" Even writer accessed segment (key=%ld, shmid=%d)\n", key, shmid);


    // Attach segment
    shm_pointer = shmat(shmid, NULL, 0);
    if(shm_pointer == (char*) -1)
    {
        printf("ERROR:'%s' while even writer attaching segment\n",strerror(errno));
        return -1;
    }
    printf(" Even writer attached segment, pointer is %p\n\n", shm_pointer);


    // Write values in loop
    printf("Ctrl-c to exit\n");
    shm_traverse = shm_pointer;
    int i=0;                                    // Starting from 0 for even indexes
    while(loop_bool)
    {
        signal(SIGINT, loop_intHandler);        // controlling loop with interrupt

        shm_traverse = shm_pointer + (i % SHMEM_SIZE);
        *shm_traverse = (i%77) + '0';           // writing a character to memory cell

        sleep(DELAY);                           // Loop delay

        printf("(Even writer) write '%c' in index %d\n", *shm_traverse, i%SHMEM_SIZE);

        i += 2;
    }


    // Detach segment
    if(shmdt(shm_pointer) == -1)
    {
        printf("ERROR:'%s' while even writer detaching segment\n",strerror(errno));
        return -1;
    }
    printf("\n Even writer detached segment\n");


    return 0;
}

*/
//////////////////////////////////
/// END FILE:writer_even.c ///////
//////////////////////////////////


//////////////////////////////////
/// BEGIN FILE:writer_odd.c //////
//////////////////////////////////
/*

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

*/
//////////////////////////////////
/// END FILE:writer_odd.c ////////
//////////////////////////////////


//////////////////////////////////
/// BEGIN FILE:reader_even.c /////
//////////////////////////////////
/*

#include <stdio.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>

///  Data definitions  ////
#define SHMEM_SIZE 10
#define DELAY 1             // Delay for reading/writing operations

key_t key;                  // Key of shared memory, assigned in main
int shmid;                  // Shared memory id
char *shm_pointer, *shm_traverse;

static volatile int loop_bool = 1;  // Loop control for reading/writing operations


///  Functions  ////
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
        printf("ERROR:'%s' while even reader accesing segment\n", strerror(errno));
        return -1;
    }
    printf(" Even reader accessed segment (key=%ld, shmid=%d)\n", key, shmid);


    // Attach segment
    shm_pointer = shmat(shmid, NULL, 0);
    if(shm_pointer == (char*) -1)
    {
        printf("ERROR:'%s' while even reader attaching segment\n",strerror(errno));
        return -1;
    }
    printf(" Even reader attached segment, pointer is %p\n\n", shm_pointer);


    // Write values in loop
    printf("Ctrl-c to exit\n");
    shm_traverse = shm_pointer;
    int i=0;                                    // Starting from 0 for even indexes
    while(loop_bool)
    {
        signal(SIGINT, loop_intHandler);        // controlling loop with interrupt

        shm_traverse = shm_pointer + (i % SHMEM_SIZE);
        printf("  (Even reader) read '%c' in index %d\n", *shm_traverse, i%SHMEM_SIZE);
        sleep(DELAY);                           // Loop delay

        i += 2;
    }


    // Detach segment
    if(shmdt(shm_pointer) == -1)
    {
        printf("ERROR:'%s' while even reader detaching segment\n",strerror(errno));
        return -1;
    }
    printf("\n Even reader detached segment\n");


    return 0;
}


*/
//////////////////////////////////
/// END FILE:reader_even.c ///////
//////////////////////////////////


//////////////////////////////////
/// BEGIN FILE:reader_odd.c //////
//////////////////////////////////
/*

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
        printf("ERROR:'%s' while odd reader accesing segment\n", strerror(errno));
        return -1;
    }
    printf(" Odd reader accessed segment (key=%ld, shmid=%d)\n", key, shmid);


    // Attach segment
    shm_pointer = shmat(shmid, NULL, 0);
    if(shm_pointer == (char*) -1)
    {
        printf("ERROR:'%s' while odd reader attaching segment\n",strerror(errno));
        return -1;
    }
    printf(" Odd reader attached segment, pointer is %p\n\n", shm_pointer);


    // Write values in loop
    printf("Ctrl-c to exit\n");
    shm_traverse = shm_pointer;
    int i=1;                                    // Starting from 1 for odd indexes
    while(loop_bool)
    {
        signal(SIGINT, loop_intHandler);        // controlling loop with interrupt

        shm_traverse = shm_pointer + (i % SHMEM_SIZE);
        printf("  (Odd reader) read '%c' in index %d\n", *shm_traverse, i%SHMEM_SIZE);
        sleep(DELAY);                           // Loop delay

        i += 2;
    }


    // Detach segment
    if(shmdt(shm_pointer) == -1)
    {
        printf("ERROR:'%s' while odd reader detaching segment\n",strerror(errno));
        return -1;
    }
    printf("\n odd reader detached segment\n");


    return 0;
}

*/
//////////////////////////////////
/// END FILE:reader_odd.c ////////
//////////////////////////////////

