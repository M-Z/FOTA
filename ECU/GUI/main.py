import RPi.GPIO as GPIO
import spidev
import time
import sys
import can
import mcp2515
    

GPIO.setmode(GPIO.BCM)
GPIO.setup(24,GPIO.IN)
GPIO.add_event_detect(24,GPIO.FALLING,callback=can.RX_interrupt)
filters = [40]
can.init(filters)
print('Waiting for message')
##flag = can.readReg(mcp2515.CANINTF)
##while ((flag & 0x01) == 0):
##    flag = can.readReg(mcp2515.CANINTF)
##print('Message Received')
msg = {'ID':30, 'format':'standard_format', 'type':'data_frame', 'length':8, 'data':[1,2,3,4,5,6,7,8]}
can.transmit_buffer0(msg)
while(1):
    len = len(can.RX_msg)
    for i in range(len):
        if can.RX_msg[0]['ID'] == 60:
            #send update request to mailbox
            window.Show_New_Update()
        del can.RX_msg[0]
      
      
      