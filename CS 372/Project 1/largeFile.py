import socket

HOST = "gaia.cs.umass.edu"
PORT = 80

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as sock:
	sock.connect((HOST, PORT))
	sock.send(b"GET /wireshark-labs/HTTP-wireshark-file3.html HTTP/1.1\r\nHost:gaia.cs.umass.edu\r\n\r\n")

	while True: # Recieves on a loop until there's nothing left
		response = sock.recv(4096)
		
		if len(response.decode()) > 0:
			print(response.decode())
		else:
			break

# Help gotten at https://realpython.com/python-sockets/
