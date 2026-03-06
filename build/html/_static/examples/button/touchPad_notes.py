# 触摸按键控制七音阶播放
from mpython import *
import music

tone = [262,294,330,349,392,440,494]     #七音阶

while True:
    print(touchPad_P.read())
    if touchPad_P.read() <200:              #当按下触摸按键P，播放do
        # buzz.on(tone[0])
        music.play(music.DADADADUM, wait=False, loop=False)
    elif touchPad_Y.read() <200:            #当按下触摸按键Y，播放re
        # buzz.on(tone[1])
        music.play(music.DADADADUM, wait=False, loop=False)
    elif touchPad_T.read() <200:            #当按下触摸按键T，播放mi
        # buzz.on(tone[2])
        music.play(music.DADADADUM, wait=False, loop=False)
    elif touchPad_H.read() <200:            #当按下触摸按键H，播放fa
        # buzz.on(tone[3])   
        music.play(music.DADADADUM, wait=False, loop=False)
    elif touchPad_O.read() <200:            #当按下触摸按键O，播放so
        # buzz.on(tone[4])
        music.play(music.DADADADUM, wait=False, loop=False)
    elif touchPad_N.read() <200:            #当按下触摸按键N，播放la
        # buzz.on(tone[5])    
        music.play(music.DADADADUM, wait=False, loop=False)
    else:
        music.stop()                           

        


 