import socket

HOST = "gaia.cs.umass.edu"
PORT = 80

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as sock:
	sock.connect((HOST, PORT))
	sock.send(b"GET /wireshark-labs/INTRO-wireshark-file1.html HTTP/1.1\r\nHost:gaia.cs.umass.edu\r\n\r\n")
	response = sock.recv(4096)
	print(response.decode())
