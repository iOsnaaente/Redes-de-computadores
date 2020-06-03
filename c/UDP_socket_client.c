#include<stdio.h>       //printf
#include<stdlib.h>      //exit(0);

#include<arpa/inet.h>
#include<netdb.h>


// Socket UDP Client  

#define IPSer "127.0.0.0" 
#define PORTA 8080

int main(){

    struct sockaddr_in socketAlvo;                          // CRIA ESTRUTURA DO SOCKET SERVIDOR 

    int socketLocal;
    int conexao;

    // CONFIGURA O SOCKET UDP
    socketLocal = socket(AF_INET, SOCK_DGRAM, 0);
    
    // Socket DO SERVIDOR
    socketAlvo.sin_family      = AF_INET;                   // CONFIGURAÇÔES DE SOCKET
    socketAlvo.sin_port        = htons(PORTA);              // PORTA ABERTA 
    socketAlvo.sin_addr.s_addr = inet_addr(IPSer);          // REDE LOCAL

    // FAZ A CONEXÃO
    conexao = connect(socketLocal, (struct sockaddr *)&socketAlvo, sizeof(socketAlvo));

    if (!conexao) {
        //PORTA ABERTA
        printf("Parabéns, porta aberta, entre!!!");

        //sendto()
        
        close(socketLocal);
        close(conexao);
    }
    else{
        //PORTA FECHADA
        printf("Porta fechada, mestre");
    }
    printf("Byeee");
}