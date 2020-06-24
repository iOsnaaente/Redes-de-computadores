/*
    User Datagram Protocol - UDP
     CÓDIGO SERVIDOR COMENTADO

    Criado por Sampaio. Bruno Gabriel

    Tarefa de Redes Industriais
    Protocolo de transferencia UDP

       Apenas envia um datagram  
        para o lado servidor
*/

#include<stdio.h>       
#include<stdlib.h>      
#include<string.h>      

#include<sys/socket.h>  // PARA socket() EM UDP - TCP - RAW
#include<netdb.h>       // PARA O bind() sendto() recvfrom()




#define MAX_BUF_LEN 512
#define PORTA 8080


// NECESSÁRIO PARA CONFIGURAÇÕES DE recvfrom() LADO CLIENTE

// SALVAMOS O NÚMERO DE BYTES RECEBIDOS NO DATAGRAM
int receive_data = 0;
char BUFF[MAX_BUF_LEN];
struct sockaddr_in Socket_Client;
int Socket_Client_Size = sizeof(struct sockaddr_in);

// MENSAGEM DE RESPOSTA AO DATAGRAM RECEBIDO 
char MESSAGE[] = "MENSAGEM RECEBIDO PELO SERVIDOR NA PORTA 8080";


void erro(char * str_erro){
    perror(str_erro);
    exit(1);
}

int main(){    

    // CRIA O SOCKET DO SERVIDOR (O PLUG)
    /// ESTRUTURAÇÃO DO SOCKET
    /// int socket(int domain, int type, int protocol)
    /// \param domain IP_INET = IP_v4 : IP_INET6 = IP_v6
    /// \param type Tipo de comunicação SOCK_DGRAM = UDP : SOCK_STREAM = TCP
    /// \param protocol Definição do protocolo de comunicação IPPROTO_UDP : UDP 
    /// \param return o valor inteiro de descritor de arquivo SD ou -1 para indicar erro
    int Sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    if (Sock == -1){
        erro((char *)"Socket não pode ser criado!!");
    }

    // PARA CONFIGURAÇÃO DA ADDR LOCAL - LADO SERVIDOR 
    struct sockaddr_in Socket_Server;   

    // ANTES DE CONFIGURAR, SETAR A MEMÓRIA DA STRUCT
    memset((char *)&Socket_Server, 0, sizeof(Socket_Server));  // Endereço, valor, tamanho

    Socket_Server.sin_family      = AF_INET;                   // CONFIGURAÇÔES DE SOCKET
    Socket_Server.sin_port        = htons(PORTA);              // PORTA PARA DE COMUNICAÇÃO
    Socket_Server.sin_addr.s_addr = INADDR_ANY;                // RECEBE QUALQUER IP (Servidor não se importa)


    // FUNÇÃO Bind PARA INICIAR A ESCUTA DA PORTA ADDR
    /// Estruturação do Bind
    /// int bind(int socket descriptor, struct sockaddr* myaddr ou INADDR_ANY, int socket_length)
    if( bind(Sock, (struct  sockaddr *) &Socket_Server, sizeof(Socket_Server)) == -1)
        erro((char *)"bind");

    /*
    *  INADDR_ANY ACEITA QUALQUER ADDR QUE RECEBA - USANDO O SOCKET ESPECIFICO, SÓ ACEITAMOS DESSA ADDR
    *  Bind ASSOCIA UM SOCKET ADDRESS IP+PORTA AO SOCKET DO SERVIDOR
    *  CASO RETORNE -1 SINAL QUE NÃO PODE FAZER A OPERAÇÃO
    */

    // ESTAMOS AGORA COM TUDO CONFIGURADO  NO LADO SERVIDOR
    // BASTA COMEÇARMOS A ESCUTAR O LADO CLIENTE

    while(1){
        
        printf("Aguardando transmissão de dados....\n");
        
        // LIVRAMOS O BUFFER LOCAL DE QUALQUER LIXO QUE ESTEJA ARMAZENANDO INTERNAMENTE
        fflush(stdout);

        // RECEBE ALGUM DADO DE ALGUM CLIENTE
        // SE NENHUM CLINETE MANDAR NADA, DARÁ ERRO;
        /// int recvfrom(int sd, void *buffer, int bufferSize, int flags, struct sockaddr *from, int *sockaddrsize)
        /// \param SD Socket Descriptor - criado no lado servidor
        /// \param BUFFER onde os bytes recebidos irão ser salvos 
        /// \param BUFEER_SIZE o número máximo do BUFFER
        /// \param FROM Ponteiro do Struct sockaddr *CLIENTE - Endereço da origem - recebe na struct criada no lado servidor 
        /// \param return retorna o valor de N bytes salvos no BUFFER ou -1 caso dê erro
        receive_data = recvfrom(Sock, BUFF, MAX_BUF_LEN, 0, (struct  sockaddr *)&Socket_Client, (socklen_t *)&Socket_Client_Size);
        if (receive_data == -1 ){
            erro((char *)"recvfrom()");
        }else{
            // SE NÃO DEU ERRO, TEMOS AGORA UM BUFFER DE n BYTES = receive_data E PODEMOS ACESSA-LO
            printf("Dados recebidos de %s:%d \n", Socket_Client.sin_addr, ntohs(Socket_Client.sin_port));
            printf("Recebido: %s\n", BUFF);
        }
        
        //SE O SERVIDOR ENCONTRAR UM DATAGRAM E QUISER RESPONDER AO REMETENTE ELE USA sendto()
        // PARAMETROS INERSOS DO recvfrom() - INTUITIVO 
        // não necessário
        int sendStatus = sendto(Sock, (void *)MESSAGE, strlen(MESSAGE), 0, (struct sockaddr *)&Socket_Client.sin_addr, sizeof(struct sockaddr));
        if (sendStatus == -1)
            erro((char *)"sendto() erro na resposta parao cliente");


        // REPETE O CICLO ATRÁS DE NOVOS CHAMADOS OU ENCERRA
        
        // PARA ENCERRAR O SOCKET COMO SEGURANÇA
        // CASO QUISERMOS ENCERRAR, MAS ELE AINDA NÃO COMPLETOU ALGUM ENVIO OU RECEBIMENTO
        // ELE AGUARDA ESSA FINALIZAÇÃO
        /// \param sd Socket Descriptor - Socket que queremos fechar 
        /// \param return Retorna o estado da fechagem -1 = erro : 1 = OK 
        //if (close(Sock) == -1)
        //    erro((char*)"Erro na hora de encerrar o Socket....");
    
    }
    return 0;
}

