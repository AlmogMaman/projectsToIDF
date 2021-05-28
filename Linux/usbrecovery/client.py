import socket
import json
import os
import sys
def create_socket():
  try:  
    global sock
    global server_address
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    server_address = ('192.168.1.19', 25565)
  except socket.error as msg:
    print("Faild to create" + str(msg) + " retrying...")
    create_socket()

def get_option():
  print ("""
      1. Restore the last version of current usb
      2. choose specific version of currnet usb
      3. Restore the last version of another usb
      4. choose any version of any usb
  """)
  option = int(input())
  if(not( 1 <= option <= 4)):
    raise ValueError
  return option

def manage_menu():
   #ensure the validation of input
  global option
  while True:
    try:
      option = get_option()
      break
    except ValueError:
      pass

    print("\n Invalid Input")
  
  
  request = ""
  if option == 1:
    curr_vendId = auto_detect()
    if(not curr_vendId): return
    request = "%s:latest" % curr_vendId
  elif option == 2:
    curr_vendId = auto_detect()
    if(not curr_vendId): return
    request = "%s:all" % curr_vendId
  elif option == 3:
    request = "all:latest"
  elif option == 4:
    request = "all:all"
  return request

def auto_detect():
  with open("/currentUsb", "r") as currUsbFile:
    curr_vendorId = currUsbFile.read()
    curr_vendorId = curr_vendorId.strip('\n')#remove \n that echo wrote when it created the file
    if len(curr_vendorId) == 0:
      print("\n please enter usb first")
      return
  return curr_vendorId


def main():
  create_socket()
  request = None
  while(not request):
    request = manage_menu()
    if request:
      print(request)
      sock.sendto(request.encode(),server_address)
      response, server = sock.recvfrom(4096)
#todo: if Error in response
#todo: os.basename(full path) -> dir name
      response = response.decode()
      print(response)
      break

  remote_backup_path = response
  if "Error" in response:
    print("Error occurred:" + response)
    sys.exit(1)

  elif option is 2:
    all_backups = json.loads(response)
    print ("choose backup from the list:\n")
    for i, backup in enumerate(all_backups):
      print(str(i) + ") %s" % os.path.basename(backup))
    backup_index = int(input("\n"))
    remote_backup_path = all_backups[backup_index]

  elif option is 3 or option is 4:
    print("choose vendor id:")
    all_ids = json.loads(response)
    for i, id in enumerate(all_ids):
      print(str(i) + ") %s" % os.path.basename(id))
    id_index = int(input("\n"))
    backups = list(all_ids.values())[id_index]

    if option is 3:
      if not backups:
        print("Error: no backups for selected usb")
        sys.exit(1)

      remote_backup_path = backups #if the option is 3 there is only one backup -> the latest

    elif option is 4:
      if len(backups) == 0:
        print("Error: no backups for selected usb")
        sys.exit(1)

      print("Choose backup from the list:")
      for k, backup in enumerate(backups):
        print(str(k) + ") %s" % os.path.basename(backup))
      index = int(input("\n"))
      remote_backup_path = backups[index]
	    
  print(remote_backup_path)

  #restore the usb
  os.system("rsync -ab --delete root@%s:%s/ /media/`date +%s-%s-%s`; notify-send 'Restoration' 'restoration completed'" % (server[0],remote_backup_path,"%d","%m","%Y"))
  
  sock.close()


if __name__ == '__main__':
  main()
