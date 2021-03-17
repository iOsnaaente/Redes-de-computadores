import socket

class Client_TCP:

    # MACRO
    HOST    = 'localhost'     # IP address 
    PORT    = 5000            # Port where the server is connected
    TIMEOUT = 1               # Timeout in seconds 
    BUFF    = 1024            # Buffer to receive n bytes 
    
    # VAR
    connection  = True
    server_addr = 0  
    tcp         = 0 

    def __init__(self, IP, PORT, server = False, timeout = 0, num_listening = 1 ):

        self.TIMEOUT  = timeout
        self.PORT     = PORT  
        self.BUFF     = 1024
        self.HOST     = IP

        self.server   = server 
        self.isAlive  = False 

        # Cria o socket TCP 
        self.tcp = socket.socket( socket.AF_INET, socket.SOCK_STREAM )

        if self.TIMEOUT:                        # Seta o Timeout para bloqueante ou não bloqueante 
            self.tcp.settimeout( self.TIMEOUT ) # Timeout garante que a conexão irá durar esse tempo

        if server:
            self.server_addr = (HOST, PORT)           # Cria a tupla addr do server
            self.tcp.bind( self.server_addr )       # Inicia o servidor 
            self.tcp.listen( num_listening )        # Backlog de conexões simultaneas 
            self.clients = []                       # Lista de clientes conectados
        else:
            self.server_addr = (HOST, PORT)           # Cria a tupla addr do server
            self.connect_server()                   # Chama o método de conexão do servidor


    ##  CLIENTE FUNCTIONS 
    """ Para se conectar em um servidor                                                  
    """
    def connect_server ( self ):
        if not self.server: 
            try: 
                # Conecta no servidor no host e ip passados
                self.tcp.connect( self.server_addr )
                print("Conectado com ", self.server_addr )
                self.isAlive = True 
            except:
                print("Falha para conectar no servidor : ", self.server_addr, " Chame novamente o método connect_server mais tarde" ) 
                self.isAlive = False 
        else: 
            print("Função exclusiva do lado cliente")

    # Método para conectar novos clientes 
    def connect_client ( self ):
        if self.server:
            try: 
                client_conn, client_addr = self.tcp.accept()
                # Todo novo cliente vai para a lista de novos clientes conectados 
                self.clients.append( (client_conn, client_addr) )
                return self.clients[-1]
            except:
                return None   
        else:
            print('Função exclusiva para servidor')

    # Retorna a lista de clientes conectados. 
    def get_clients_connected(self):
        if self.server:
            return self.clients


    """ Para mandar uma mensagem TCP usar o método abaixo.
        Padrão usar mensagens str.encode() ou str. 
    """
    def send_message( self, msg, client = 0 ):
        if self.server and client != 0:
            with client : 
                # Garante que a mensagem esteja codificada
                if type(msg) is str:
                    msg = msg.encode()
                elif type(msg) is not bytes:
                    print("Dados fora do padrão de envio TCP != str or bytes")
                self.tcp.send( msg )
        elif not self.server:
            # Garante que a mensagem esteja codificada
            if type(msg) is str:
                msg = msg.encode()
            elif type(msg) is not bytes:
                print("Dados fora do padrão de envio TCP != str or bytes")
            self.tcp.sendto( msg, self.server_addr )
        else:
            print('Para enviar mensagens ao cliente, passe a conexão como parametro de client')


    """ Método para receber uma mensagem.
        Lembrar do timeout (segundos).
    """
    def receive_message(self, client = 0, show_msg = False):
        if self.server:
            try:
                msg = client.recvfrom( self.BUFF )
                if show_msg:
                    print( "Receive : ", msg )
                return msg
            except socket.timeout as err :
                if show_msg:
                    print( "Receive ", err )
                return None 
        else: 
            try:
                msg = self.tcp.recvfrom( self.BUFF ) 
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