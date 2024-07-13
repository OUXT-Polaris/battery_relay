import socket
import time
import struct

HOST = '192.168.0.200'
PORT = 2000
BUFSIZE = 4096
FORMAT = 'ascii'

client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

client.connect((HOST,PORT))

try:
    while True:
        client.sendall(struct.pack('<f', time.time()))

        data = client.recv(BUFSIZE)
        print('Return from server')
        print(data.decode(FORMAT))
except KeyboardInterrupt:
    client.close()
