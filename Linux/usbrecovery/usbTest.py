import usb.core
import usb.util
import sys

class find_class(object):
    def __init__(self, class_):
        self._class = class_
    def call(self, device):
        if device.bDeviceClass == self._class:
            return True
        for cfg in device:
            intf = usb.util.find_descriptor(
                                        cfg,
                                        bInterfaceClass=self._class
                                )
            if intf is not None:
                return True

        return False

storage = usb.core.find(find_all=1, custom_match=find_class(8))
if(storage != None):
    print(storage)
