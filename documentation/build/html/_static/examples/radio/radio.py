'''广播'''
'''广播数据'''
import time
import random
from mpython import *
from radio import *

#MPythonESPNow(wifi_ch=0)  wifi_ch:信道 0-14 整型
espnow_0 = MPythonESPNow(wifi_ch=0) 

#MPythonESPNow.get_mac(mode=0) mode:0 sta地址/1 ap地址 16进制字符串mac地址
oled.fill(0)
oled.DispChar(str(espnow_0.get_mac(mode=0)), 0, 0, 1)
oled.show()

print(espnow_0.get_mac(mode=0)) # sta 
print(espnow_0.get_mac(mode=1)) # ap

while True:
    msg = random.randint(0, 99999)
    #MPythonESPNow.broadcast_data(msg='') msg：字符串数据
    espnow_0.broadcast_data(msg=msg) 
    print(str(msg))
    time.sleep(0.5)

