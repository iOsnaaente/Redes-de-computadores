#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <string.h>

# define MAX 10

// ESTRUTURA DO MESSAGE QUEUE 
struct message_queue {
    long msg_type;
    char data[255];
};


// CRIA A CHAVE E O ID DO QUEUE
key_t key;
int msgid; 


// THREAD 1 VAI ESCREVER EM UM MESSAGE QUEUE 
 void * threadWrite(void *arg) {
    
    // Cria uma messageWrite 
    struct message_queue messageWrite; 

    // Cria o message queue e retorna o identificador
    msgid = msgget (key, 0666 | IPC_CREAT );
    messageWrite.msg_type = 1;
    
    char i;
    char * messageData ;

    while ( fgets( messageWrite.data, sizeof(messageWrite), stdin ) != NULL ) {

        // Recebe a mensagem
        int len = strlen(messageWrite.data);

        if (messageWrite.data[len-1] == '\n'){
            messageWrite.data[len-1] = '\0';
        }
        // Manda a mensagem
        if ( msgsnd( msgid, &messageWrite, len+1 , 0 ) == -1){
            perror("msgsnd error");
        }
    }
    
    if ( msgctl(msgid, IPC_RMID, NULL) == -1 ){
        perror("msgctl error");
        exit(1);
    }

    return NULL;
}


// THREAD 2 VAI LER O MESSAGE QUEUE 
void * threadRead( void *arg ){

    // Cria uma messageWrite 
    struct message_queue messageRead; 

    // Cria o message queue e retorna o identificador
    msgid = msgget (key, 0666 | IPC_CREAT );
    messageRead.msg_type = 1;

    while ( 1 ){
        if ( msgrcv( msgid, &messageRead, sizeof(messageRead.data), 0, 0 ) == -1 ){
            perror("msrcv error");
            exit(1);
        }  
        // Mostar a mensagem 
        printf( "Data send is : %s \n", messageRead.data);
    }
    return NULL;
}

int main() {

    // UNIFICA A CHAVE ( UNIQUE )
    key = ftok("progfile", 65);
    
    // Cria as threads Write e Read 
    pthread_t thr1, thr2;
    int i;

    if ( pthread_create( &thr1, NULL, threadWrite, NULL ) ) {
        printf("error creating thread 1.");
        abort();
    }

    if ( pthread_create( &thr2, NULL, threadRead, NULL ) ){
        printf("error creating thread 2.");
        abort();
    }


    // ENCERRA AS THREADS 
    if ( pthread_join ( thr1, NULL ) ) {
        printf("error joining thread 1 .");
        abort();
    }

    // Destroi a message queue 
    msgctl(msgid, IPC_RMID, NULL);

    if ( pthread_join ( thr2, NULL ) ) {
        printf("error joining thread 2 .");
        abort();
    }

    exit(0);

    return 0;
}