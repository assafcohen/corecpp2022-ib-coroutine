import socket
import sys

HOST = "127.0.0.1"  # The server's hostname or IP address
PORT = 2022  # The port used by the server

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as conn:
    conn.connect((HOST, PORT))
    filename: str = 'C:\\Program Files\\JetBrains\\CLion 2022.1.1\\bin\\clion.ico'
    conn.send(filename.encode())
    size = conn.recv(4)
    fileSize = int.from_bytes(size, sys.byteorder)
    print(fileSize)
    with open("received", "wb") as file:
        while True:
            data = conn.recv(16384)
            if data:
                file.write(data)
                continue
            break
