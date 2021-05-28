def print_list(list):
	"""
	Prints the needed parameters for each packet.
	
	:param parameters_list: needed parameters, for each packet in a list.
	"""
	for element in list:
		print(element)
	print("\n\n")

def print_live_packet(packet):
	"""
	Prints a packet in live time.
	
	:param packet: a packet.
	"""
	
	is_udp = UDP in packet
	print("src -> %s, dst -> %s" % (packet[IP].src, packet[IP].dst))
	if is_udp:
		print("src port -> %d, dst port -> %d" % (packet[UDP].sport, packet[UDP].dport))
	else:
		print("src port -> %d, dst port -> %d" % (packet[TCP].sport, packet[TCP].dport))