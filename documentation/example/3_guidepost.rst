路标识别
==============


代码
-----------
例程::

    from mpython import *
    import smartcamera_new as smartcamera
    import time

    smart_camera = smartcamera.SmartCamera(tx=Pin.P16, rx=Pin.P15)
    smart_camera.guidepost_init(1)
    while True:
        smart_camera.guidepost.recognize()
        if smart_camera.guidepost.id != None and smart_camera.guidepost.max_score >= 0.8:
            print(smart_camera.guidepost.id)
            print(smart_camera.guidepost.max_score)
        time.sleep_ms(20)




mPython图形化示例
-----------
.. figure:: /_static/image/example/guidepost/guidepost.png
    :align: center
    :width: 1080