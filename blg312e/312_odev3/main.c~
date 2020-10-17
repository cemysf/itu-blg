//
//  BLG312E Operating Systems
//  HW 3
//  Cem Yusuf Aydoğdu
//  150120251
//
//  compiling: gcc main.c -pthread

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <signal.h>

#define PARENTKEY 11  //ftok(strcat(get_current_dir_name(),argv[0]),1)
#define MUTEXKEY 12 //ftok(strcat(get_current_dir_name(),argv[0]),2)
#define COUNTKEY 13 //ftok(strcat(get_current_dir_name(),argv[0]),3)
#define XRAYKEY 14 //ftok(strcat(get_current_dir_name(),argv[0]),4)

//  mutex_sem  : used for two doctors in a department
//  count_sem  : to synchronize nurses and doctors
//  parent_sem : to synchronize parent and child processes
//  xray_sem   : to mutex xray operations (max 3 xray can be done at the same time)

int mutex_sem, count_sem, parent_sem, xray_sem;
FILE *fp_input;
int index_child;         // to enumerate child processes

///*  starting data structure  */
    typedef struct queue_node Node;
    struct queue_node       //patient
    {
        int data, patient_number, xray;
        Node *next;
    };

    typedef struct queue_list       //waiting room
    {
        Node *front, *back;
    }Queue;

    void initList(Queue *q)
    {
        q->front = NULL;
        q->back = NULL;
    }

    void enqueue(Queue *q, int val, int number, int bool_xray)
    {
        Node *newnode = (Node *)malloc(sizeof(Node));
        newnode->data = val;
        newnode->patient_number = number;
        newnode->xray = bool_xray;
        newnode->next = NULL;
        if(q->front == NULL)
        {
            q->back = newnode;
            q->front = newnode;
        }
        else
        {
            q->back->next = newnode;
            q->back = newnode;
        }

    }

    void dequeue(Queue *q, int *data, int *number, int *xray_status)
    {
        *data = q->front->data;
        *number = q->front->patient_number;
        *xray_status = q->front->xray;
        Node *tempnode = q->front;

        q->front = q->front->next;
        free(tempnode);
    }

    int isEmpty(Queue *q)
    {
        if(q->front == NULL) return 1;
        else return 0;
    }

    Queue waitingRoom;
///*  ending data structure  */


///*  semaphore operations start */
    void sem_wait(int semid, int val)   //decrement
    {
        struct sembuf sem;
        sem.sem_num=0;
        sem.sem_op= -1*val;
        sem.sem_flg=1;
        semop(semid,&sem,1);
    }
    void sem_signal(int semid, int val) //increment
    {
        struct sembuf sem;
        sem.sem_num=0;
        sem.sem_op=val;     //val neg: allocate res., pos:release res.,
        sem.sem_flg=1;
        semop(semid, &sem, 1);
    }
///*  semaphore operations end */

void * nurse_function(void *ptr)
{
    int var,count=1, xray_stat;

    while(fscanf((FILE *)ptr,"%d %d\n",&var, &xray_stat) == 2 )
    {
        printf("Department %d Nurse: Patient %d is registered\n",index_child,count);
        enqueue(&waitingRoom,var,count++,xray_stat);
        sem_signal(count_sem,1);        //synch sem (nurse should do first)
        sleep(2);
    }

    pthread_exit(NULL);
}

void * doctor_function(void *ptr)
{
    sem_wait(count_sem,2);          // doctors should wait for 2 patients, it prevents doctors to exit after treating just one patient
    int var=0,numb=0, xray_stat=0;
    while(!isEmpty(&waitingRoom))
    {
        sem_wait(mutex_sem,1);
            dequeue(&waitingRoom,&var,&numb,&xray_stat);
        sem_signal(mutex_sem,1);
        sleep(var);

        if(xray_stat==1)
        {
            sem_wait(xray_sem,1);
                sleep(2);
            sem_signal(xray_sem,1);

            printf("Department %d  Doctor %c: Patient %d is treated (X-Ray taken)\n",index_child,(char *)ptr, numb);
        }
        else
        {
            printf("Department %d  Doctor %c: Patient %d is treated\n",index_child,(char *)ptr, numb);
        }
    }

    pthread_exit(NULL);
}


int main(int argc, char *argv[])
{
    if(argc != 6)
    {
        printf("Enter filenames as command line argument\n");
        exit(-1);
    }

    // parent_sem and xray_sem are common in all processes
    parent_sem = semget(PARENTKEY,1,0700|IPC_CREAT);    // before ending parent, wait child processes to end
    semctl(parent_sem,0,SETVAL,0);                      // semaphore is initially 0, for synch.

    xray_sem = semget(XRAYKEY,1,0700|IPC_CREAT);
    semctl(xray_sem,0,SETVAL,3);                        // initially 3, at most 3 xray in same time

    int f;
    for(index_child=1;index_child<=5;index_child++)
    {
        f=fork();
        if(f==0) break;
    }

    if(f==0)    // child processes (departments)
    {
        fp_input = fopen(argv[index_child],"r");

        if( fp_input == NULL)
        {
            printf("%d. input file error. Process exits.",index_child);
            sem_signal(parent_sem,1);
            exit(-1);
        }

        // semaphores for each child process
        mutex_sem = semget(MUTEXKEY, 1, 0700|IPC_CREAT);     // for doctors, not to two doctors remove from queue at the same time
        count_sem = semget(COUNTKEY, 1, 0700|IPC_CREAT);     // nurse should execute before doctors start to remove from queue

        semctl(mutex_sem,0,SETVAL,1);
        semctl(count_sem,0,SETVAL,0);

        pthread_t nurse, doctor1, doctor2;

        initList(&waitingRoom);


        if(pthread_create(&nurse, NULL, nurse_function,(FILE *)fp_input))     //pthread_t address, attributes, funct pointer, funct arguments
        {
            printf("Department %d nurse thread error",index_child);
            exit(-1);
        }
        if(pthread_create(&doctor1, NULL, doctor_function,(char *)'1'))
        {
            printf("Department %d doctor 1 error",index_child);
            exit(-1);
        }
        if(pthread_create(&doctor2, NULL, doctor_function,(char *)'2'))
        {
            printf("Department %d doctor2 error",index_child);
            exit(-1);
        }

        // wait threads to end
        pthread_join(doctor1,NULL);
        pthread_join(doctor2,NULL);
        pthread_join(nurse,NULL);

        fclose(fp_input);
        semctl(mutex_sem,0,IPC_RMID,0);
        semctl(count_sem,0,IPC_RMID,0);

        sem_signal(parent_sem,1);
        exit(0);
    }
    else        //parent process
    {
        sem_wait(parent_sem,5);     //parent waits all childs

        semctl(parent_sem,0,IPC_RMID,0);
        semctl(xray_sem,0,IPC_RMID,0);
        printf("main is ending..\n");
        exit(0);

    }
    return 0;
}
