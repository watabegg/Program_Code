import RPi.GPIO as GPIO
import spidev
import time

TEMP_THRESHOLD = 30.0
ACCEL_THRESHOLD = 1.5
LED_PIN = 21          

GPIO.setmode(GPIO.BCM)
GPIO.setup(LED_PIN, GPIO.OUT)

adc_spi = spidev.SpiDev()
adc_spi.open(0, 0)
adc_spi.max_speed_hz = 10000

lis_spi = spidev.SpiDev()
lis_spi.open(0, 1)
lis_spi.max_speed_hz = 10000

start = 0b01000000
sgl   = 0b00100000
ch0   = 0b00000000
msbf  = 0b00001000

CTRL_REG1 = 0x20
OUT_X_L = 0x28
OUT_Y_L = 0x2A
OUT_Z_L = 0x2C

def mcp3002(ch):
    rcv = adc_spi.xfer2([(start + sgl + ch + msbf), 0x00])
    ad = (((rcv[0] & 0x03) << 8) + rcv[1])
    return ad

def read_mcp9700a():
    try:
        data = mcp3002(ch0)
        voltage = (data * 3.3) / 1023.0
        
        temperature = (voltage / 0.01)
        return temperature
    except Exception as e:
        print(f"MCP9700A read error: {e}")
        return None

def setup_lis3dh():
    lis_spi.xfer2([CTRL_REG1, 0x27])

def read_lis3dh_axis_g(reg_l):
    reg_h = reg_l + 1
    low_byte = lis_spi.xfer2([reg_l | 0x80, 0x00])[1]
    high_byte = lis_spi.xfer2([reg_h | 0x80, 0x00])[1]
    
    value = (high_byte << 8) | low_byte
    
    if value > 32767:
        value -= 65536
    
    raw_value = value >> 4
    
    g_value = (raw_value / 2047.0) * 2.0
    return g_value

try:
    setup_lis3dh()
    
    while True:
        temp = read_mcp9700a()
        
        x_val = read_lis3dh_axis_g(OUT_X_L)
        y_val = read_lis3dh_axis_g(OUT_Y_L)
        z_val = read_lis3dh_axis_g(OUT_Z_L)
        
        if temp is not None:
            print(f"# Temp: {temp:.2f} C | Accel X: {x_val}, Y: {y_val}, Z: {z_val}")
            if temp is not None and temp > TEMP_THRESHOLD:
                print("\n!!! TEMPERATURE ALERT !!!")
                for _ in range(5):
                    GPIO.output(LED_PIN, GPIO.HIGH)
                    time.sleep(0.1)
                    GPIO.output(LED_PIN, GPIO.LOW)
                    time.sleep(0.1)
            elif abs(x_val) > ACCEL_THRESHOLD or abs(y_val) > ACCEL_THRESHOLD or abs(z_val) > ACCEL_THRESHOLD:
                print("\n!!! ACCELERATION ALERT !!!")
                for _ in range(3):
                    GPIO.output(LED_PIN, GPIO.HIGH)
                    time.sleep(0.3)
                    GPIO.output(LED_PIN, GPIO.LOW)
                    time.sleep(0.3)
            else:
                GPIO.output(LED_PIN, GPIO.LOW)
        else:
            print("Failed to read temperature.")
        
        time.sleep(0.5)

except KeyboardInterrupt:
    print("\nProgram stopped.")
finally:
    adc_spi.close()
    lis_spi.close()
