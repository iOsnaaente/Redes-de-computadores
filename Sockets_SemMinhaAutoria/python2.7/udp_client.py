import socket

sock = socket.socket(socket.AF_INET,
                                    socket.SOCK_DGRAM)

UDP_IP = '127.0.0.1'
UDP_PORT = 1123

count = 0

while True:
    MESSAGE = str(count)
    count += 1
    sock.sendto(MESSAGE, (UDP_IP, UDP_PORT))