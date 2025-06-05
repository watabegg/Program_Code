import RPi.GPIO as GPIO
import time

GPIO.setmode(GPIO.BCM)
SW = 21
GPIO.setup(SW, GPIO.IN, pull_up_down=GPIO.PUD_UP)

s = 0

def checkSW(pin):
    global s
    s = 1
    
GPIO.add_event_detect(SW, GPIO.FALLING, callback=checkSW, bouncetime=200)

try:
    while True:
        if s == 1:
            print("SW on")
            s = 0
        else:
            print("SW off")
        time.sleep(1)
        
except KeyboardInterrupt:
    pass
finally:
    GPIO.remove_event_detect(sw)
    GPIO.cleanup()