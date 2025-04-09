数字识别
==============

代码
-----------
例程::

    from mpython import *
    import smartcamera_new as smartcamera
    import time

    smart_camera = smartcamera.SmartCamera(tx=Pin.P16, rx=Pin.P15)
    smart_camera.mnist_init(1)
    while True:
        smart_camera.mnist.recognize()
        if smart_camera.mnist.id != None:
            print(smart_camera.mnist.id)
        time.sleep_ms(20)



mPython图形化示例
-----------
.. figure:: /_static/image/example/mnist/mnist.png
    :align: center
    :width: 1080