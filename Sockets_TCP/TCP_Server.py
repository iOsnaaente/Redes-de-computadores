from threading import Thread, Lock 
import socket
import time 

class Server_TCP:

    HOST    = '127.0.0.1'     # IP address 
    PORT    = 5000            # Port where the server is connected
    TIMEOUT = 1               # Timeout in seconds 
    BUFF    = 1024            # Buffer to receive n bytes

    tcp = 0 
    server_addr = 0 
    connection = True 

    def __init__(self, HOST, IP, timeout = 0, num_listening = 1):
        
        self.HOST     = HOST
        self.IP       = IP  
        self.TIMEOUT  = timeout
        self.BUFF     = 1024

        # Cria o socket TCP 
        self.tcp = socket.socket( socket.AF_INET, socket.SOCK_STREAM )

        if self.TIMEOUT:                        # Seta o Timeout para bloqueante ou não bloqueante 
            self.tcp.settimeout( self.TIMEOUT ) # Timeout garante que a conexão irá durar esse tempo

        self.server_addr = (HOST, IP)           # Cria a tupla addr do server

        self.tcp.bind( self.server_addr )       # Inicia o servidor 
        self.tcp.listen( num_listening )        # Backlog de conexões simultaneas 

        self.clients = []                       # Lista de clientes conectados
    

    # Método para conectar novos clientes 
    def connect_client ( self ):
        try: 
            client_conn, client_addr = self.tcp.accept()
            # Todo novo cliente vai para a lista de novos clientes conectados 
            self.clients.append( (client_conn, client_addr) )
            return self.clients[-1]
        except:
            return None   
        

    # Retorna a lista de clientes conectados. 
    def get_clients_connected(self):
        return self.clients


    """ Para mandar uma mensagem TCP usar o método abaixo.
        Padrão usar mensagens str.encode() ou str. 
    """
    def send_message( self, msg, client ):
        with client : 
            # Garante que a mensagem esteja codificada
            if type(msg) is str:
                msg = msg.encode()
            elif type(msg) is not bytes:
                print("Dados fora do padrão de envio TCP != str or bytes")

            self.tcp.send( msg )


    """ Método para receber uma mensagem.
        Lembrar do timeout (segundos).
    """
    def receive_message(self, client, show_msg = False ):
        try:
            msg = client.recvfrom( self.BUFF )
            if show_msg:
                print( "Receive : ", msg )
            return msg

        except socket.timeout as err :
            if show_msg:
                print( "Receive ", err )
            return None 


    """ setar o tamanho máximo do buffer.
    """
    def set_buffer(self, buff):
        self.BUFF = buff 


    """
        Setar o timeout da conexão.
    """
    def set_timeout(self, timeout):
        self.TIMEOUT = timeout
        self.tcp.settimeout( self.TIMEOUT )


    """ Encerrar a conexão TCP.
    """
    def close_connection(self):
        self.tcp.close()