import socket   
import sys      

# VARIÁVEIS PARA O SOCKET UDP
host = 'localhost'
port = 8080

MAX_MESSAGE_LENGTH = 1024

# TENTA CRIAR O SOCKET UDP
try:
	socket.setdefaulttimeout(1/10)
	socket.timeout
	s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

except socket.error:
	print("Failed to create socket")
	sys.exit()

# ENVIANDO UM PING PARA RECEBER UM PONG
msg = "Ping"

#CODIFICA A MENSAGEM EM ARRAY DE BYTES
msg = bytearray(msg.encode())

#ENVIA O DATAGRAM
s.sendto(msg, (host, port))

MAX_CONN_TRY = 10
num_conn = 0 
conn = False

print('Esperando uma resposta por até 1 segundo')
while num_conn < MAX_CONN_TRY:
	try:
		d = s.recvfrom(MAX_MESSAGE_LENGTH)

		#MENSAGEM RECEBIDA
		reply = d[0]

		print ('Retornaram: ' + str(reply))
		num_conn = 0
		conn = True
		break

	except socket.timeout:
		num_conn = num_conn + 1 
		print("Ninguém retornou !! Tentativa : %i" %num_conn)
		conn = False

if conn:
	print('Finalizando o processo, comunicação bem sucedida')
else:
	print('Finalizando o processo, comunicação sem resposta')

