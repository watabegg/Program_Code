import RPi.GPIO as GPIO
import time

SW = 21       # スイッチのGPIOピン
CDS = 20      # CDS出力（比較器出力）のGPIOピン
LED = 16      # LEDのGPIOピン

GPIO.setmode(GPIO.BCM)
GPIO.setup(SW, GPIO.IN, pull_up_down=GPIO.PUD_UP)
GPIO.setup(CDS, GPIO.IN, pull_up_down=GPIO.PUD_UP)
GPIO.setup(LED, GPIO.OUT)

led_on = False

def sw_callback(channel):
    global led_on
    if led_on:
        GPIO.output(LED, GPIO.HIGH)
        led_on = False
        print("SW押下：LED消灯")

def cds_callback(channel):
    global led_on
    if GPIO.input(CDS) == GPIO.HIGH:  # 暗いときにLOWになる設定
        GPIO.output(LED, GPIO.LOW)
        led_on = True
        print("暗さ検知：LED点灯")

GPIO.add_event_detect(SW, GPIO.FALLING, callback=sw_callback, bouncetime=200)
GPIO.add_event_detect(CDS, GPIO.FALLING, callback=cds_callback, bouncetime=200)

try:
    while True:
        time.sleep(1)
except KeyboardInterrupt:
    pass
finally:
    GPIO.cleanup()
