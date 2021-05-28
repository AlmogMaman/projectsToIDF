COMMA = ","
SPACE = " "
COLON = ":"
SETTINGS_FILE_LOCATION = r"settings.dat"

def parse_settings_file():
	"""
	Parsed the settings.dat file.
	Returns the parsed file as list that inside this list has dictionaries.
	Each dictionary symbols a line in the settings.dat file.
	
	:Return type: list.
	:list cells type: each one is a dict.
	
	"""
	parsed_settings = []
	
	with open(SETTINGS_FILE_LOCATION, "r") as settings_file:
		setting_line_dict = {} #Dict of the current setting (workers or block-list)
		file_lines = settings_file.readlines()
		lines_len = len(file_lines)
		settings_lines_counter = 1 #Counts how many settings lines have in the file.
		
		#Removes the \n from each line in the file, each index contains the line without newline.
		for index in range(lines_len):
			file_lines[index] = file_lines[index][ : -1] #Not include the \n at the end...
		
		for setting_line in file_lines: #Running on each setting line.
			
			#Splits the the current setting line to list.
			splited_setting_line = setting_line.split(COMMA)
			splited_setting_line[0] = splited_setting_line[0].split(SPACE)[2] #For do not reference to the not relevant data. ("WORKER = " or "BLACKLIST = ")
			
			#Adds the current parsed setting line to the parsed settings object.
			for setting in splited_setting_line:
				setting = setting.split(COLON)
				key = setting[0] #The worker name or the ip of the blocked site.
				value = setting[1] #The worker ip or the name of the blocked site.
				
				if settings_lines_counter == 1: #The first line - the line with the names. 
					setting_line_dict[value] = key
				else:
					setting_line_dict[key] = value
			
			settings_lines_counter += 1
			parsed_settings.append(setting_line_dict)
			setting_line_dict = {} #For each setting.
			
	return parsed_settings
	
# print(parse_settings_file())