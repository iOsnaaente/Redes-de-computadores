import socket   
import sys      


host = 'localhost'
port = 8080

MAX_MESSAGE_LENGTH = 1024

# TENTA CRIAR O SOCKET UDP - SEMELHANTE AO DE CPP
try:
    s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

except socket.error:
    print("Failed to create socket")
    sys.exit()


def sendAndListening(msg):

    #CODIFICA A MENSAGEM EM ARRAY DE BYTES
    msg = bytearray(msg.encode())

    #ENVIA A SOLICITAÇÃO
    s.sendto(msg, (host, port))

    #AGUARDA A RESPOSTA
    d = s.recvfrom(MAX_MESSAGE_LENGTH)

    #MENSAGEM RECEBIDA
    reply = d[0]

    print ('Servidor retornou: ' + str(reply))
    return reply


if __name__ == "__main__":

    intState  = 1
    floatAng  = 180.0101010
    floatTime = 2.24
    while True:
        strMsg = str(intState) + ':' + str(floatAng) + ':' + str(floatTime) + '\n'

    reply = sendAndListening(strMsg)

