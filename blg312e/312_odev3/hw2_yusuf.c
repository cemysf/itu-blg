
/*Yusuf Ekiz 150120040 *

I have sychronization problem in my code.*/


#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include<sys/ipc.h>
#include<sys/sem.h>
#include<sys/types.h>
#include <signal.h>
#include <pthread.h>
#define SEMKEY 8
#define SEMKEY2 9
#define SEMKEY3 10


typedef struct Node {
    int time;
    int x_ray;
    struct Node* next;
} Node;

typedef struct Queue {
    Node* head;
    Node* last;
    int size;
} Queue;


void push (Queue * ptr,int time,int x_ray);
void create (Queue * ptr);
Node pop  (Queue * ptr);
void sem_signal(int sem_id,int value);
void sem_wait(int sem_id,int value);
void * doctor_function(void * ptr);
void * nurse_function(void * ptr);


FILE * fptr[5];//Global pointers and queue.


int sem_doctor;
int sem_nurse;
int sem_xray;
Queue queue;


int main(int argc,char * argv[])
{
	
	int i,f;
	sem_xray=semget(SEMKEY,1,0700|IPC_CREAT);
	semctl(sem_xray,0,SETVAL,3);
	for(i=0;i<5;i++)
	{
		f=fork();
		if(f==0)break;
	}
	// forkdan sonra.
	
	if(f==0)
	{
	create(&queue);//creating queue.
	fptr[i]=fopen(argv[i+1],"r");
	sem_doctor=semget(SEMKEY2,1,0700|IPC_CREAT);
	sem_nurse=semget(SEMKEY3,1,0700|IPC_CREAT); //Creat value sem_nurse and sem_doctor
	semctl(sem_doctor,0,SETVAL,1);
	semctl(sem_nurse,0,SETVAL,0);//set values for sem_nurse and sem_doctor 
    pthread_t doctor1,doctor2,nurse;//defining threads.
    Node doctor_1_input;
	Node doctor_2_input;
    doctor_1_input.time=1;
    doctor_1_input.x_ray=i;
    doctor_2_input.time=2;
    doctor_2_input.x_ray=i;
	pthread_create(&nurse,NULL,nurse_function,(void *)&i);
	pthread_create(&doctor1,NULL,doctor_function,(void *)&doctor_1_input); //thread creating.
	pthread_create(&doctor2,NULL,doctor_function,(void *)&doctor_2_input);
	pthread_join(nurse,NULL);
	pthread_join(doctor1,NULL);
	pthread_join(doctor2,NULL);
	fclose(fptr[i]);
	semctl(sem_doctor,0,IPC_RMID,0);  //taking back values 
	semctl(sem_nurse,0,IPC_RMID,0);
	pthread_exit(NULL);
    return 0;
	}
	else 
	{
	 wait(NULL);
	 semctl(sem_xray,0,IPC_RMID,0);
	 return 0;
	}
	
	
    	 
}

void sem_signal(int sem_id,int value)
{
  struct sembuf temp;
  temp.sem_num=0;
  temp.sem_op=value;
  temp.sem_flg=1;
 semop(sem_id,&temp,1);
}// V(S)

void sem_wait(int sem_id,int value)
{
  struct sembuf temp;
  temp.sem_num=0;
  temp.sem_op=(-1 * value);
  temp.sem_flg=1;
  semop(sem_id,&temp,1);
}//P(S)  	

Node pop  (Queue * ptr)
{
	Node rtrn=*(ptr->head);
	Node* temp = ptr->head;
    ptr->head = ptr->head->next;  //Pop from queue.
    ptr->size=ptr->size - 1;
    free(temp);
    return rtrn;
}
       
void push (Queue * ptr,int x,int x_ray)
{
 Node * new_node =(Node*) malloc (sizeof(Node));
 new_node->time=x;
 new_node->x_ray=x_ray;
 new_node->next=NULL;
		
	if(ptr->head==NULL)
	{	
            	ptr->head=new_node;
				ptr->last=new_node;
				ptr->size=ptr->size +1;
				ptr->last->next=NULL;   //add to the queue.
	}
	
	else
	{
             	ptr->last->next=new_node;
				ptr->last=new_node;
				ptr->last->next=NULL;
				ptr->size=ptr->size +1 ;	
	}
return;
}

void create (Queue * ptr)
{
	ptr->head=NULL;  //creating queue.
	ptr->last=NULL;
}



void * doctor_function(void * ptr)
{
		sem_wait(sem_nurse,1);
		
		//waiting the nurse to register patient.
 		 int counter =0;
  		Node * temp=(Node*) ptr;
  		int id=temp->time;
  		int number=temp->x_ray;
  		
  		
  		while(queue.head!=NULL)
  		{
  		
		counter++;
  		sem_wait(sem_doctor,1);//Doctor communication.When a doctor is popping a value from queue,the other one should wait.
  		Node data=pop(&queue);
  		sem_signal(sem_doctor,1);
		//signaling to system to the other doctor can pop value.
  		sleep(data.time);//Process time.
  		if(data.x_ray==0)
  		{
			printf("Department %d Doctor %d :Patient%d is treated\n",number+1,id,counter);
		}
		else if(data.x_ray==1)   //X-Ray semaphore between processes.
		{
			sem_wait(sem_xray,1);
			sleep(2);
			printf("Departmend %d Doctor %d :Patient%d is treated(X-Ray taken)\n",number+1,id,counter);
			sem_signal(sem_xray,1);
		}
		
  		
  		}
  	
  		pthread_exit(NULL);
  		return;
  
  
  
}

void * nurse_function(void * ptr)
{
	
	int x=0;
	int y=0;
	int counter=0;
	int * p_id=(int *) ptr; 
	int z=* p_id;
	FILE * file_ptr=fptr[z];
	while(!feof(file_ptr))
	{
	 	 counter++;
	  	fscanf(file_ptr,"%d %d \n",&x,&y);
	     	push(&queue,x,y);
	     	sem_signal(sem_nurse,1);
	     	sleep(2);
		printf("Department %d  Nurse:Patient%d is registered\n", z+1,counter);
    	}
	pthread_exit(NULL);
	return;
}

