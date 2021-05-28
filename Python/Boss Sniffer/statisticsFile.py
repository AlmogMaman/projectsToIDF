import Tools

MOST_USED_SUM = 5 #The number of the most used statistic thing (ip\country\apps).

#The statistics keys:
MOST_USED_IPS_KEY = "Most Used Ips"
MOST_USED_COUNTRIES_KEY = "Most Used Countries"
MOST_USED_APPS_KEY = "Most Used Applications"
MOST_USED_PORTS_KEY = "Most Used Ports"
TOTAL_INCOMING_LEN_KEY = "Total Incoming"
TOTAL_OUTGOING_LEN_KEY = "Total Outgoing"
BLACKLIST_KEY = "Blacklist Visits"


#The packet keys:
IP_KEY_OF_PACKET = "Second Side Ip"
COUNTRIE_KEY_OF_PACKET = "Second Side Country"
APP_KEY_OF_PACKET = "Application"
PORT_KEY_OF_PACKET = "Second Side Port"
RECEIVED_PACKET_KEY_OF_PACKET = "Received Packet"
LEN_KEY_OF_PACKET = "Total Packet Len"

#worker keys - for every signal worker has a field for himself in the statistics dict.
#This field is a dict, every signal fields in this dict is cold 'worker key'
INCOMING_BYTES_KEY = "Incoming Bytes"
OUTGOING_BYTES_KEY = "Outgoing Bytes"
INCOMING_BYTES_AS_PERCENTAGES_KEY = "Incoming Percentages"
OUTGOING_BYTES_AS_PERCENTAGES_KEY = "Outgoing Percentages"

#Constants of the most used things:
AMOUNT_KEY = "Amount"
SUM_KEY = "Bytes Sum"

#Another constants
DICT_TYPE = type({})

statistics = {} #Will be here the most used ip, most used country etc.

def count_and_sum_field_values_in_all_packets(all_packets, packet_key):
	"""
	Counts how many times a value in a packet filed appears in all of the packets.
	And sums the bytes of each field's value.
	Return a temp dict with the values, and the number of them.
	
	:param all_packets: all of the packets that received to the boss.
	:all_packets type: list.
	
	:param packet_key: key of the field that we want count its values.
	:packet_key type: str.
	
	:Return type: dict.
	"""
	statistic_dict = {}
	# counts how many times each statistic thing appears in hole packets(of all agents).
	# The counting is starting from 1
	#print(all_packets)
	for agent_packet in all_packets: #Run on the all packets, from all agents.
		for sniffed_pac_dict in agent_packet:
			for pac_item in sniffed_pac_dict.items(): #Runs on each packet in an agent packet.
				key = pac_item[0]
				value = pac_item[1]
				
				if key == packet_key:
					try:
						statistic_dict[value][AMOUNT_KEY] += 1 #The value is an statistic thing
						try:
							statistic_dict[value][SUM_KEY] += sniffed_pac_dict[LEN_KEY_OF_PACKET]
						except Exception:
							statistic_dict[value][SUM_KEY] = sniffed_pac_dict[LEN_KEY_OF_PACKET]
					except Exception:
						try:
							statistic_dict[value][AMOUNT_KEY] = 1
						except Exception:
							statistic_dict[value] = {}
							statistic_dict[value][AMOUNT_KEY] = 1
							statistic_dict[value][SUM_KEY] = sniffed_pac_dict[LEN_KEY_OF_PACKET]
							
							
	#print(statistic_dict)			
	return statistic_dict

def find_counters(statistic_dict):
	"""
	Finds the counters of a statistic dict.
	Returns the counters of each value, as list.
	
	:Param statistic_dict: a dist with the amount and counters of a statistic thing.
	"""
	counters_list = []
	for value in statistic_dict.values(): #Value is a dict of amount and bytes' sum.
		counter = value[AMOUNT_KEY]
		counters_list.append(counter)
		
	return counters_list
	
def find_and_update_the_most_used(statistic_dict, statistic_key):
	"""
	Finds the most used statistic thing (statistic thing is the values that we want to find
	the most used off (like ips\countries\apps)).
	The function finds the most used statistic thing, and updates it's to the statistics dict.
	
	:param statistic_dict: the dictionary with the statistic data (the name of the ips\countries\apps and how times each one appears)
	:statistic_dict type: dict.
	
	:param statistic_key: a key of the statistic object.
	:statistic_key type: str.
	"""
	global statistics
	#print(statistic_dict)
	# Finds the most used statistic thing, and updates it - according to a constants.
	for time in range(MOST_USED_SUM):
		if list(statistic_dict.values()) != []: #If the tmep dict is not empty.
			counters_list = find_counters(statistic_dict)#The counters of each ip or app etc...
			max_value = max(counters_list)
			
			for item in statistic_dict.items(): #Item is a dict.
				key = item[0] #Ip or app or port or countrie.
				value = item[1] #Dict of amount and bytes sum.
				#print(value)
				#print(item)
				if value[AMOUNT_KEY] == max_value: #If the amount of the current statistic thing (ip, app etc) is the most used.
					most_used = key
					statistics[statistic_key].append((key, value[SUM_KEY])) #Adds the ip or country etc, and the bytes' sum.
					break
			
			del statistic_dict[most_used] #For find the next used statistic thing.
		else:
			break

def most_used_statistics(all_packets, statistic_key, packet_key):
	"""
	Comply the statistics for the most used things (like apps\ips\countries).
	
	:Param all_packets: the stack of the packet (all of the received packets till now).
	:all_packets type: list.
	
	:param statistic_key: key of the statistic dict.
	:statistic_key type: str.
	
	:param packet_key: key of the statistic thing that we want (like: key of ip, country, app)
	:packet_key type: str.
	"""
	global statistics
	statistics[statistic_key] = [] #For each statistic.
	statistic_dict = {} #Contains statistic things in the same type, and how many times each statistic is appearing (for all of the packets that the boss received).
	
	
	statistic_dict = count_and_sum_field_values_in_all_packets(all_packets, packet_key)
	#print(statistic_dict)
	find_and_update_the_most_used(statistic_dict, statistic_key)
	
	#Tools.print_list(statistics[statistic_key])

def find_worker_name(worker_ip, parsed_settings):
	"""
	Finds a worker's name according to a worker's ip.
	Returns the worker's name.
	
	:Param worker_ip: a worker's ip - str.
	:Param parsed_settings: the settings in the settings.dat file as a dict inside list.
	:Return type: str.
	"""
	try: #Try to find the worker name.
		worker_name = parsed_settings[0][worker_ip] #The first setting line is the names' line.
	except Exception: #If the user is not exist in the settings.dat file. 
		worker_name = "Unknown Worker"
	
	return worker_name
	
def traffic_statistics(all_packets,employees_ips, parsed_settings):
	"""
	Recent the number of incoming/outgoing bytes of a worker.
	If the worker is not in the settings.dat file the name is going to be Unknown worker.
	
	:Param all_packets: the stack of the packet (all of the received packets till now).
	:all_packets type: list.
	
	:Param employees_ips: the ips of all the of the employees.
	:worker_info type: lst.
	
	:Param parsed_settings: the settings in the settings.dat file as list.
	:Parsed_settings type: list.
	"""
	employee_index = 0
	for agent_packet in all_packets:
		employee_ip = employees_ips[employee_index] #Ip of the current employee.
		worker_name = find_worker_name(employee_ip, parsed_settings)
		for single_sniffed_packet in agent_packet:
			if single_sniffed_packet[RECEIVED_PACKET_KEY_OF_PACKET] == 1: #If the packet has received.
				try: #Try to add the packet len to the incoming filed of the worker.
					statistics[worker_name][INCOMING_BYTES_KEY] += single_sniffed_packet[LEN_KEY_OF_PACKET]
				except Exception: #If the incoming field has not created or has created, but we can not add to nothing, we are creating this field with the packet len or init this field..
					try:
						statistics[worker_name][INCOMING_BYTES_KEY] = single_sniffed_packet[LEN_KEY_OF_PACKET]
					except Exception:
						statistics[worker_name] = {}
						statistics[worker_name][INCOMING_BYTES_KEY] = single_sniffed_packet[LEN_KEY_OF_PACKET]
				
			else: #If the packet has not received - the packet has sent.
				try: #Try to add the packet len to the outgoing filed of the worker.
					statistics[worker_name][OUTGOING_BYTES_KEY] += single_sniffed_packet[LEN_KEY_OF_PACKET]
				except Exception: #If the outgoing field has not created or has created, but we can not add to nothing, we are creating this field with the packet len or init this field..
					try:
						statistics[worker_name][OUTGOING_BYTES_KEY] = single_sniffed_packet[LEN_KEY_OF_PACKET]
					except Exception:
						statistics[worker_name] = {}
						statistics[worker_name][OUTGOING_BYTES_KEY] = single_sniffed_packet[LEN_KEY_OF_PACKET]
		
		employee_index += 1
		
def add_total_incoming_outgoing_bytes_fields(all_packets):
	"""
	Adds the fields that contain the incoming/outgoing bytes sum.
	
	:Param all_packets: all of the packets that have sent to the boss.
	:all_packets type: list.
	"""
	incoming_len = 0 #For all packet.
	outgoing_len = 0 #For all packet.
	
	#Init the len of the incoming/outgoing len (for all of the packets). 
	for agent_packet in all_packets:
		for single_sniffed_packet in agent_packet:
			if single_sniffed_packet[RECEIVED_PACKET_KEY_OF_PACKET] == 1:
				incoming_len += single_sniffed_packet[LEN_KEY_OF_PACKET]
			else:
				outgoing_len += single_sniffed_packet[LEN_KEY_OF_PACKET]
	
	
	#Init the statistucs field.
	statistics[TOTAL_INCOMING_LEN_KEY] = incoming_len
	statistics[TOTAL_OUTGOING_LEN_KEY] = outgoing_len	
		
def traffic_statistics_as_persentages():
	"""
	Recent the number of incoming/outgoing bytes of a worker as percentage.
	The len of the incoming/outgoing len is going to be adds too (to the statistics).
	"""
	one_incoming_percent = (statistics[TOTAL_INCOMING_LEN_KEY] / 100) #Of total len.
	one_outgoing_percent = (statistics[TOTAL_OUTGOING_LEN_KEY] / 100) #Of total len.
	
	for item in statistics.items():
		key = item[0]
		value = item[1]
		
		if type(value) == DICT_TYPE and INCOMING_BYTES_KEY in value: #If the key is a worker.
			#Calculates each incoming/outgoing traffic for each worker. 
			incoming_of_worker = value[INCOMING_BYTES_KEY]
			outgoing_of_worker = value[OUTGOING_BYTES_KEY]
			
			incoming_percentage_of_worker = "%0.2f" % (incoming_of_worker / one_incoming_percent,)
			outgoing_percentage_of_worker = "%0.2f" % (outgoing_of_worker / one_outgoing_percent,)
			
			#Adds the % symbol.
			incoming_percentage_of_worker = incoming_percentage_of_worker + "%"
			outgoing_percentage_of_worker = outgoing_percentage_of_worker + "%"
			
			#Adds the percentages for each worker.
			statistics[key][INCOMING_BYTES_AS_PERCENTAGES_KEY] = incoming_percentage_of_worker
			statistics[key][OUTGOING_BYTES_AS_PERCENTAGES_KEY] = outgoing_percentage_of_worker
	
def blacklist_statistic(all_packets, employees_ips, parsed_settings):
	"""
	Adds black visits to the blacklist field.
	The field is a dict that contains the worker ip and worker name.
	
	example:
	Blacklist: {facebook: {worker_ip : worker_name}, twitter : {worker_ip : worker_name}}.
	
	:Param all_packets: the stack of the packet (all of the received packets till now).
	:all_packets type: list.
	
	:Param employees_ips: the ips of all the of the employees.
	:worker_info type: lst.
	
	:Param parsed_settings: the settings in the settings.dat file as list.
	:Parsed_settings type: list.
	"""
	employee_index = 0 #Index of each employee.
	blacklist_dict = parsed_settings[1] #The black list as dict.
	
	for agent_packet in all_packets: #Runs on the agents' packets.
		employee_ip = employees_ips[employee_index] #Find the ip of the current employee.
		worker_name = find_worker_name(employee_ip, parsed_settings) #Finds the name for the current employee.
		for single_sniffed_packet in agent_packet: #Runs on every single sniffed packet for each employee. 
			if single_sniffed_packet[IP_KEY_OF_PACKET] in blacklist_dict: #If a sniffed packet has visited in a blacklist' site.
				blacklist_ip = single_sniffed_packet[IP_KEY_OF_PACKET] #Saves the ip of the blacklist's site.
				black_site = blacklist_dict[blacklist_ip] #Saves the blacklist sites' name.
				try: #Try to add the ip/name to the black site.
					statistics[BLACKLIST_KEY][black_site][employee_ip] = worker_name #Adds the worker ip/name to the statistics (like the ex above).
				except Exception: #If this is the first add to a black site.
					statistics[BLACKLIST_KEY][black_site] = {}
					statistics[BLACKLIST_KEY][black_site][employee_ip] = worker_name
		
		employee_index += 1

def create_statistics(all_packets, employees_ips, parsed_settings):
	"""
	Creates the agents' statistics.
	Returns the statistics.
	
	:Param all_packets: the stack of the packet (all of the received packets till now).
	:all_packets type: list.
	
	:Param employees_ips: the ips of all the of the employees.
	:worker_info type: lst.
	
	:Param parsed_settings: the settings in the settings.dat file as list.
	:Parsed_settings type: list.
	
	:Return type: list.
	"""
	global statistics
	statistics = {} #For each iteration - each round.
	statistics[BLACKLIST_KEY] = {}
	
	#For ips.
	most_used_statistics(all_packets, MOST_USED_IPS_KEY, IP_KEY_OF_PACKET)
	
	#For countries.
	most_used_statistics(all_packets, MOST_USED_COUNTRIES_KEY, COUNTRIE_KEY_OF_PACKET)
	
	#For applications.
	most_used_statistics(all_packets, MOST_USED_APPS_KEY, APP_KEY_OF_PACKET)
	
	#For ports.
	most_used_statistics(all_packets, MOST_USED_PORTS_KEY, PORT_KEY_OF_PACKET)
	
	#For the traffic statistics - the incoming and outgoing traffic.
	traffic_statistics(all_packets,employees_ips, parsed_settings)
	
	#Adds the fields that contain the incoming/outgoing bytes sum.
	add_total_incoming_outgoing_bytes_fields(all_packets)
	
	#For the traffic statistics - the incoming and outgoing traffic as percentages.
	traffic_statistics_as_persentages() #The expansion of part 3.
	
	#Adds the visits to the black list sites, for each worker.
	blacklist_statistic(all_packets, employees_ips, parsed_settings)
	
	
	print(statistics)
	print("\n\n")
	
	
	return statistics