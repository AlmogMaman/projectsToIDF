import socket
import requests
import sys


GEOIP_URL = "http://www.geoipview.com"

START_COUNTRY_STR = "<b>Country</b>: "
END_COUNTRY_STR = '</div>";'
START_COUNTRY_STR_LEN = 16

START_CITY_STR = "<b>City</b>: "
END_CITY_STR = '</div>";'
START_CITY_STR_LEN = 13

COMMA = ","

def find_country_by_ip(ip , ips_countries_dict):
	"""
	Finds a ip by URL and ips countries dict.
	Returns the wanted country, ips - countries dict recently.
	
	:param ip: an ip to search.
	:param ips_countries_dict: a dict that using like a cash
	
	:ip type: str.
	:ips_countries_dict type: dict.
	
	:Return type: tuple.
	"""
	if ip not in ips_countries_dict.keys():
		
		#If the site is not working, or corrupt: 
		try:
			res = requests.get(GEOIP_URL + "/?q=%s" % (ip ,))
		except Exception:
			print("The GeoIpView is not working, try to support, and try again...\n")
			sys.exit()
		
		html = res.text
		
		#If the city was not founded, but just the country was founded.
		if START_COUNTRY_STR in html:
			start_index = html.find(START_COUNTRY_STR) + START_COUNTRY_STR_LEN
			end_index = html.find(END_COUNTRY_STR)
			country = html[start_index : end_index]
			
		#If the city was founded.
		elif START_CITY_STR in html:
			start_index = html.find(START_CITY_STR) + START_CITY_STR_LEN
			end_index = html.find(END_CITY_STR)
			city = html[start_index : end_index]
			splited_city = city.split(COMMA)
			country = splited_city[1]
			country = country[1 : ] #Without the space in the start.
			
		#If the site did not find the ip's country.
		if country == "":
			country = "Not found"
		
		ips_countries_dict[ip] = country
	else:
		country = ips_countries_dict[ip]
	
		
	return country, ips_countries_dict

def get_my_address():
	"""
	Finds my local address.
	Returns my address, as str.
	"""
	s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
	try:
		s.connect(("wix.com", 80))
	except Exception:
		print("Has not Internet connection...")
		sys.exit()
	my_address = s.getsockname()[0]
	s.close()
	return my_address

	
#For checking:
"""
ans = find_country_by_ip("239.255.255.250", {})
print(ans)
"""