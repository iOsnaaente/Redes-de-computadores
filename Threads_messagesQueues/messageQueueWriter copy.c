# include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define MAX 10 

struct message_queue {
    long msg_type;
    char data[100];
} message;


int main(){

    key_t key;
    int msgid; 

    key = ftok("progfile", 65);
    
    // Cria o message queue e retorna o identificador
    msgid = msgget (key, 0666 | IPC_CREAT );
    message.msg_type = 1;

    print("Write Data here: ");
    fgets( message.data, MAX, stdin );
    
    // Manda a mensagem
    msgsnd( msgid, &message, sizeof(message), 0 );

    // Mostar a mensagem 
    printf( "Data send is : %s", message.data);

    return 0; 
}
