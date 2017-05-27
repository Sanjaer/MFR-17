# It would be a good idea making all the filters in here, to save processing load in the arduino
#!/usr/bin/python

import smbus
import sys

bus = smbus.SMBus(1)

def i2csend(module, data_array, address=None):
    #TODO: Add checks
    if address == None:
        address = 4
        
    try:
        bus.write_block_data(address, module, data_array)
        return 0
    except:
        e = sys.exc_info()[0]
        return -1 
    
def i2crecv(address=None):

    if address == None:
        address = 4
    number=bus.read_block_data(address, 0)
    return number