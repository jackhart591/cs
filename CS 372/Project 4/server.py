import socket

HOST = "localhost"
PORT = 8123

# Used echo client/server example from this website:
# https://realpython.com/python-sockets/#echo-server
with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as sock:
    sock.bind((HOST, PORT))
    sock.listen()
    conn, addr = sock.accept()
    with conn:
        while 1:
            recvMsg = conn.recv(1024).decode() # Look for client message
            print(recvMsg)

            if recvMsg == "/q": # If client is done
                print("Client has ended chat...")
                break

            msg = input("Message to send:\n") # Send our own message back
            conn.send(msg.encode())

            if msg == "/q": # If server is done
                print("Ending chat...")
                break