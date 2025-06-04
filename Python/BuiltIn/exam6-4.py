import pigpio
import time
import spidev

PIN = 19
Hz = 10000
pi = pigpio.pi()
pi.set_mode( PIN, pigpio.OUTPUT )

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

def duty_func(per):
    return per * 1000

try:
    for i in range(100):
        pi.hardware_PWM( PIN, Hz, duty_func(i) )
        sum = 0
        for j in range(100):
            sum += mcp3002(ch0)
            time.sleep(0.001)
            
        cds = sum / 100
        print(f"Duty {i} % cds R: {cds}")
        
    pi.set_mode(PIN, pigpio.INPUT)
    pi.stop()
    
except KeyboardInterrupt:
    pass

pi.set_mode(PIN, pigpio.INPUT)
pi.stop()

# Duty 0 % cds R: 1022.65
# Duty 1 % cds R: 1006.8
# Duty 2 % cds R: 867.19
# Duty 3 % cds R: 765.15
# Duty 4 % cds R: 686.58
# Duty 5 % cds R: 636.69
# Duty 6 % cds R: 594.12
# Duty 7 % cds R: 555.12
# Duty 8 % cds R: 528.68
# Duty 9 % cds R: 503.34
# Duty 10 % cds R: 484.68
# Duty 11 % cds R: 464.05
# Duty 12 % cds R: 446.75
# Duty 13 % cds R: 432.86
# Duty 14 % cds R: 417.63
# Duty 15 % cds R: 406.52
# Duty 16 % cds R: 394.54
# Duty 17 % cds R: 384.53
# Duty 18 % cds R: 372.67
# Duty 19 % cds R: 365.19
# Duty 20 % cds R: 357.91
# Duty 21 % cds R: 348.6
# Duty 22 % cds R: 341.64
# Duty 23 % cds R: 334.6
# Duty 24 % cds R: 328.73
# Duty 25 % cds R: 322.52
# Duty 26 % cds R: 316.13
# Duty 27 % cds R: 312.14
# Duty 28 % cds R: 305.71
# Duty 29 % cds R: 300.99
# Duty 30 % cds R: 296.27
# Duty 31 % cds R: 292.94
# Duty 32 % cds R: 287.32
# Duty 33 % cds R: 283.23
# Duty 34 % cds R: 280.26
# Duty 35 % cds R: 276.25
# Duty 36 % cds R: 272.29
# Duty 37 % cds R: 269.53
# Duty 38 % cds R: 265.42
# Duty 39 % cds R: 262.72
# Duty 40 % cds R: 259.13
# Duty 41 % cds R: 256.01
# Duty 42 % cds R: 254.09
# Duty 43 % cds R: 250.96
# Duty 44 % cds R: 247.78
# Duty 45 % cds R: 245.33
# Duty 46 % cds R: 242.61
# Duty 47 % cds R: 240.49
# Duty 48 % cds R: 237.79
# Duty 49 % cds R: 235.1
# Duty 50 % cds R: 232.82
# Duty 51 % cds R: 230.74
# Duty 52 % cds R: 228.02
# Duty 53 % cds R: 225.67
# Duty 54 % cds R: 226.23
# Duty 55 % cds R: 222.59
# Duty 56 % cds R: 221.68
# Duty 57 % cds R: 218.45
# Duty 58 % cds R: 215.85
# Duty 59 % cds R: 216.0
# Duty 60 % cds R: 213.67
# Duty 61 % cds R: 212.19
# Duty 62 % cds R: 208.95
# Duty 63 % cds R: 208.8
# Duty 64 % cds R: 206.17
# Duty 65 % cds R: 205.01
# Duty 66 % cds R: 203.96
# Duty 67 % cds R: 202.17
# Duty 68 % cds R: 201.42
# Duty 69 % cds R: 199.51
# Duty 70 % cds R: 198.11
# Duty 71 % cds R: 196.88
# Duty 72 % cds R: 195.52
# Duty 73 % cds R: 194.82
# Duty 74 % cds R: 193.32
# Duty 75 % cds R: 192.63
# Duty 76 % cds R: 190.77
# Duty 77 % cds R: 189.05
# Duty 78 % cds R: 187.95
# Duty 79 % cds R: 187.14
# Duty 80 % cds R: 185.84
# Duty 81 % cds R: 184.76
# Duty 82 % cds R: 183.21
# Duty 83 % cds R: 182.75
# Duty 84 % cds R: 181.66
# Duty 85 % cds R: 180.49
# Duty 86 % cds R: 179.26
# Duty 87 % cds R: 178.95
# Duty 88 % cds R: 178.39
# Duty 89 % cds R: 176.8
# Duty 90 % cds R: 175.62
# Duty 91 % cds R: 176.55
# Duty 92 % cds R: 173.98
# Duty 93 % cds R: 173.72
# Duty 94 % cds R: 172.59
# Duty 95 % cds R: 171.16
# Duty 96 % cds R: 169.93
# Duty 97 % cds R: 169.32
# Duty 98 % cds R: 168.51
# Duty 99 % cds R: 167.74

