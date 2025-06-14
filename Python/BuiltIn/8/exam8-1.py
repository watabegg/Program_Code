import RPi.GPIO as GPIO
import time

DIG = [24, 25, 26 ,27]
DEC = [20, 21, 22, 23]
SW = 16

GPIO.setmode( GPIO.BCM )
for i in range(4):
    GPIO.setup(DIG[i], GPIO.OUT)
    GPIO.output(DIG[i], GPIO.HIGH)
    GPIO.setup(DEC[i], GPIO.OUT)
    
# def 
    
try:
    GPIO.output(DIG[0], GPIO.HIGH)
    GPIO.output(DIG[1], GPIO.HIGH)
    GPIO.output(DIG[2], GPIO.LOW)
    GPIO.output(DIG[3], GPIO.HIGH)
    # for i in range(9, -1, -1):
    GPIO.output(DEC[0], GPIO.LOW) # 8
    GPIO.output(DEC[1], GPIO.LOW) # 4
    GPIO.output(DEC[2], GPIO.LOW) # 2
    GPIO.output(DEC[3], GPIO.LOW) # 1
    time.sleep(10)

except KeyboardInterrupt:
    pass

finally:
    GPIO.cleanup()

