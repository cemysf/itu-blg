///
/// BLG 449 Prog in Parallel&Dist. Sys. Prog
/// Hw - message passing
/// Cem Yusuf Aydoğdu -15120251
/// 29/02/2016
/// 

///
/// Usage: First, run server.c, copy the message queue key
/// from screen, then run the client and select option 1 and
/// paste the key.
///

///! IMPORTANT NOTE: Because ninova only accepts 
///! a single c file, this file contains 
///! two files, server.c and client.c. 

///////////////////////////
/// BEGIN FILE:server.c ///
///////////////////////////


#include <stdio.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <signal.h>

///*   Definitions  *///
#define MAX_CLIENTS 10
#define MAX_GROUPS 100
#define MAX_MSG_LEN 100
static volatile int server_isOnline = 1;

///*   Data structures  *///
// Message queue data structures
typedef struct msg_data
{
    char mtext[MAX_MSG_LEN];
    long pid;       // sender pid
}Data;
typedef struct msg_struct
{
    long mtype;
    Data mdata;
}Message;

// Server data structures
typedef struct msg_group
{
    char group_name[MAX_MSG_LEN];
    key_t group_key;
    long group_members[MAX_CLIENTS];
    int member_count;

}MessageGroup;
typedef struct srv_struct
{
    int my_pid;
    key_t server_mq_key;
    int server_mq_id;

    long clients[MAX_CLIENTS];
    int client_count;

    MessageGroup *groups[MAX_GROUPS];
    int group_count;

}Server;


///*   Functions  *///
// Interrupt handler for main loop for server
void server_intHandler()
{
    server_isOnline = 0;
}

// Creates a new message queue and returns msqid
int createMessageQueue(Server *s, key_t key)
{
    int retval;
    retval = msgget(key, IPC_CREAT | 0660);
    if(retval == -1)
    {
        printf("[Server](%d) ERROR:%s cannot create message queue with key=%d\n", s->my_pid, strerror(errno), key);
    }

    return retval;
}

// Gets a message to given buffer
int getMessage(Server *s, int mq_id, Message *buffer)
{
    int result;

    if(result = msgrcv(mq_id, buffer, sizeof(struct msg_struct) - sizeof(long), 0, 0) == -1 )
    {
        printf("[Server](%d) ERROR:%s while getting message\n", s->my_pid, strerror(errno));
        return -1;
    }
    //printf("[Server](%d) message type=%ld received: '%s', from pid=%ld\n", s->my_pid, buffer->mtype, buffer->mdata.mtext, buffer->mdata.pid);

    return result;
}

// Send a message, takes text and message type as input
int sendMessage(Server *s, char *msg_text, long msg_type ,int mq_id)
{
    int msg_len = strlen(msg_text), retval;
    if(msg_len > MAX_MSG_LEN)
    {
        printf("[Server](%d) ERROR: message '%s' is too long\n", s->my_pid, msg_text);
        return -1;
    }

    Message m;
    strncpy(m.mdata.mtext, msg_text, msg_len);
    m.mdata.mtext[msg_len] = '\0';
    m.mtype = msg_type;
    m.mdata.pid = s->my_pid;

    if(retval = msgsnd(mq_id, &m, sizeof(struct msg_struct) -sizeof(long), 0) == -1)  // returns 0 if succesful
    {
        printf("[Server](%d) ERROR:%s while sending '%s'\n", s->my_pid, strerror(errno), msg_text);
    }
    return retval;
}


int main()
{
    // Initialize server struct
    Server s;
    int i=0,j=0;
    for(i=0 ; i<MAX_CLIENTS; i++)
        s.clients[i]=0;
    s.client_count=0;
    s.group_count=0;
    s.my_pid = getpid();
    s.server_mq_key = ftok(".", 'x');
    printf("[Server](%d) created\n", s.my_pid);

    // Create a group (msg queue) for server-clients communications
    s.server_mq_id = createMessageQueue(&s, s.server_mq_key);
    if(s.server_mq_id == -1)
        return -1;
    printf("!!!!!!!!!!!!!!!!!!!!!!\n");
    printf("[Server](%d) server-clients message queue created \n  KEY= %ld  (copy this for clients)\n", s.my_pid, s.server_mq_key);
    printf("!!!!!!!!!!!!!!!!!!!!!!\n");

    // Add the new group to server's list
    MessageGroup mg;
    char *name = "Server-client comm. group";
    strncpy(mg.group_name,name,strlen(name));
    mg.group_name[strlen(name)] = '\0';
    mg.group_key = s.server_mq_key;
    mg.member_count = 1;
    mg.group_members[0] = s.my_pid;
    for(i=1 ; i<MAX_CLIENTS; i++)
        mg.group_members[i] = 0;
    s.groups[0] = &mg;
    s.group_count += 1;


    printf("\n[Server](%d) waiting for messages (ctrl-c to exit)\n\n", s.my_pid);
    server_isOnline = 1;
    Message m;
    char *text;
    // Server listens for messages in this main loop, differentiates messages with their types
    while(server_isOnline)
    {
        signal(SIGINT, server_intHandler);

        if(getMessage(&s, s.server_mq_id, &m) != -1)
        {
            // Register message received
            if( m.mtype == 1L)
            {
                if(s.client_count > MAX_CLIENTS)
                {
                    printf(" Cannot register client pid=%ld, server is full\n", m.mdata.pid);
                    continue;
                }

                // Write client's pid to a empty location in the list
                i=0;
                s.client_count += 1;
                while(i < s.client_count)
                {
                    if(s.clients[i] == 0)
                    {
                        s.clients[i] = m.mdata.pid;
                        printf("  Client pid=%ld registered\n", m.mdata.pid);
                        break;
                    }
                    i += 1;
                }

            }

            // Signout message received
            if( m.mtype == 2L)
            {
                // Find and delete client's pid
                i=0;
                while(i < s.client_count)
                {
                    if(s.clients[i] == m.mdata.pid)
                    {
                        s.clients[i] = 0;
                        s.client_count -= 1;
                        printf("  Client pid=%ld signout\n", m.mdata.pid);
                        break;
                    }
                    i += 1;
                }
            }

            // List message received
            if( m.mtype == 3L)
            {
                // NOTE: only printing in server side for test
                //!TODO: Send these to client

                printf("--- Groups ---\n");
                for(i=0; i<s.group_count; i++)
                {
                    printf(" Name: %s\n Key:%ld\n", s.groups[i]->group_name, s.groups[i]->group_key);
                    for(j=0; j<s.groups[i]->member_count; j++)
                    {
                        if(j==0)
                            printf("  Member pids\n");
                        printf("    %ld\n", s.groups[i]->group_members[j]);
                    }
                    printf("\n");
                }

                // TODO: send these information to client

            }

        }

    }

    // Exit procedures
    if( msgctl(s.server_mq_id, IPC_RMID, NULL))
    {
        printf("[Server](%d) ERROR:%s while removing message queue with key=%ld\n", s.my_pid, strerror(errno), s.server_mq_key);
        return -1;
    }
    printf("[Server](%d) server main message queue key=%ld marked for removal\n", s.my_pid, s.server_mq_key);
    printf("[Server](%d) exit\n", s.my_pid);
    return 0;

}



///////////////////////////
/// END FILE:server.c /////
///////////////////////////



///////////////////////////
/// BEGIN FILE:client.c ///
///////////////////////////
/*


#include <stdio.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <signal.h>

///   Definitions  ///
#define MAX_MSG_LEN 100
static volatile int client_waitMessages = 1;

///   Data structures  ///
// Message queue data structures
typedef struct msg_data
{
    char mtext[MAX_MSG_LEN];
    long pid;       // sender pid
}Data;
typedef struct msg_struct
{
    long mtype;
    Data mdata;
}Message;

// Client data structure
typedef struct clt_struct
{
    int my_pid;
    long server_mq_key;     // client's server message queue key
    int server_mq_id;       // client's server message queue id
}Client;


///   Functions  ///
// Interrupt handler for main loop for client
void client_intHandler()
{
    client_waitMessages = 0;
}

// Returns message queue id
int connectMessageQueue(Client *c, key_t key)
{
    int retval;
    retval = msgget(key, 0660);
    if(retval == -1)
    {
        printf("[Client](%d) ERROR:%s while connecting message queue with key=%d\n", c->my_pid, strerror(errno), key);
    }

    return retval;
}

int getMessage(Client *c, int mq_id, Message *buffer)
{
    int result;

    if(result = msgrcv(mq_id, buffer, sizeof(struct msg_struct) - sizeof(long), 0, 0) == -1 )
    {
        printf("[Client](%d) ERROR:%s while getting message\n", c->my_pid, strerror(errno));
        return -1;
    }
    printf("[Client](%d) message type=%ld received: '%s', from pid=%ld\n", c->my_pid, buffer->mtype, buffer->mdata.mtext, buffer->mdata.pid);

    return result;
}

int sendMessage(Client *c, char *msg_text, long msg_type ,int mq_id)
{
    int msg_len = strlen(msg_text), retval;
    if(msg_len > MAX_MSG_LEN)
    {
        printf("[Client](%d) ERROR: message '%s' is too long\n", c->my_pid, msg_text);
        return -1;
    }

    Message m;
    strncpy(m.mdata.mtext, msg_text, msg_len);
    m.mdata.mtext[msg_len] = '\0';
    m.mtype = msg_type;
    m.mdata.pid = c->my_pid;

    if(retval = msgsnd(mq_id, &m, sizeof(struct msg_struct) -sizeof(long), 0) == -1)  // returns 0 if succesful
    {
        printf("[Client](%d) ERROR:%s while sending '%s'\n", c->my_pid, strerror(errno), msg_text);
    }
    return retval;
}

// Show options for client
void showMenu()
{
    printf("\n\nSelect operation\n");
    printf(" 1. Register to server\n");
    printf(" 2. Sign out from server\n");
    printf(" 3. List messaging groups\n");
    printf(" 4. Send a message\n");
    printf(" 5. Listen for messages\n");
    printf("\n 0. Exit\n");
}


int main()
{
    // Initialize necessary data
    Client c;
    c.my_pid = getpid();
    c.server_mq_id = -1;
    printf("[Client](%d) created\n", c.my_pid);

    int client_isOnline=1, option;
    Message m;
    char *message;

    // Client main loop
    while(client_isOnline)
    {
        showMenu();
        printf(" Select option: ");
        scanf("%d", &option);

        switch (option)
        {
        // Connect to server message queue with its known key
        case 1:
            printf(" Server key: ");
            scanf("%ld", &c.server_mq_key);

            // Get server message queue id
            c.server_mq_id = connectMessageQueue(&c, c.server_mq_key);
            if(c.server_mq_id == -1 )
                return -1;
            printf("[Client](%d) connected server's message queue with key=%ld, id=%d\n", c.my_pid, c.server_mq_key, c.server_mq_id);

            // Send 'REGISTER' message to server, with message id=1
            message = "REGISTER";
            if(sendMessage(&c, message, 1L, c.server_mq_id) == 0)
                printf("[Client](%d) message '%s' sent to server\n", c.my_pid, message);
            break;

        // Sign out from server
        case 2:
            if(c.server_mq_id == -1)
            {
                printf("Error: connect to server first\n");
                break;
            }

            // Send 'SIGNOUT' message to server, with message id=2
            message = "SIGNOUT";
            if(sendMessage(&c, message, 2L, c.server_mq_id) == 0)
                printf("[Client](%d) message '%s' sent to server\n", c.my_pid, message);
            break;

        // Request groups list from server
        case 3:
            if(c.server_mq_id == -1)
            {
                printf("Error: connect to server first\n");
                break;
            }

            // Send 'REGISTER' message to server, with message id=3
            message = "LIST";
            if(sendMessage(&c, message, 3L, c.server_mq_id) == 0)
                printf("[Client](%d) message '%s' sent to server\n", c.my_pid, message);

            //!TODO: Receive list from server

            break;

        // Send messages to listening clients
        case 4:

            if(c.server_mq_id == -1)
            {
                printf("Error: connect to server first\n");
                break;
            }

            //!TODO: Send message to any group with ket key from user

            printf("Message: ");

            char text[MAX_MSG_LEN];
            scanf("%s", &text);
            text[strlen(text)] = '\0';

            printf ("m: %s\n", text);
            if(sendMessage(&c, text, 4L, c.server_mq_id) == 0)
                printf("[Client](%d) message '%s' sent to server\n", c.my_pid, text);
            break;

        // Listen messages from clients
        case 5:
            printf("Listening message queue\n");
            Message m;
            while(client_waitMessages == 1)
            {
                signal(SIGINT, client_intHandler);
                if(getMessage (&c, c.server_mq_id, &m) != -1)
                {
                    if(m.mtype == 4L)
                        printf("     (pid:%ld) - %s\n", m.mdata.pid, m.mdata.mtext);
                }

            }
            client_waitMessages = 1;
            break;

            //!TODO: Sign in to a messaging group with key
        //case 6:
            ///
            //break;

            //!TODO: Sign out from a messaging group
        //case 7:
            ///
            //break;

        // Quit
        case 0:
            client_isOnline = 0;
            if(c.server_mq_id != -1)
            {
                // Send 'SIGNOUT' message to server, with message id=2
                message = "SIGNOUT";
                if(sendMessage(&c, message, 2L, c.server_mq_id) == 0)
                    printf("[Client](%ld) message '%s' sent to server\n", c.my_pid, message);
            }
            break;

        default:
            printf(" invalid option\n");
            break;
        }

        printf("  enter to continue..\n");
        getchar();
        getchar();
    }


    printf(" [Client](%d) exit\n", getpid());
    return 0;
}

*/
///////////////////////////
/// END FILE:client.c /////
///////////////////////////

