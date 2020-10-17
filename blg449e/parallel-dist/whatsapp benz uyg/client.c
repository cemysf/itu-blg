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
