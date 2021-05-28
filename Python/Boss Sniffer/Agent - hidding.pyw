from scapy.all import*
import requests
import socket
import findIps
import json
import Tools
import os

BOSS_IP = "127.0.0.1"
BOSS_PORT = 40618	
BOSS_INFO = BOSS_IP, BOSS_PORT
ENTER = "\n"
OPEN_BRAEKT = "["
CLOSE_BRAEKT = "]"
MY_IP = findIps.get_my_address()
ROUND_PAC_SUM = 350

#Packet keys:
IP_KEY = "Second Side Ip"
PORT_KEY = "Second Side Port"
RECEIVED_PACKET_KEY_OF_PACKET = "Received Packet"
COUNTRY_KEY = "Second Side Country"
LEN_KEY = "Total Packet Len"
APP_KEY = "Application"

#Cmd commands.
FINDING_APPLICATION_COMMAND = "netstat -nb"


ips_countries_dict = {} #Dictionary of the passed Ips and them countries.


def is_udp_or_tcp_pac(pac):
	"""
	A filter function.
	Checks if a packet is a tcp or udp packet.
	Returns true for yes, and false for no.
	
	:param pac: a pac.
	:pac type: could to change.
	:Return type: boolean.
	"""
	return IP in pac and (UDP in pac or TCP in pac)

def find_app_name_index(MY_IP, application_port, netstat_nb):
	"""
	Finds the first application's name index that sent or received the packet.
	Returns the first application's name index.
	
	:param MY_IP: my local ip.
	:Param application_port: the port of the application that sent or received the packet.
	:Param netstat_nb: Windows operation system action.
	
	:MY_IP type: str.
	:application_port type: int.
	:netstat_nb type: str.
	
	:Return type: int.
	"""
	#The start of the application's record index. (record like: 10.0.0.3:4434      1.2.3.4:443 etc)
	start_raw_index = netstat_nb.find("%s:%s" % (MY_IP, str(application_port)))
	is_unknown = False #Is the application unknown.
	is_application = False #Is the application is known.
	raw_and_beyond = netstat_nb[start_raw_index: ] #The application raw until the end of the netstat.
	enter_counter = 0 #Counts the enters than the application raw and beyond.
	curr_index = start_raw_index
	
	if start_raw_index != -1: #If the application is in the netstat's records.
		#Finds the index of the first application's name index:
		while(not is_unknown and not is_application):
			chara = netstat_nb[curr_index]
			if chara == ENTER:
				enter_counter += 1
			if enter_counter > 1: #If the application info is not under the packet info, for each packet.
				is_unknown = True
				
			elif chara == OPEN_BRAEKT:
				is_application = True
			
			curr_index += 1
		
	if is_application:
		first_app_name_index = curr_index
	else:
		first_app_name_index = None
		
	return first_app_name_index
	
def find_app_name(first_app_name_index, netstat_nb):
	"""
	Finds the application's name that sent or received the packet.
	Returns application's name.
	
	:Param first_app_name_index: the index of the start application's name.
	:Param netstat_nb: Windows operation system action.
	
	:first_app_name_index type: int.
	:netstat_nb type: str.
	
	:Return type: str.
	"""
	app_name_and_beyond_len = len(netstat_nb[first_app_name_index :]) #The len of the app's name and all of the netstat stuff after the app's name.  
	app_name = ""
	
	for relative_index in range(app_name_and_beyond_len):
		app_char_index = first_app_name_index + relative_index #The index started from 0 until the len - 1
		app_char = netstat_nb[app_char_index]
		if app_char != CLOSE_BRAEKT:
			app_name += app_char
		else:
			break
			
	return app_name
	
def find_app(MY_IP, application_port, netstat_nb):
	"""
	Finds the application that sent or received the packet.
	Returns the application name.
	
	:param MY_IP: my local ip.
	:Param application_port: the port of the application that sent or received the packet.
	:Param netstat_nb: Windows operation system action.
	
	:MY_IP type: str.
	:application_port type: int.
	:netstat_nb type: str.
	
	:Return type: str.
	"""
	
	first_app_name_index = find_app_name_index(MY_IP, application_port, netstat_nb) #Finds the first app name index.
	
	if first_app_name_index != None:
		application_name = find_app_name(first_app_name_index, netstat_nb)	
	else:
		application_name = "Unknown"
	
	return application_name
	
def create_needed_parameters_list(packets):
	"""
	Creates parameters the need to be in the agent's packet, for each pac.
	Returns a list of dictionaries, every dictionary is needed parameters for pac.
	
	:param packets: the sniffed packets.
	:packets type: list.
	:Return type: list.
	"""
	global ips_countries_dict
	needed_parameters_list = []
	current_dict = {} #Dictionary of current needed parameters.
	netstat_nb = os.popen(FINDING_APPLICATION_COMMAND).read()
	
	for pac in packets:
		is_udp_pac = UDP in pac #Checks if it a udp or tcp pac
		
		#Init the dict without the country field, the len field, the application field:
		#Received packet:
		if MY_IP == pac[IP].dst:
			current_dict[IP_KEY] = pac[IP].src
			current_dict[RECEIVED_PACKET_KEY_OF_PACKET] = 1
			if is_udp_pac:
				current_dict[PORT_KEY] = pac[UDP].sport
				application_port = pac[UDP].dport
			else:
				current_dict[PORT_KEY] = pac[TCP].sport
				application_port = pac[TCP].dport
		
		#Exit packet - I sent the packet:
		else:
			current_dict[IP_KEY] = pac[IP].dst
			current_dict[RECEIVED_PACKET_KEY_OF_PACKET] = 0
			if is_udp_pac:
				current_dict[PORT_KEY] = pac[UDP].dport
				application_port = pac[UDP].sport
			else:
				current_dict[PORT_KEY] = pac[TCP].dport
				application_port = pac[TCP].sport
				
		#Finds the pac len.
		current_dict[LEN_KEY] = pac[IP].len
		
		#Finds country by ip, and recent the 'cash' dict.
		current_dict[COUNTRY_KEY], ips_countries_dict = findIps.find_country_by_ip(current_dict["Second Side Ip"], ips_countries_dict) #Finds the country.
		
		#Finds the application on my PC:
		current_dict[APP_KEY] = find_app(MY_IP, application_port, netstat_nb)
		
		needed_parameters_list.append(current_dict)
		
		current_dict = {} #For each packet.
		
	return needed_parameters_list

def sned_to_boss(round_needed_parameters_list):
	"""
	Sends the needed parameters for each round to the boss.
	
	:param round_needed_parameters_list: the needed parameters for a round.
	:round_needed_parameters_list type: list.
	"""
	sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
	data = json.dumps(round_needed_parameters_list).encode()
	
	sock.sendto(data, BOSS_INFO)
	
	sock.close()

def agent():
	"""
	Comply the Boss Sniffer's agent.
	"""
	while(True):
		print("Im working")
		round_needed_parameters_list = [] #For each round
		packets = sniff(count = ROUND_PAC_SUM, lfilter = is_udp_or_tcp_pac)#Sniff till ROUND_PAC_SUM value, a packet with udp or tcp layer.
		round_needed_parameters_list = create_needed_parameters_list(packets)
		## Tools.print_list(round_needed_parameters_list)
		sned_to_boss(round_needed_parameters_list)
		
def main():
	agent()
	
if __name__ == "__main__":
	main()