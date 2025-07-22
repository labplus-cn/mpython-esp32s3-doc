# 通过y轴加速度求y轴与水平面倾斜角度
from mpython import*
from lv_gui import *
from math import acos,degrees


gui = GUI()
while True:
    y=accelerometer.get_y()
    if y<=1 and y>=-1:
        rad_y=acos(y)
        deg_y=90-degrees(rad_y)
        gui.fill(type=0)
        gui.draw_label(text=str('%.2f°' %deg_y), row=1, color=0xffffff, wrap=False)
        gui.update()

        

