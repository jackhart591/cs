import socket

HOST = "localhost"
PORT = 8123

# Used echo client/server example from this website:
# https://realpython.com/python-sockets/#echo-server
with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as sock:
    sock.connect((HOST, PORT))

    while 1:
        msg = input("Message to send:")
        sock.send(msg.encode())

        if msg == "/q": # If client is done
            print("Ending chat...")
            break

        recvMsg = sock.recv(1024).decode() # Get message back

        if recvMsg == "/q": # If the server is done
            print("Server has ended chat...")
            break

        print(recvMsg)