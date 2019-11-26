import rospy 
import usb.core
import usb.util
import time
import os 
import subprocess 
import sys


USB_IF      = 0 # Interface
USB_TIMEOUT = 5 # Timeout in MS

USB_VENDOR  = 0x054c # Rii
USB_PRODUCT = 0x05c4 # Mini Wireless Keyboard

dev = usb.core.find(idVendor=USB_VENDOR, idProduct=USB_PRODUCT)

endpoint = dev[0][(0,0)][0]

#if dev.is_kernel_driver_active(USB_IF) is True:
#  dev.detach_kernel_driver(USB_IF)

#usb.util.claim_interface(dev, USB_IF)

while True:
  control = None
  try:
    control = dev.read(endpoint.bEndpointAddress, endpoint.wMaxPacketSize, USB_TIMEOUT)
    left = 2*(127 - int(control[2]))
    right = 2*(127-int(control[4]))
    left_cmd = "rostopic pub drive_left std_msgs/Int16 --once -- " + str(3)
    # subprocess.call(left_cmd)
    print left_cmd
    #os.system("rostopic pub drive_right std_msgs/Int16" + str(right) + " --once")
    #print("(", 2*(127 - int(control[2])), ", ", 2*(127-int(control[4])), ")")
  except:
    pass
  
  time.sleep(0.01) # Let CTRL+C actually exit
