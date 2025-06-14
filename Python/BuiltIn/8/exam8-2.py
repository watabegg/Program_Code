import RPi.GPIO as GPIO
import datetime
import time

PIN_D0 = 20 # 8
PIN_D1 = 21 # 4
PIN_D2 = 22 # 2
PIN_D3 = 23 # 1
BCD_PINS = [PIN_D0, PIN_D1, PIN_D2, PIN_D3]

PIN_DIG1 = 24
PIN_DIG2 = 25
PIN_DIG3 = 26
PIN_DIG4 = 27
DIGIT_PINS = [PIN_DIG1, PIN_DIG2, PIN_DIG3, PIN_DIG4]

PIN_SWITCH = 16

display_mode = 'time'

BCD_CODES = {
    0: (0,0,0,0), 1: (1,0,0,0), 2: (0,1,0,0), 3: (1,1,0,0), 4: (0,0,1,0),
    5: (1,0,1,0), 6: (0,1,1,0), 7: (1,1,1,0), 8: (0,0,0,1), 9: (1,0,0,1),
    15: (1,1,1,1)
}

def setup():
    GPIO.setmode(GPIO.BCM)
    GPIO.setwarnings(False)
    for pin in BCD_PINS:
        GPIO.setup(pin, GPIO.OUT)
    for pin in DIGIT_PINS:
        GPIO.setup(pin, GPIO.OUT)
        GPIO.output(pin, GPIO.HIGH) # 全桁を初期状態で非表示
    GPIO.setup(PIN_SWITCH, GPIO.IN, pull_up_down=GPIO.PUD_DOWN)
    GPIO.add_event_detect(PIN_SWITCH, GPIO.RISING, callback=switch_callback, bouncetime=300)

def switch_callback(channel):
    global display_mode
    if display_mode == 'time':
        display_mode = 'date'
    else:
        display_mode = 'time'

def send_to_bcd(number):
    code = BCD_CODES.get(number, BCD_CODES[15])
    for i in range(4):
        GPIO.output(BCD_PINS[i], code[i])

def display_loop():
    while True:
        now = datetime.datetime.now()
        
        if display_mode == 'time':
            h1 = now.hour // 10
            h2 = now.hour % 10
            m1 = now.minute // 10
            m2 = now.minute % 10
            display_digits = [h1, h2, m1, m2]
        else:
            mo1 = now.month // 10
            mo2 = now.month % 10
            d1 = now.day // 10
            d2 = now.day % 10
            display_digits = [mo1, mo2, d1, d2]
            
        if display_digits[0] == 0:
            display_digits[0] = 15
        if display_digits[2] == 0:
            display_digits[2] = 15
        
        for i in range(4):
            for pin in DIGIT_PINS:
                GPIO.output(pin, GPIO.HIGH)
            
            send_to_bcd(display_digits[i])
            
            GPIO.output(DIGIT_PINS[i], GPIO.LOW)
            
            time.sleep(0.002)

def main():
    try:
        setup()
        display_loop()
    except KeyboardInterrupt:
        pass
    finally:
        GPIO.cleanup()

if __name__ == '__main__':
    main()