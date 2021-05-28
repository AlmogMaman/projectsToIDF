import ctypes, sys

def is_admin():
	"""
	Checks if the program is in an admin permissions.
	"""
	
	try:
		return ctypes.windll.shell32.IsUserAnAdmin()
	except Exception:
		return False

def administrator():
	"""
	Ask the user for permissions.
	"""
	ctypes.windll.shell32.ShellExecuteW(None, "runas", sys.executable, __file__, None, 1)
	