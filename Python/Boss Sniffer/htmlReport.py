import statisticsFile as sf
from datetime import datetime
import json

REPORT_PATH = r"template/html/Boss Report.html"

#For time line.
UPDATE_TIME_INDEX = 114

#For incoming.
WORKERS_NAMES_INDEX_FOR_INCOMING = 152
WORKERS_VALUES_INDEX_FOR_INCOMING = 156

#For outgoing.
WORKERS_NAMES_INDEX_FOR_OUTGOING = 180
WORKERS_VALUES_INDEX_FOR_OUTGOING = 184

#For countries.
COUNTRIES_NAMES_INDEX = 225
COUNTRIES_VALUES_INDEX = 229

#For ips.
IPS_NAMES_INDEX = 272
IPS_VALUES_INDEX = 276

#For apps.
APPS_NAMES_INDEX = 317
APPS_VALUES_INDEX = 321

#For ports.
PORTS_NAMES_INDEX = 364
PORTS_VALUES_INDEX = 368

#For alerts.
ALERTS_INDEX = 403

def update_time(statistics, html_lines):
	"""
	Updates the updating time of the graph's file.
	
	:Param statistics: the statistics that we did - dict.
	:Param html_lines: the html as lines - list.
	"""
	
	time = str(datetime.now().time())[ : 5] #The current time.
	date = str(datetime.now().date()).replace("-", ".") #The current date (this date is not order in beauty shape).
	day = date[8 : ]
	month = date[5 : 7]
	year = date[ : 4]
	date = day + "." + month + "." + year
	html_lines[UPDATE_TIME_INDEX] = "                        <p>Last update: %s, %s</p>\n" % (date, time)

	return html_lines

def incoming_outgoing_graph(statistics, html_lines, parsed_settings):
	"""
	Updates the incoming/outgoing graph.
	
	:Param statistics: the statistics that we did - dict.
	:Param html_lines: the html as lines - list.
	:Param parsed_settings: the settings in the settings.dat file as list. 
	"""
	incoming_names_bytes = [] #The bytes of each name.
	outgoing_names_bytes = [] #The bytes of each name.
	incoming_names_percentages = [] #The bytes as percentages for each name. 
	outgoing_names_percentages = [] #The bytes as percentages for each name.
	#Init the names.
	names_list = list(parsed_settings[0].values())
	names_list.append("Unknown Worker") #For figure out all of the workers(not just who in the settings.dat file).
	names_list_len = len(names_list)
	
	for name in names_list:
		#Try to take the incoming/outgoing bytes/percentages of a name, if fail, the name is not in the statistic, the incoming/outgoing are 0.
		try:
			#The incoming:
			incoming_name_bytes = statistics[name][sf.INCOMING_BYTES_KEY]
			incoming_name_percentages = statistics[name][sf.INCOMING_BYTES_AS_PERCENTAGES_KEY]
			
			#The outgoing:
			outgoing_name_bytes = statistics[name][sf.OUTGOING_BYTES_KEY]
			outgoing_name_percentages = statistics[name][sf.OUTGOING_BYTES_AS_PERCENTAGES_KEY]
		
		except Exception:
			incoming_name_bytes = 0
			outgoing_name_bytes = 0
			outgoing_name_percentages = "0%"
			incoming_name_percentages = "0%"
			
		#Add to incoming:
		incoming_names_bytes.append(incoming_name_bytes) #The incoming bytes in the order of the names.
		incoming_names_percentages.append(incoming_name_percentages)
		
		#Add to the outgoing:
		outgoing_names_bytes.append(outgoing_name_bytes)#The outgoing bytes in the order of the names.
		outgoing_names_percentages.append(outgoing_name_percentages)
		
		
	#Converts the incoming/outgoing names bytes to strings .  
	incoming_names_bytes = json.dumps(incoming_names_bytes)
	outgoing_names_bytes = json.dumps(outgoing_names_bytes)
	
	
	#Adds the incoming percentages to the names:
	for index in range(names_list_len):
		names_list[index] = names_list[index] + " - %s" % (incoming_names_percentages[index],)
	
	#Updates the incoming traffic graph:
	#The names of the workers.
	names = json.dumps(names_list) #The names of the workers as str-list.
	html_lines[WORKERS_NAMES_INDEX_FOR_INCOMING] = "                            labels: %s,\n" % (names,)
	html_lines[WORKERS_VALUES_INDEX_FOR_INCOMING] = "                                data: %s\n" % (incoming_names_bytes,)
	
	#Removes the incoming percentages to the names:
	for index in range(names_list_len):
		names_list[index] = names_list[index].replace(" - %s" % (incoming_names_percentages[index],), "")
	
	#Adds the outgoing percentages to the names:
	for index in range(names_list_len):
		names_list[index] = names_list[index] + " - %s" % (outgoing_names_percentages[index],)
	
	
	#Updates the outgoing graph:
	#The names of the workers:
	html_lines[WORKERS_NAMES_INDEX_FOR_OUTGOING] = "                            labels: %s,\n" % (names,)
	html_lines[WORKERS_VALUES_INDEX_FOR_OUTGOING] = "                                data: %s\n" % (outgoing_names_bytes,)
	
	
	return html_lines

def most_used_graph(statistics, html_lines, most_used_statistics_key, most_used_names_html_index, most_used_values_html_index):
	"""
	Updates the traffic per most used something (countries, apps, ports, ips).
	
	:Param statistics: the statistics that we did - dict.
	:Param html_lines: the html as lines - list.
	:Param most_used_statistics_key: the key of the most used ips/countries/apps/ports - str.
	:Param most_used_names_html_index: the index of the most used's names (the names of the most used countries/ips...)
	:Param most_used_values_html_index: the index of the most used's values (the values of the most used countries/ips...)
	"""
	most_used_names = [] 
	most_used_values = [] #The values in the order of the names.
	
	for most_used in statistics[most_used_statistics_key]: #The most used is a tuple of the mos used name and the bytes of this most used.
		most_used_name = most_used[0] #Finds the names of the most used.
		most_used_bytes = most_used[1] #Finds the bytes amount of the most used.
		
		#Add to the lists:
		most_used_names.append(most_used_name)
		most_used_values.append(most_used_bytes) #Values are bytes.
		
	#Converts the most used names and values to list-str.
	most_used_values = json.dumps(most_used_values)
	most_used_names = json.dumps(most_used_names)
	
	#Updates the graph.
	#Updates the most used names.
	html_lines[most_used_names_html_index] = "                            labels: %s,\n" % (most_used_names,)
	
	#Updates the most used values.
	html_lines[most_used_values_html_index] = "                                data:  %s\n" % (most_used_values,)
	
	return html_lines

def update_alerts(statistics, html_lines):
	"""
	Updates the alerts.
	
	:Param statistics: the statistics that we did - dict.
	:Param html_lines: the html as lines - list.
	"""
	blacklist = statistics[sf.BLACKLIST_KEY] #The first line is the names line.
	
	
	#Converts the black list to dict-str.
	blacklist = json.dumps(blacklist)
	
	
	#Updates the alerts.
	html_lines[ALERTS_INDEX] = "                 %s\n" % (blacklist,)
	
	return html_lines
	
def add_statistics_to_report(statistics, parsed_settings):
	"""
	Adds the statistics to the html report.
	
	:Param statistics: the statistics that we need to recent the report.
	:Statistics type: dict.
	
	:Param parsed_settings: the settings in the settings.dat file as list. 
	"""
	#Updates the report.
	with open(REPORT_PATH,"r+") as template_file:
		html_lines = template_file.readlines() #The html as lines.
		
		#Updates the time line.
		html_lines = update_time(statistics, html_lines)
		
		#Updates the traffic per incoming/outgoing graph - include percentages to part 3:
		html_lines = incoming_outgoing_graph(statistics, html_lines, parsed_settings)
		
		#Updates the traffic per most used countries graph.
		most_used_graph(statistics, html_lines, sf.MOST_USED_COUNTRIES_KEY, COUNTRIES_NAMES_INDEX, COUNTRIES_VALUES_INDEX)
		
		#Updates the traffic per most used ips graph.
		most_used_graph(statistics, html_lines, sf.MOST_USED_IPS_KEY, IPS_NAMES_INDEX, IPS_VALUES_INDEX)
		
		#Updates the traffic per most used apps graph.
		most_used_graph(statistics, html_lines, sf.MOST_USED_APPS_KEY, APPS_NAMES_INDEX, APPS_VALUES_INDEX)
		
		#Updates the traffic per most used ports graph.
		most_used_graph(statistics, html_lines, sf.MOST_USED_PORTS_KEY, PORTS_NAMES_INDEX, PORTS_VALUES_INDEX)
		
		#Updates the Alerts.
		html_lines = update_alerts(statistics, html_lines)
	
	#Re write the html file.
	with open(REPORT_PATH, "w") as template_file:
		for line in html_lines:
			template_file.write(line)

			
#add_statistics_to_report({'Blacklist Visits': {'twitter': {'127.0.0.1': 'Almog'}, 'Youtube': {'127.0.0.1': 'Almog'}}, 'Most Used Ips': [('34.200.11.75', 1681461), ('185.60.216.19', 1395570), ('157.240.1.38', 233704), ('216.58.206.132', 48119), ('31.13.90.36', 6929)], 'Most Used Countries': [('United States', 2055455), ('Ireland', 1406449), ('Not found', 15693), ('Israel', 17174)], 'Most Used Applications': [('chrome.exe', 3426012), ('Unknown', 40743), ('googledrivesync.exe', 28016)], 'Most Used Ports': [(443, 3470471), (1900, 9398), (80, 2910), (5222, 3805), (53, 1892)], 'Almog': {'Outgoing Bytes': 294371, 'Incoming Bytes': 3200400, 'Incoming Percentages': '100.00%', 'Outgoing Percentages': '100.00%'}, 'Total Incoming': 3200400, 'Total Outgoing': 294371}, [{"213": "Almog", "234234" : "rom"} , {}])
