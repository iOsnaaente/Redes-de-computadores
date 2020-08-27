#include<sys/socket.h>
#include<arpa/inet.h>
#include<netdb.h>
#include<stdlib.h>  
#include<stdio.h>    
#include <time.h>

/*
    User Datagram Protocol - UDP
         CÓDIGO CLIENTE

    Criado por Sampaio. Bruno Gabriel

    Tarefa de Redes Industriais
    Protocolo de transferencia UDP

       Apenas envia um datagram  
        para o lado servidor
*/
    
#define IPSer "127.0.0.1" 
#define PORTA 8080

#define MAX_BUFF 32

time_t rawtime;
struct tm * timeinfo;

uint8_t MESSAGE_BUFF[MAX_BUFF];
uint8_t MESSAGE_LEN = sizeof(MESSAGE_BUFF);

uint8_t RECEIVE_BUFF[MAX_BUFF];
uint8_t RECEIVE_LEN = sizeof(RECEIVE_BUFF);

struct sockaddr_in socketServidor;                          

int socketLocal;
int statusSend;
int statusReceive;

void erro(char * srt_erro);

int main(){

    socketLocal = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (socketLocal == -1)
        erro((char *)"Erro ao criar o socket do cliente");


   socketServidor.sin_family      = AF_INET;                
    socketServidor.sin_port        = htons(PORTA);             
    socketServidor.sin_addr.s_addr = inet_addr(IPSer);   

    time ( &rawtime );
    timeinfo = localtime ( &rawtime );

    MESSAGE_BUFF[0] = timeinfo->tm_sec;
    MESSAGE_BUFF[1] = timeinfo->tm_min;
    MESSAGE_BUFF[2] = timeinfo->tm_hour;
    MESSAGE_BUFF[3] = timeinfo->tm_wday;
    MESSAGE_BUFF[4] = timeinfo->tm_mday;
    MESSAGE_BUFF[5] = timeinfo->tm_mon;
    MESSAGE_BUFF[6] = timeinfo->tm_year;
    
    statusSend = sendto(socketLocal, &MESSAGE_BUFF, MESSAGE_LEN, 0, (struct sockaddr *)&socketServidor, sizeof(socketServidor) );
    if (statusSend == -1)
        erro((char *)"sendTo() falhou...!!!");
    statusReceive = recvfrom(socketLocal, &RECEIVE_BUFF, RECEIVE_LEN, 0, NULL, NULL);
    if (statusReceive == -1){
        erro((char *)"Erro no recebimento de resposta");
    }else{
        printf("Mensagem recebida pelo servidor");
    }

}

void erro( char * str_erro){
    perror(str_erro);
    exit(1);
} 