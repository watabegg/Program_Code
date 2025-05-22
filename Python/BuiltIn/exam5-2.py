import spidev
import time

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

try:
    for i in range(10):
        sum += mcp3002(ch1)
        time.sleep(0.5)
        
    print(sum / 10)
except KeyboardInterrupt:
    pass

spi.close()