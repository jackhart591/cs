import socket

HOST = "127.0.0.1"
PORT = 7000

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as sock:
    sock.connect((HOST, PORT))

    while 1:
        msg = input("Message to send:\n")
        sock.send(msg.encode())

        if msg == "/q": # If client is done
            print("Ending chat...")
            break

        recvMsg = sock.recv(1024).decode()

        if recvMsg == "/q":
            print("Server has ended chat...")
            break

        print(recvMsg)