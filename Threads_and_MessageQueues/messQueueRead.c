<<<<<<< HEAD
# include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define MAX 10 

struct message_buff {
    long msg_type;
    char data[100];
} message;


int main(){

    key_t key;
    int msgid; 

    // Gera uma chave unica 
    key = ftok("progfile", 65);
    
    // Cria o message queue e retorna o identificador
    msgid = msgget (key, 0666 | IPC_CREAT );
    
    // Recebe a mensagem
    msgrcv( msgid, &message, sizeof(message), 1, 0 );

    // Mostar a mensagem 
    printf( "Data send is : %s", message.data);

    // Destroi a message queue 
    msgctl(msgid, IPC_RMID, NULL);
    
    return 0; 
=======
# include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define MAX 10 

struct message_buff {
    long msg_type;
    char data[100];
} message;


int main(){

    key_t key;
    int msgid; 

    // Gera uma chave unica 
    key = ftok("progfile", 65);
    
    // Cria o message queue e retorna o identificador
    msgid = msgget (key, 0666 | IPC_CREAT );
    
    // Recebe a mensagem
    msgrcv( msgid, &message, sizeof(message), 1, 0 );

    // Mostar a mensagem 
    printf( "Data send is : %s", message.data);

    // Destroi a message queue 
    msgctl(msgid, IPC_RMID, NULL);
    
    return 0; 
>>>>>>> 2294ba3496aa0706b65e15105de47c11e53b91de
}