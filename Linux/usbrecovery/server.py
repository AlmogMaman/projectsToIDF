import socket
import json
import os



def create_socket():
  try:
    global sock
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    sock.bind(('', 25565))
  except socket.error as msg:
    print("socket creation faild: " + str(msg) + " retrying...")
    create_socket()


def find_all_sub_dirs_of(path):
  result = []
  for dir in os.listdir(path):
    full_path = os.path.join(path, dir)
    if os.path.isdir(full_path): result.append(full_path)
  result.sort(key=os.path.getctime)
  return result

def find_latest(list_of_backups):

  latest = max(list_of_backups, key=os.path.getmtime)
  return latest



def main():
  create_socket()
  while True:
    print("waiting for request...")
    request, client_address = sock.recvfrom(4096)
    print("new request from: " + client_address[0])
    request = request.decode()
    print(request)
    vendorID, backupDate = request.split(":")
    response = ""
    print(vendorID +"      " + backupDate)
    #if client selected auto detection:
    if vendorID != "all":
        try:
            all_backups = find_all_sub_dirs_of("/home/Backups/%s" % vendorID)
            if(len(all_backups) == 0):
                print("There are no backups for selected USB")
                response = "Error: There are no backups for selected USB"
   
            else:
                if backupDate == "latest":
                    response = find_latest(all_backups)
                elif backupDate == "all":
                    response = json.dumps(all_backups)
        except:
            print("unknown USB - There are no backups")
            response = "Error: unknown USB - There are no backups"
    else:
        response = {}
        all_usbs = find_all_sub_dirs_of("/home/Backups")
        for usb in all_usbs:
            if backupDate == "latest":
                try:
                    response[usb] = find_latest(find_all_sub_dirs_of(usb))
                except:
                    #if there are no backups for this usb
                    response[usb] = None
                    continue
            else:
                response[usb] = find_all_sub_dirs_of(usb)
        response = json.dumps(response)
    sock.sendto(response.encode(), client_address)



if __name__ == '__main__':
  main()
