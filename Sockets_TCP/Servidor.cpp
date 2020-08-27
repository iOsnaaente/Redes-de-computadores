#include <sys/socket.h>
#include <netdb.h>

#define QLEN 10

void erro(char * msg);

int varSocket = socket(PF_INET, SOCK_STREAM, 0);
if (varSocket != 0 )
    erro((char*)"Erro na criação do socket");


struct sockaddr_in my_addr;

my_addr.sin_family      = AF_INET;
my_addr.sin_addr.s_addr = INADDR_ANY;
my_addr.sin_port        = htons(myport);

int varBind =  bind(varSocket, (struct sockaddr *) &my_addr, sizeof(struct sockaddr_in) );
if (varBind != 0 )
    erro((char *)"Erro na criação do bind");

int status = listen(sd, QLEN);
if (status != 0)
    erro((char *)"Erro no listen");



void erro(char * msg){
    perror(msg);
    exit(1);
}
