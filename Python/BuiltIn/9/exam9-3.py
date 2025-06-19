import RPi.GPIO as GPIO
import spidev
import time

# --- 異常値の閾値とLEDピンを定義 --- 
TEMP_THRESHOLD = 30.0  # 温度の異常値 (℃)
ACCEL_THRESHOLD = 1.5 # 加速度の異常値 (g)
LED_PIN = 21           # LEDを接続するGPIOピン

# --- GPIOのセットアップ ---
GPIO.setmode(GPIO.BCM)
GPIO.setup(LED_PIN, GPIO.OUT)

# --- SPIデバイスの準備 ---
# デバイス0 (CE0) for ADC (MCP3002)
adc_spi = spidev.SpiDev()
adc_spi.open(0, 0) # SPIバス0, デバイス0 (CE0)
adc_spi.max_speed_hz = 10000

# デバイス1 (CE1) for Accelerometer (LIS3DH)
lis_spi = spidev.SpiDev()
lis_spi.open(0, 1) # SPIバス0, デバイス1 (CE1) 
lis_spi.max_speed_hz = 10000

# --- MCP3002 制御用定数 ---
start = 0b01000000
sgl   = 0b00100000
ch0   = 0b00000000
msbf  = 0b00001000

# --- LIS3DH レジスタアドレス等 ---
CTRL_REG1 = 0x20
OUT_X_L = 0x28
OUT_Y_L = 0x2A
OUT_Z_L = 0x2C

def mcp3002(ch):
    """MCP3002から指定チャンネルの値を読み取る (ADC用SPIを使用)"""
    rcv = adc_spi.xfer2([(start + sgl + ch + msbf), 0x00])
    ad = (((rcv[0] & 0x03) << 8) + rcv[1])
    return ad

def read_mcp9700a():
    """MCP9700Aの値をMCP3002経由で読み取り温度に変換する関数"""
    try:
        data = mcp3002(ch0)
        voltage = (data * 3.3) / 1023.0
        
        temperature = (voltage / 0.01)
        return temperature
    except Exception as e:
        print(f"MCP9700A read error: {e}")
        return None

def setup_lis3dh():
    """LIS3DHを初期化する (加速度センサ用SPIを使用)"""
    # CTRL_REG1 (0x20) に 0x27 を書き込み 
    # ODR=10Hz, Normal mode, X/Y/Z軸有効 
    lis_spi.xfer2([CTRL_REG1, 0x27])

def read_lis3dh_axis_g(reg_l):
    """LIS3DHの指定された軸のデータを読み取り、g値に変換して返す"""
    reg_h = reg_l + 1
    low_byte = lis_spi.xfer2([reg_l | 0x80, 0x00])[1]
    high_byte = lis_spi.xfer2([reg_h | 0x80, 0x00])[1]
    
    # 2バイトを結合して16bitのデータにする
    value = (high_byte << 8) | low_byte
    
    # 2の補数表現で負の値を判定
    if value > 32767:
        value -= 65536
    
    # 12bitデータなので4bit右シフトしてraw値を取得
    raw_value = value >> 4
    
    # raw値をg値に変換 (±2gモードの場合)
    # 12bitの最大値(2047)が+2gに相当
    g_value = (raw_value / 2047.0) * 2.0
    return g_value


# --- メイン処理 ---
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
                # 温度異常：速い点滅
                print("\n!!! TEMPERATURE ALERT !!!")
                for _ in range(5):
                    GPIO.output(LED_PIN, GPIO.HIGH)
                    time.sleep(0.1)
                    GPIO.output(LED_PIN, GPIO.LOW)
                    time.sleep(0.1)
            elif abs(x_val) > ACCEL_THRESHOLD or abs(y_val) > ACCEL_THRESHOLD or abs(z_val) > ACCEL_THRESHOLD:
                # 加速度異常：遅い点滅
                print("\n!!! ACCELERATION ALERT !!!")
                for _ in range(3):
                    GPIO.output(LED_PIN, GPIO.HIGH)
                    time.sleep(0.3)
                    GPIO.output(LED_PIN, GPIO.LOW)
                    time.sleep(0.3)
            else:
                # 正常時はLEDオフ
                GPIO.output(LED_PIN, GPIO.LOW)
        else:
            print("Failed to read temperature.")
        
        time.sleep(0.5)

except KeyboardInterrupt:
    print("\nProgram stopped.")
finally:
    adc_spi.close()
    lis_spi.close()
    
# Temp: 27.10 C | Accel X: 0.01172447484123107, Y: 0.027357107962872496, Z: 1.0669272105520273
# Temp: 27.10 C | Accel X: 0.0, Y: 0.039081582804103565, Z: 1.063019052271617
# Temp: 27.10 C | Accel X: 0.03517342452369321, Y: 0.03126526624328285, Z: 1.1216414264777723
# Temp: 27.10 C | Accel X: -0.050806057645334635, Y: 0.06643869076697606, Z: 1.0825598436736688
# Temp: 27.10 C | Accel X: -0.01172447484123107, Y: 0.019540791402051783, Z: 1.051294577430386
# Temp: 27.10 C | Accel X: 0.007816316560820713, Y: 0.019540791402051783, Z: 1.0591108939912066
# Temp: 27.10 C | Accel X: 0.007816316560820713, Y: 0.027357107962872496, Z: 1.063019052271617
# Temp: 27.10 C | Accel X: 0.01172447484123107, Y: 0.05862237420615535, Z: 1.0669272105520273
# Temp: 27.42 C | Accel X: 0.4298974108451392, Y: 0.0625305324865657, Z: 1.9931607230092818

# !!! ACCELERATION ALERT !!!
# Temp: 27.10 C | Accel X: 0.0039081582804103565, Y: 0.039081582804103565, Z: 1.0317537860283341
# Temp: 27.10 C | Accel X: 0.0, Y: 0.027357107962872496, Z: 1.0552027357107963
# Temp: 27.10 C | Accel X: 0.0, Y: 0.03126526624328285, Z: 1.063019052271617
# Temp: 27.10 C | Accel X: -0.0039081582804103565, Y: 0.03126526624328285, Z: 1.0473864191499755
# Temp: 27.10 C | Accel X: -0.007816316560820713, Y: 0.04298974108451392, Z: 1.051294577430386
# Temp: 27.42 C | Accel X: 0.01172447484123107, Y: 0.027357107962872496, Z: 1.0669272105520273
# Temp: 27.74 C | Accel X: 0.0039081582804103565, Y: 0.039081582804103565, Z: 1.0786516853932584
# Temp: 28.39 C | Accel X: 0.0039081582804103565, Y: 0.03517342452369321, Z: 1.0669272105520273
# Temp: 29.03 C | Accel X: 0.0039081582804103565, Y: 0.04689789936492428, Z: 1.0591108939912066
# Temp: 29.35 C | Accel X: -0.0039081582804103565, Y: 0.03517342452369321, Z: 1.0591108939912066
# Temp: 29.68 C | Accel X: 0.0, Y: 0.04689789936492428, Z: 1.0591108939912066
# Temp: 30.00 C | Accel X: 0.0039081582804103565, Y: 0.039081582804103565, Z: 1.0669272105520273
# Temp: 30.32 C | Accel X: 0.0039081582804103565, Y: 0.04298974108451392, Z: 1.0669272105520273

# !!! TEMPERATURE ALERT !!!
# Temp: 30.65 C | Accel X: 0.0039081582804103565, Y: 0.02344894968246214, Z: 1.0552027357107963

# !!! TEMPERATURE ALERT !!!
# Temp: 30.32 C | Accel X: 0.0039081582804103565, Y: 0.03126526624328285, Z: 1.074743527112848
