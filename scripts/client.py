import socket

HOST = '192.168.0.210'
PORT = 8080
BUFSIZE = 4096
FORMAT = 'ascii'

client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

client.connect((HOST,PORT))

try:
    while True:
        msg = input('Hello.')
        client.sendall(msg.encode(FORMAT))

        data = client.recv(BUFSIZE)
        print('Return from server')
        print(data.decode(FORMAT))
except KeyboardInterrupt:
    client.close()