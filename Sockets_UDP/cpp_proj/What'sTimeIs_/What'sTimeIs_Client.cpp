#include<sys/socket.h>
#include<arpa/inet.h>
#include<string.h>
#include<netdb.h>
#include<stdlib.h>  
#include<stdio.h>      
#include <time.h>

/*
    User Datagram Protocol - UDP
          CÓDIGO SERVIDOR

    Criado por Sampaio. Bruno Gabriel

    Tarefa de Redes Industriais
    Protocolo de transferencia UDP

    Client:   Que horas são ?
    Server:  'O Server responde' ;)
    
*/
    
#define IPSer "127.0.0.1" 
#define PORTA 8080

#define MAX_BUFF 32

uint8_t RECEIVE_BUFF[MAX_BUFF];
uint8_t RECEIVE_LEN = sizeof(RECEIVE_BUFF);

struct sockaddr_in socketServidor;                          
int socketServidor_LEN = sizeof(socketServidor);

void erro(char * srt_erro);

int main(){

    int socketLocal = socket(AF_INET, SOCK_DGRAM, 0);
    if (socketLocal == -1)
        erro((char *)"Erro ao criar o socket do cliente");

    socketServidor.sin_family      = AF_INET;     
    socketServidor.sin_port        = htons(PORTA);  
    socketServidor.sin_addr.s_addr = inet_addr(IPSer);

    char * question = (char *)"Que horas são?";
    printf("%s", question);

    int statusSend = sendto(socketLocal, &question, strlen(question), 0, (struct sockaddr *)&socketServidor, sizeof(socketServidor) );
    if (statusSend == -1)
        erro((char *)"sendTo() falhou...!!!");
    
    int statusAnswer = recvfrom(socketLocal, RECEIVE_BUFF, RECEIVE_LEN, 0, (struct sockaddr *)&socketServidor, (socklen_t *)&socketServidor_LEN);
    if (statusAnswer == -1)
        erro((char *)"recvfrom() error");
    else
        printf("Agora é %s\n", RECEIVE_BUFF);
}

void erro( char * str_erro){
    perror(str_erro);
    exit(1);
} 