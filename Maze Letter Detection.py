import time, sensor, image
from image import SEARCH_EX, SEARCH_DS
from pyb import UART
from pyb import LED

uart = UART(3, 9600, timeout_char = 5000)
led1 = LED(1)  #connect LED

# Reset sensor
sensor.reset()

# Set sensor settings
sensor.set_contrast(1)
sensor.set_gainceiling(16)

# Max resolution for template matching with SEARCH_EX is QQVGA
sensor.set_framesize(sensor.QQVGA)

# Set windowing to reduce the search image.
#sensor.set_windowing(((640-80)//2, (480-60)//2, 80, 60))
sensor.set_pixformat(sensor.GRAYSCALE)

# Load template.

# Template
S = image.Image("/S.pgm")
U = image.Image("/U.pgm")
clock = time.clock()


# Run template matching
while (True):
     clock.tick()
     img = sensor.snapshot()   #image screenshot

#U & S LETTER

     U_img = img.find_template(U, 0.40, step=4, search=SEARCH_DS) #,roi=(10, 0, 60, 60))
     S_img = img.find_template(S, 0.40, step=4, search=SEARCH_DS) #,roi=(10, 0, 60, 60))


#IF DETECTS U, SEND U WITH UART , with circle, it is U, without it is H

     if U_img:
         if img.find_circles():
             print ("U")
             uart.write("U\n")
             #time.sleep(4000)
         else:
             print ("H")
             uart.write("H\n")
             time.sleep(4000)

#IF DETECTS S, SEND S WITH UART

     if S_img:
             print ("S")
             uart.write("S\n")
             time.sleep(4000)
