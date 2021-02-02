import socket
import struct
import time 
import sys 

HOST = '25.90.190.66'  # Endereco IP do Servidor
PORT = 5000            # Porta que o Servidor esta

# Criação do socket no protocolo SOCK_DGRAM = UDP 
socket.setdefaulttimeout(1/10)
udp = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

# Definição do ADDR do servidor 
dest = (HOST, PORT)


while True:

    # Variável da mensagem a ser transmitida 
    msg = input("Fale: ")
    msg = msg.encode()
    
    # Envia a mensagem para o endereço do servidor
    udp.sendto (msg, dest)
    try:
        msgRec, addr = udp.recvfrom(1204)
        print(msgRec)
    except:
        pass



# Encerra o Socket
udp.close()


