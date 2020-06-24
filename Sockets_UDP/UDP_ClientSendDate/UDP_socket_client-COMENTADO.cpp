/*
    User Datagram Protocol - UDP
      CÓDIGO CLIENTE COMENTADO

    Criado por Sampaio. Bruno Gabriel

    Tarefa de Redes Industriais
    Protocolo de transferencia UDP
      
      Apenas recebe um datagram  
        vindo do lado cliente
*/
    
#include<stdlib.h>  
#include<stdio.h>      
#include <time.h>

// Código para Linux
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netdb.h>

#define IPSer "127.0.0.1" 
#define PORTA 8080

#define MAX_BUFF 32

// PEGAR A DATA ATUAL DO SISTEMA PARA ENVIAR VIA DATAGRAM
time_t rawtime;
struct tm * timeinfo;

// NÚMERO DA MENSAGEM ENVIADA
int identation = 0;

// CRIA O BUFFER PARA A MENSAGEM A SER ENVIADA
uint8_t MESSAGE_BUFF[MAX_BUFF];
uint8_t MESSAGE_LEN = sizeof(MESSAGE_BUFF);

// CRIA ESTRUTURA DO SOCKET SERVIDOR 
struct sockaddr_in socketServidor;                          

// STATUS DE socket() E sendto()
int socketLocal;
int statusSend;


void erro(char * srt_erro);

int main(){

    // CONFIGURA O SOCKET UDP
    socketLocal = socket(AF_INET, SOCK_DGRAM, 0);
    if (socketLocal == -1)
        erro((char *)"Erro ao criar o socket do cliente");


    // CONFIGURANDO PARA O Socket DO SERVIDOR
    socketServidor.sin_family      = AF_INET;                   // CONFIGURAÇÔES DE SOCKET
    socketServidor.sin_port        = htons(PORTA);              // PORTA ABERTA 
    socketServidor.sin_addr.s_addr = inet_addr(IPSer);          // REDE LOCAL

    // AQUISIÇÃO DOS DADOS DE DATA E HORA
    time ( &rawtime );
    timeinfo = localtime ( &rawtime );

    // timeinfo usa -> o inves de . porque é struct de ponteiro 
    MESSAGE_BUFF[0] = timeinfo->tm_sec;
    MESSAGE_BUFF[1] = timeinfo->tm_min;
    MESSAGE_BUFF[2] = timeinfo->tm_hour;
    MESSAGE_BUFF[3] = timeinfo->tm_wday;
    MESSAGE_BUFF[4] = timeinfo->tm_mday;
    MESSAGE_BUFF[5] = timeinfo->tm_mon;
    MESSAGE_BUFF[6] = timeinfo->tm_year;
    MESSAGE_BUFF[7] = identation++;

    //printf ( "Data atual do sistema é: %s", asctime (timeinfo) );

    // UDP É CONNECTIONLESS OU SEJA, SEM CONEXÃO - APENAS ENVIAMOS COM O sendto() O DATAGRAM
    statusSend = sendto(socketLocal, &MESSAGE_BUFF, MESSAGE_LEN, 0, (struct sockaddr *)&socketServidor, sizeof(socketServidor) );
    if (statusSend == -1)
        erro((char *)"sendTo() falhou...!!!");
    
}

void erro( char * str_erro){
    perror(str_erro);
    exit(1);
} 