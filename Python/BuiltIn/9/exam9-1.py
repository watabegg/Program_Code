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
    """ADT7410から温度を読み取る関数"""
    try:
        # 上位バイトと下位バイトを読み込み 
        word_data = i2c.read_word_data(adt7410_address, 0x00)
        # バイトオーダーをスワップ
        data = (word_data & 0xFF) << 8 | (word_data >> 8)
        # 13bitモードなので3bit右シフト 
        data = data >> 3
        
        # 2の補数表現で負の値を判定
        if data & 0x1000: # 13bit目で判定
            data -= 8192 # 2^13 = 8192
            
        # 温度に換算 (分解能 0.0625℃) 
        temperature = data * 0.0625
        return temperature
    except IOError:
        return None

def read_mcp9700a():
    """MCP9700Aの値をMCP3002経由で読み取り温度に変換する関数"""
    try:
        data = mcp3002(ch0)
        
        # デジタル値を電圧に変換 (10bit, 3.3V)
        voltage = (data * 3.3) / 1023.0
        
        # 電圧を温度に変換 (℃) 
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
    
# 2025/06/19 18:20
# ADT7410 (Digital): 27.56 C, MCP9700A (Analog): 27.42 C
# ADT7410 (Digital): 27.50 C, MCP9700A (Analog): 27.10 C
# ADT7410 (Digital): 28.12 C, MCP9700A (Analog): 27.10 C
# ADT7410 (Digital): 27.94 C, MCP9700A (Analog): 27.42 C
# ADT7410 (Digital): 29.00 C, MCP9700A (Analog): 27.42 C

# 2025/06/19 19:20
# ADT7410 (Digital): 27.56 C, MCP9700A (Analog): 26.45 C
# ADT7410 (Digital): 26.94 C, MCP9700A (Analog): 26.45 C
# ADT7410 (Digital): 27.50 C, MCP9700A (Analog): 26.45 C
# ADT7410 (Digital): 27.50 C, MCP9700A (Analog): 26.45 C
# ADT7410 (Digital): 27.06 C, MCP9700A (Analog): 26.13 C
# ADT7410 (Digital): 26.75 C, MCP9700A (Analog): 26.45 C