//  BLG312E Operating Systems
//  HW 2
//  Cem Yusuf Aydoğdu
//  150120251
//
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <signal.h>

#define MUTEXKEY 12
#define COUNTKEY 13
int mutex_sem, count_sem;
FILE *fp_input, *fp_output;

///*  starting data structure  */
    typedef struct queue_node Node;
    struct queue_node       //patient
    {
        int data, patient_number;
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

    void enqueue(Queue *q, int val, int number)
    {
        Node *newnode = (Node *)malloc(sizeof(Node));
        newnode->data = val;
        newnode->patient_number = number;
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

    void dequeue(Queue *q, int *data, int *number)
    {
        *data = q->front->data;
        *number = q->front->patient_number;
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

void * nurse_function(void *ptr)
{
    int var,count=1;

    while(fscanf((FILE *)ptr,"%d\n",&var) == 1 )
    {
        printf("Nurse: Patient %d registered \n",count);
        fprintf(fp_output,"Nurse: Patient %d registered \n",count);
        enqueue(&waitingRoom,var,count++);
        sem_signal(count_sem,1);    //synch sem (nurse should do first)
        sleep(2);
    }

    pthread_exit(NULL);
}

void * doctor_function(void *ptr)
{
    sem_wait(count_sem,1);
    int var=0,numb=0;
    while(!isEmpty(&waitingRoom))
    {
         sem_wait(mutex_sem,1);
            dequeue(&waitingRoom,&var,&numb);

        sem_signal(mutex_sem,1);
        sleep(var);
        printf("\tDoctor %c: Patient %d treated (t=%d)\n",(char *)ptr, numb, var);
        fprintf(fp_output,"\tDoctor %c: Patient %d treated (t=%d)\n",(char *)ptr, numb, var);
    }
    pthread_exit(NULL);
}


int main(int argc, char *argv[])
{
    if(argc != 3)
    {
        printf("Enter filenames as command line argument");
        exit(-1);
    }

    pthread_t nurse, doctor1, doctor2;
    initList(&waitingRoom);
    fp_input = fopen(argv[1], "r");
    fp_output = fopen(argv[2],"w+");

    if( fp_input == NULL)
    {
        printf("Input file error. Program exits");
        exit(-1);
    }

    if( fp_output == NULL)
    {

        printf("Output file error. Program exits");
        exit(-1);
    }

    //create semaphore
    mutex_sem = semget(MUTEXKEY, 1, 0700|IPC_CREAT);     //key, number of sems., flag
    count_sem = semget(COUNTKEY, 1, 0700|IPC_CREAT);

    //set value of sem. to 1
    semctl(mutex_sem,0,SETVAL,1);   // mutex
    semctl(count_sem,0,SETVAL,0);


    if(pthread_create(&nurse, NULL, nurse_function,(FILE *)fp_input))     //pthread_t address, attributes, funct pointer, funct arguments
    {
        printf("nurse thread error");
        exit(-1);
    }

    if(pthread_create(&doctor1, NULL, doctor_function,(char *)'1'))
    {
        printf("doct1 error");
        exit(-1);
    }
    if(pthread_create(&doctor2, NULL, doctor_function,(char *)'2'))
    {
        printf("doct2 error");
        exit(-1);
    }

    // wait threads to end
    pthread_join(doctor1,NULL);
    pthread_join(doctor2,NULL);
    pthread_join(nurse,NULL);

    //sleep(200);
    semctl(mutex_sem,0,IPC_RMID,0);
    semctl(count_sem,0,IPC_RMID,0);
    fclose(fp_input);
    fclose(fp_output);

    exit(0);
}
