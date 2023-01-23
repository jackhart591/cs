import socket

HOST = "localhost"
PORT = 8000

PAGE_DATA = "HTTP/1.1 200 OK\r\n\"Content-Type: text/html; charset=UTF-8\r\n\r\n<html>Congratulations! You've downloaded the first Wireshark lab file!</html>\r\n"

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as sock:
	sock.bind((HOST, PORT))
	sock.listen()
	conn, addr = sock.accept()

	with conn:
		print(f"Connected by {addr}")
		
		data = conn.recv(1024)
		print(data.decode())

		conn.send(bytes(PAGE_DATA, 'utf-8'))
