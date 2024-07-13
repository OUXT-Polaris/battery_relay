import socket
import struct

HOST = '192.168.0.200'
PORT = 2000
BUFSIZE = 4096
FORMAT = 'ascii'
loop_count: int = 0

client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

client.connect((HOST,PORT))

try:
    while True:
        # print("Loop Count : " + str(loop_count))
        client.sendall(struct.pack('<i', loop_count))

        data = client.recv(BUFSIZE)
        print('Return from server')
        print(data.decode(FORMAT))
        loop_count = loop_count + 1
except KeyboardInterrupt:
    client.close()
