#include<stdio.h>       //printf
#include<stdlib.h>      //exit(0);

#include<string.h>      //memset

#include<sys/socket.h>
#include<arpa/inet.h>
#include<netdb.h>


// Socket UDP Client

#define PORTA 8080
#define MAX_BUF_LEN 512

void die(char *s);

int main(){

    struct sockaddr_in Socket_Client, Socket_Server;           // CRIA ESTRUTURA DO SOCKET SERVIDOR e CLIENTE 

    char BUFF[MAX_BUF_LEN];
    
    int sock_len = sizeof(Socket_Client);
    int sock = 0;
    
    int receive_data = 0;

    // CRIA O SOCKET UDP DO SERVIDOR
    if( (sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP))==-1)
        die("socket");

    // ANTES DE CONFIGURAR, SETAR A MEMÓRIA DA STRUCT
    memset((char *)&Socket_Server, 0, sizeof(Socket_Server));
    
    Socket_Server.sin_family      = AF_INET;                   // CONFIGURAÇÔES DE SOCKET
    Socket_Server.sin_port        = htons(PORTA);              // PORTA DO CLIENTE 
    Socket_Server.sin_addr.s_addr = inet_addr(INADDR_ANY);     // RECEBE QUALQUER IP (dosn't matter)

    // FUNÇÃO Bind PARA INICIAR A ESCUTA NA PORTA
    if( bind(sock, (struct  sockaddr *) &Socket_Server, sizeof(Socket_Server))== -1)
        die("bind");
    

    while(1){
        printf("Aguardando transmissão de dados....\n");
        fflush(stdout);

        // RECEBE ALGUM DADO DE ALGUM CLIENTE
        // SE NENHUM CLINETE MANDAR NADA, DARÁ ERRO;
        if(receive_data = recvfrom(sock, BUFF, MAX_BUF_LEN, 0, (struct  sockaddr *)&Socket_Client, &sock_len)==-1)
            die("recvfrom()");

        printf("Dados recebidos de %s:%d \n", inet_ntoa(Socket_Client.sin_addr), ntohs(Socket_Client.sin_port));
        printf("Recebido: %s\n", BUFF);

        // REPETE O CICLO ATRÁS DE NOVOS CHAMADOS
    }
    return 0;
}

void die(char *string){
    perror(string);
    exit(1);
}