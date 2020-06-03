
import smbus  
import time  
import sys  
bus = smbus.SMBus(1)    
address = 0x08          # Arduino I2C Address  
def main():
    
    while 1:  
        response = bus.read_byte(address);        #receive data from Argon
        print ("Argon answer to RPi:", response); # print down the response
        time.sleep(3)
        # create a timer
        if (response == 1):
            for i in range(21):   
                print(i)
                time.sleep(1)
                if(i == 20):
                    print("congratulation you have been cleaned :))")
    
    
    

if __name__ == '__main__':  
    try:  
        main()  
    except KeyboardInterrupt:
        # clean up all the system
        gpio.cleanup()  
        sys.exit(0) 