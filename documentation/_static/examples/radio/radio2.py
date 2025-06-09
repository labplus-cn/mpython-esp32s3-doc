'''广播'''
'''发送数据给特定mac地址设备'''
import time
import random
from mpython import *
from radio import *

espnow_0 = MPythonESPNow(0)

#MPythonESPNow.set_add_peer(peer_mac='') peer_mac:mac地址 16进制字符串 将提供的mac地址注册为对等地址 7CDFA1F20AF4
espnow_0.set_add_peer(peer_mac='7CDFA1F20ADC') 

print(espnow_0.get_mac(0))
print(espnow_0.get_mac(1))

while True:
    msg = random.randint(0, 9999999)
    print(str(msg), 0, 32, 1)
    #MPythonESPNow.send_msg(peer_mac='',msg='') msg：字符串数据
    espnow_0.send_msg(peer_mac='7CDFA1F20ADC', msg=msg)
    time.sleep(0.3)

