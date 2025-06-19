import smbus
import spidev
import time

# --- ADT7410 (I2C) 設定 ---
i2c = smbus.SMBus(1)
adt7410_address = 0x48 # ADT7410のスレーブアドレス 

# --- MCP3002 (SPI) 設定 ---
spi = spidev.SpiDev()
spi.open(0, 0)
spi.bits_per_word = 8
spi.max_speed_hz = 10000

start = 0b01000000
sgl   = 0b00100000
ch0   = 0b00000000
ch1   = 0b00010000
msbf  = 0b00001000

def mcp3002(ch):
    rcv = spi.xfer2([(start + sgl + ch + msbf ), 0x00 ] )
    ad  = ((( rcv[0] & 0x03 ) << 8 ) + rcv[1] )
    return ad

def read_adt7410():
    try:
        word_data = i2c.read_word_data(adt7410_address, 0x00)
        data = (word_data & 0xFF) << 8 | (word_data >> 8)
        data = data >> 3
        
        if data & 0x1000:
            data -= 8192
            
        temperature = data * 0.0625
        return temperature
    except IOError:
        return None

def read_mcp9700a():
    try:
        data = mcp3002(ch0)
        
        voltage = (data * 3.3) / 1023.0
        
        temperature = (voltage / 0.01)
        return temperature
    except Exception as e:
        print(f"MCP9700A read error: {e}")
        return None

try:
    while True:
        temp_adt = read_adt7410()
        temp_mcp = read_mcp9700a()
        
        print(f"# ADT7410 (Digital): {temp_adt:.2f} C, MCP9700A (Analog): {temp_mcp:.2f} C")
        
        time.sleep(1)

except KeyboardInterrupt:
    print("\nProgram stopped.")
finally:
    spi.close()
    i2c.close()