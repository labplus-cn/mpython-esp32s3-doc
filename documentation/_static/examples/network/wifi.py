from mpython import *
import network

my_wifi = wifi()

my_wifi.connectWiFi("my_wifi", "12345678")

if my_wifi.sta.isconnected():
    print(my_wifi.sta.ifconfig())



