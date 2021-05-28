import htmlReport as hr
import socket

#Server information
SERVER_IP = "54.71.128.194"
SERVER_PORT = 8808

SERVER_INFO = SERVER_IP, SERVER_PORT

#Packets constants.
FIRST_MESSAGE = b"400#USER=almog.maman"
THIRD_MSG = b"900#BYE"

#Technical settings:
PAC_SIZE = 1000
 
def upload_to_the_site():
	"""
	Uploading the html file to the server (not web server, but another server that will do that).
	"""
	with open(hr.REPORT_PATH,"r+") as report_file:
		html = report_file.read() #As str.
		html_size = len(html)
		
		#Socket.
		sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
		
		#Connecting.
		sock.connect(SERVER_INFO)
		
		#Protocol.
		sock.send(FIRST_MESSAGE)
		
		server_ans = sock.recv(PAC_SIZE)
		print(server_ans.decode())
		
		#My second msg.
		second_msg = b"700#SIZE=%d,HTML=%b" % (html_size, html.encode())
		sock.send(second_msg)
		
		server_ans = sock.recv(PAC_SIZE)
		print(server_ans.decode())
		
		#My third msg.
		sock.send(THIRD_MSG)
		
		server_ans = sock.recv(PAC_SIZE)
		print(server_ans.decode() + "\n")
		
		#Closing the socket.
		sock.close()
		
#upload_to_the_site()