/*
    User Datagram Protocol - UDP
          CÓDIGO SERVIDOR

    Criado por Sampaio. Bruno Gabriel
    Tarefa de Redes Industriais
    Protocolo de transferencia UDP
*/

#include<sys/socket.h>
#include<stdlib.h>      
#include<string.h> 
#include<netdb.h>
#include<stdio.h>       


#define MAX_BUF_LEN 512
#define PORTA 8080

int receive_data = 0;

char BUFF[MAX_BUF_LEN];

struct sockaddr_in Socket_Client;
int Socket_Client_Size = sizeof(struct sockaddr_in);

char MESSAGE[] = "MENSAGEM RECEBIDO PELO SERVIDOR NA PORTA 8080";


void erro(char * str_erro);

int main(){    

    int Sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    if (Sock == -1)
        erro((char *)"Socket não pode ser criado!!");
    
    struct sockaddr_in Socket_Server;   
    memset((char *)&Socket_Server, 0, sizeof(Socket_Server));  

    Socket_Server.sin_family      = AF_INET; 
    Socket_Server.sin_port        = htons(PORTA);
    Socket_Server.sin_addr.s_addr = INADDR_ANY;  

    if( bind(Sock, (struct  sockaddr *) &Socket_Server, sizeof(Socket_Server)) == -1)
        erro((char *)"bind");

    while(1){
        
        printf("Aguardando transmissão de dados....\n");
        fflush(stdout);

        receive_data = recvfrom(Sock, BUFF, MAX_BUF_LEN, 0, (struct  sockaddr *)&Socket_Client, Socket_Client_Size);
        if (receive_data == -1 ){
            erro((char *)"recvfrom()");
        }else{
            printf("Dados recebidos de %s:%d \n", Socket_Client.sin_addr, ntohs(Socket_Client.sin_port));
            printf("Recebido: %s\n", BUFF);
        }
        
        int sendStatus = sendto(Sock, (void *)MESSAGE, strlen(MESSAGE), 0, (struct sockaddr *)&Socket_Client.sin_addr, sizeof(struct sockaddr));
        if (sendStatus == -1)
            erro((char *)"sendto() erro na resposta parao cliente");    
    }

    //if (close(Sock) == -1)
    //    erro((char*)"Erro na hora de encerrar o Socket....");
    return 0;
}


void erro(char * str_erro){
    perror(str_erro);
    exit(1);
}