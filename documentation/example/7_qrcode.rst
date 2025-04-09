二维码识别
==============

代码
-----------
例程::

    from mpython import *
    import smartcamera_new as smartcamera
    import time

    smart_camera = smartcamera.SmartCamera(tx=Pin.P16, rx=Pin.P15)
    smart_camera.qrcode_init(1)
    smart_camera.qrcode.add_qrcode(2)
    while True:
        smart_camera.qrcode.recognize()
        if smart_camera.qrcode.id != None:
            print(smart_camera.qrcode.id)
        time.sleep_ms(20)



mPython图形化示例
-----------
.. figure:: /_static/image/example/qrcode/qrcode.png
    :align: center
    :width: 1080




