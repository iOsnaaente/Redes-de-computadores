<<<<<<< HEAD
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

# define MAX 10

// ESTRUTURA DO MESSAGE QUEUE 
struct message_queue {
    long msg_type;
    char data[255];
};


// THREAD 1 VAI ESCREVER EM UM MESSAGE QUEUE 
 void * threadWrite(void *arg, key_t key, int msgid) {
    
    // Cria uma messageWrite 
    struct message_queue messageWrite; 

    // Cria o message queue e retorna o identificador
    msgid = msgget (key, 0666 | IPC_CREAT );
    messageWrite.msg_type = 1;
    
    int i = 0 ;
    char * messageData = (char*) 0 ;

    for (i = 0; i < 255; i++)
        
        *messageData ++ = (char*) i ; 
        
        // Salva a char crescente em messageWrite.data 
        fgets( messageWrite.data, MAX, messageData );
        
        // Manda a mensagem
        msgsnd( msgid, &messageWrite, sizeof(messageWrite), 0 );

        // Sleep de 0.01 segundos 
        sleep(0.01);

    return NULL;
}


// THREAD 2 VAI LER O MESSAGE QUEUE 
void * threadRead( void *arg, key_t key, int msgid ){

    // Cria uma messageWrite 
    struct message_queue messageRead; 

    // Recebe a mensagem
    msgrcv( msgid, &messageRead, sizeof(messageRead), 1, 0 );

    // Mostar a mensagem 
    printf( "Data send is : %s", messageRead.data);

    return NULL;
}


int main() {

    // CRIA A CHAVE E O ID DO QUEUE
    key_t key;
    int msgid; 

    // UNIFICA A CHAVE ( UNIQUE )
    key = ftok("progfile", 65);
    

    // Cria as threads Write e Read 
    pthread_t thr1, thr2;
    int i;

    if ( pthread_create( &thr1, NULL, threadWrite, (key, msgid) ) ) {
        printf("error creating thread 1.");
        abort();
    }

    if ( pthread_create( &thr2, NULL, threadRead, (key, msgid) ) ){
        printf("error creating thread 2.");
        abort();
    }

    // CÓDIGO AQUI 

    for ( i = 0; i < 20; i++ ) {
        
        myglobal = myglobal+1;

        printf("o");
        fflush(stdout);
        sleep(1);

    }

    // FIM DO CÓDIGO 

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
=======
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

# define MAX 10

// ESTRUTURA DO MESSAGE QUEUE 
struct message_queue {
    long msg_type;
    char data[255];
};


// THREAD 1 VAI ESCREVER EM UM MESSAGE QUEUE 
 void * threadWrite(void *arg, key_t key, int msgid) {
    
    // Cria uma messageWrite 
    struct message_queue messageWrite; 

    // Cria o message queue e retorna o identificador
    msgid = msgget (key, 0666 | IPC_CREAT );
    messageWrite.msg_type = 1;
    
    int i = 0 ;
    char * messageData = (char*) 0 ;

    for (i = 0; i < 255; i++)
        
        *messageData ++ = (char*) i ; 
        
        // Salva a char crescente em messageWrite.data 
        fgets( messageWrite.data, MAX, messageData );
        
        // Manda a mensagem
        msgsnd( msgid, &messageWrite, sizeof(messageWrite), 0 );

        // Sleep de 0.01 segundos 
        sleep(0.01);

    return NULL;
}


// THREAD 2 VAI LER O MESSAGE QUEUE 
void * threadRead( void *arg, key_t key, int msgid ){

    // Cria uma messageWrite 
    struct message_queue messageRead; 

    // Recebe a mensagem
    msgrcv( msgid, &messageRead, sizeof(messageRead), 1, 0 );

    // Mostar a mensagem 
    printf( "Data send is : %s", messageRead.data);

    return NULL;
}


int main() {

    // CRIA A CHAVE E O ID DO QUEUE
    key_t key;
    int msgid; 

    // UNIFICA A CHAVE ( UNIQUE )
    key = ftok("progfile", 65);
    

    // Cria as threads Write e Read 
    pthread_t thr1, thr2;
    int i;

    if ( pthread_create( &thr1, NULL, threadWrite, (key, msgid) ) ) {
        printf("error creating thread 1.");
        abort();
    }

    if ( pthread_create( &thr2, NULL, threadRead, (key, msgid) ) ){
        printf("error creating thread 2.");
        abort();
    }

    // CÓDIGO AQUI 

    for ( i = 0; i < 20; i++ ) {
        
        myglobal = myglobal+1;

        printf("o");
        fflush(stdout);
        sleep(1);

    }

    // FIM DO CÓDIGO 

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
>>>>>>> 2294ba3496aa0706b65e15105de47c11e53b91de
}