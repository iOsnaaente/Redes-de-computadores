import socket

HOST = ''              # Endereco IP do Servidor
PORT = 5000            # Porta que o Servidor esta

# Criação do socket no protocolo SOCK_DGRAM = UDP 
socket.setdefaulttimeout(1/10)
udp = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

# Definição do ADDR do servidor 
orig = (HOST, PORT)

# Início do Servidor, começa a escutar no endereço orig
udp.bind(orig)

while True:
	
    msg = input("Fale: ")
    msg = msg.encode()

    # Recebe mensagem e addr com a função refvfrom(BUFF_SIZE)
    try:
        msgCli, cliente = udp.recvfrom(1024)
        print(msgCli)

        udp.sendto(msg, cliente)
    except:
        pass

    print()

    print (cliente, msg)

# Encerra o socket 
udp.close()



