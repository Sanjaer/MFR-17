# It would be a good idea making all the filters in here, to save processing load in the arduino
#!/usr/bin/python

import smbus
import sys

bus = smbus.SMBus(1)

valid_modules = [0x01, 0x0A, 0xAA, 0xAB, 0xAC, 0xAD]

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
    
def i2crecv(module, address=None):

    if address == None:
        address = 4
    # Report Arduino
    if module == 0x01:
        try:
            answ=bus.read_byte_data(address, module)
            return answ
        except:
            e = sys.exc_info()[0]
            return 0x00

    # Report motors
    elif module == 0xAA:
        try:
            if bus.read_byte_data(address, module) == 0x01:
                answ.append(bus.read_byte_data(address, 0xAB)) #Report sign
                answ.append(bus.read_byte_data(address, 0xAC)) #Report valueRight
                answ.append(bus.read_byte_data(address, 0xAD)) #Report valueLeft
                return answ
            else: 
                return 0x00
        except:
            e = sys.exc_info()[0]
            return 0x00
    else:
        if module in valid_modules:
            answ.append(bus.read_byte_data(address, module))
            return answ
        else:
            return 0x00

    