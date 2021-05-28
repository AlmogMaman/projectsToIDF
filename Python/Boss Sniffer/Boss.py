import socket
import json
import sys
import os
import Tools
import statisticsFile
import parseSettingsFile as psf
import htmlReport as hr
import uploading as up


BOSS_IP = "127.0.0.1"
BOSS_PORT = 40618
BOSS_INFO = BOSS_IP, BOSS_PORT

MAX_PAC_LEN = 2000000


			
def give_agent_packet():
	"""
	Gives some client's requires parameters from a client packet.
	Returns a client ip, a client data.
	
	:Return type: tuple.
	"""
	
	sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
	
	try:
		sock.bind(BOSS_INFO)
	except Exception:
		print("The port is in another process\n")
		sys.exit()
	
	data, worker_info = sock.recvfrom(MAX_PAC_LEN)
	data = data.decode()
	data_list = json.loads(data)
	client_ip = worker_info[0]
	
	sock.close()
	
	return client_ip, data_list
	
def boss():
	"""
	Comply the Boss sniffer's boss.
	"""
	parsed_settings = [] #The settings that in the settings.dat file.
	all_packets = [] #The packets from the agents.
	statistics = {} #Will be here the most used ip, most used country etc.
	employees_ips = [] #The ips of all the employees.
	while(True):
		parsed_settings = psf.parse_settings_file() #For if the file will be changed in the boss' runtime.
		worker_ip, agent_packet = give_agent_packet()
		
		employees_ips.append(worker_ip) #All of the employees' ips.
		all_packets.append(agent_packet) #All of the employees' packets.
		
		statistics = statisticsFile.create_statistics(all_packets, employees_ips, parsed_settings)
		hr.add_statistics_to_report(statistics, parsed_settings)
		up.upload_to_the_site()
		
	
def main():
	boss()
	
if __name__ == "__main__":
	main()