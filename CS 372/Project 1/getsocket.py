import socket

HOST = "gaia.cs.umass.edu"
PORT = 80

# Creates socket using TCP connection
with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as sock:
	sock.connect((HOST, PORT)) # Connects to gaia... on port 80
	sock.send(b"GET /wireshark-labs/INTRO-wireshark-file1.html HTTP/1.1\r\nHost:gaia.cs.umass.edu\r\n\r\n") # Sends request for webpage
	response = sock.recv(4096) # waits for response
	print(response.decode()) # decodes from bytes into text

# Help gotten at https://realpython.com/python-sockets/
