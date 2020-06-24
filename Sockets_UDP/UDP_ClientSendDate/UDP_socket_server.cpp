#include<sys/socket.h>  
#include<arpa/inet.h>
#include<netdb.h> 
#include<stdio.h>          
#include<stdlib.h>      
#include<string.h>   

/*
    User Datagram Protocol - UDP
         CÓDIGO SERVIDOR

    Criado por Sampaio. Bruno Gabriel

    Tarefa de Redes Industriais
    Protocolo de transferencia UDP
      
      Apenas recebe um datagram  
        vindo do lado cliente
        
*/

#define MAX_BUF_LEN 512
#define PORTA 8080

int receive_data = 0;
char BUFF[MAX_BUF_LEN];
struct sockaddr_in Socket_Client;
int Socket_Client_Size = sizeof(struct sockaddr_in);

char * MESSAGE = (char *)"MENSAGEM RECEBIDO PELO SERVIDOR NA PORTA 8080";

void erro(char * str_erro){
    perror(str_erro);
    exit(1);
}

int main(){    

    int Sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    if (Sock == -1){
        erro((char *)"Socket não pode ser criado!!");
    }

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

        receive_data = recvfrom(Sock, BUFF, MAX_BUF_LEN, 0, (struct  sockaddr *)&Socket_Client, (socklen_t *)&Socket_Client_Size);
        if (receive_data == -1 ){
            erro((char *)"recvfrom()");
        }else{
            printf("Dados recebidos de %s:%d \nRecebido:", inet_ntoa(Socket_Client.sin_addr), ntohs(Socket_Client.sin_port));
            for (int i = 0; i<7; i++)
                printf("%i ", BUFF[i]);
            printf("\n");
        }
    }
    return 0;
}

