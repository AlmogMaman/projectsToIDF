import os.path
from os import path
import pwd
RULE_PATH="/etc/udev/rules.d/83-detectUsb.rules"

BACKUP_AGENT = os.path.abspath("notify-plugin.sh")
UMOUNT_AGENT= os.path.abspath("remove.sh")
HOME = os.environ['HOME']
USER = os.getenv('SUDO_USER')
PWNAM=pwd.getpwnam(USER)
uid = PWNAM.pw_uid
print(HOME)
print(uid)
#adapt the BACKUP_AGENT to the environment
with open("scriptPattern", "r") as scriptSrc:
    script_content = scriptSrc.read()
    with open("notify-plugin.sh", "w") as outputScript:
        script_content = script_content % (HOME, uid, '%d', '%m', '%Y')
        outputScript.write(script_content)

#create udev rule
if(not path.exists(RULE_PATH)):
    with open("udevRule", "r") as srcRuleFile:
        rule_content = srcRuleFile.read()
        with open(RULE_PATH , "w") as rule:
            rule.write(rule_content % (HOME, BACKUP_AGENT, '%k', UMOUNT_AGENT))
            print("Writing new rule to custom udev rules dictionary")
    os.system("udevadm control -R") 

else:
   pass
