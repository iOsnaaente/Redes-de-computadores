#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>      
#include <string.h> 
#include <netdb.h>
#include <stdio.h>
#include <time.h>

/*
      User Datagram Protocol - UDP
            CÓDIGO SERVIDOR

    Criado por Sampaio. Bruno Gabriel
        Tarefa de Redes Industriais
       Protocolo de transferencia UDP

    O Servidor tem a tarefa de receber
    os Datagrans do Cliente com a soli-
    citação  dos   dados  coletados  e 
    enviar de volta.

*/

#define MAX_BUF_LEN 512
#define PORTA 8080

char MESSAGE_BUFF[MAX_BUF_LEN];
int  MESSAGE_LEN = sizeof(MESSAGE_BUFF);

char RECEIVE_BUFF[MAX_BUF_LEN];
int  RECEIVE_LEN = sizeof(RECEIVE_BUFF);


struct sockaddr_in Socket_Client;
int Socket_Client_Size = sizeof(Socket_Client);


bool flagReceive = false;


void erro(char * str_erro);


int main(){    

    // CRIA O SOCKET UDP 
    int Sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (Sock == -1)
        erro((char *)"Socket não pode ser criado!!");
    
    // CRIA A ESTRUTURA DA COMUNICAÇÃO
    struct sockaddr_in Socket_Server;   
    memset((char *)&Socket_Server, 0, sizeof(Socket_Server));  

    Socket_Server.sin_family      = AF_INET; 
    Socket_Server.sin_port        = htons(PORTA);
    Socket_Server.sin_addr.s_addr = INADDR_ANY;  

    // INICIA A SESSÃO DE SERVIDOR
    if( bind(Sock, (struct  sockaddr *) &Socket_Server, sizeof(Socket_Server)) == -1)
        erro((char *)"bind");

    // COMEÇA A RECEBER
    while(1){
        
        printf("Aguardando transmissão de dados....\n");
        fflush(stdout);

        receive_data = recvfrom(Sock, RECEIVE_BUFF, RECEIVE_LEN, 0, (struct  sockaddr *)&Socket_Client, (socklen_t *)&Socket_Client_Size);
        if (receive_data == -1 ){
            erro((char *)"recvfrom()");
            flagReceive = false;
        }else{
            printf("Recebidos de %s:%d \n", inet_ntoa(Socket_Client.sin_addr), ntohs(Socket_Client.sin_port));
            printf("Recebido: %s", RECEIVE_BUFF);
            flagReceive = true;
        }

        if(flagReceive){
            if (strcmp(question, RECEIVE_BUFF)){
                // A MENSAGEM RECEBIDA É O PEDIDO DE INFORMAÇÕES
                if(sendto(Sock, (void *)MESSAGE_BUFF, strlen(MESSAGE_BUFF),0, (struct sockaddr *)&Socket_Client, Socket_Client_Size)==-1)
                    erro((char *)"sendto() error");

            }else{
                printf("Foi recebido %s de %s:%d e deveria ser %s\n", RECEIVE_BUFF, inet_ntoa(Socket_Client.sin_addr),ntohs(Socket_Client.sin_port), question);
            }
            //TERMINA A COMUNICAÇÃO E VOLTA A ESCUTAR
            flagReceive = false;
        }    
    }
    return 0;
}

void erro(char * str_erro){
    perror(str_erro);
    exit(1);
}