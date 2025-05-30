麦克风
=============

掌控板板载麦克风，可以用其感知周边环境的声音变化。

例：显示声音值
::
    from mpython import *
<<<<<<< HEAD
    
    while True:
        oled.fill(0) 
        oled.DispChar('声音：',0,16)
        oled.DispChar("%d" % (sound.read()),40,20)
        oled.show()
=======
    from lv_gui import *

    gui = GUI()
    while True:
        gui.fill(type=0)
        gui.draw_label(text=str('声音：'), row=1, color=0xffffff, wrap=False)
        gui.draw_label(text="%d" % (sound.read()), row=2, color=0xffffff, wrap=False)
        gui.update()
>>>>>>> a49b02ac8b2ea287667f94e3850599e06d43dcdb


使用前，导入mpython模块
::

  from mpython import *

我们使用 ``sound.read()`` 获取麦克风的数据。
::

    sound.read()



.. Note::

    麦克风使用 ``read()`` 函数来读取数据。返回的值为12bit的ADC采样数据，即最大值为十进制4095。


学会了如何收集周边环境的声音数据，我们可以结合其他功能做更多有趣的场景。

