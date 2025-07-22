'''接收消息'''
import time
import random
from mpython import *
from radio import *

def espnow_recv_callback(espnow_obj):
    espnow_mac, espnow_data, espnow_rssi = espnow_obj.recv_msg() # 接收消息
    print(espnow_data)
    print(f"MAC: {espnow_mac}, RSSI: {espnow_rssi} dBm, Data: {espnow_data}")

espnow_1 = MPythonESPNow(0)
# MPythonESPNow.set_irq_callback(callback) callback 接收消息回调函数
espnow_1.set_irq_callback(espnow_recv_callback)

print(espnow_1.get_mac(0))
print(espnow_1.get_mac(1))
