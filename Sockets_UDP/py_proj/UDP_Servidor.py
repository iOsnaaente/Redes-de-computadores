import socket

# USE UDP_IP = '' TO CATH ALL IPS
# USE UDP_PORT = ARBITRARY NUMBER 
UDP_IP = '127.0.0.1'
UDP_PORT = 8080

# DEFINE THE BUFFER SIZE
BUFFER_SIZE = 1024

# CREATE DE SERVER SOCKET 
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

# INIT THE COMMUNICATION
sock.bind((UDP_IP, UDP_PORT))

flagReceive = False

while True:
    data, addr = sock.recvfrom(BUFFER_SIZE)
    if data != 0 :
        print("Recebido de %s : %s " %(addr, data) )
        flagReceive = True 
    else: 
        flagReceive = False
    
    if flagReceive:
        str_send = bytearray("recebido ;)\n".encode())
        sock.sendto(str_send, addr)

    print (data, addr)


