颜色识别
==============


颜色识别
-----------
例程::

    from mpython import *
    import smartcamera_new as smartcamera
    import time

    smart_camera = smartcamera.SmartCamera(tx=Pin.P16, rx=Pin.P15)
    smart_camera.color_init(1)
    smart_camera.color.add_color(2)
    while True:
        smart_camera.color.recognize()
        if smart_camera.color.id != None:
            print(smart_camera.color.id)
        time.sleep_ms(20)




mPython图形化示例
-----------
.. figure:: /_static/image/example/color/color.png
    :align: center
    :width: 1080



LAB颜色提取
-----------
例程::

    from mpython import *
    from camera import *
    import time

    camera = CameraV831(tx=Pin.P16, rx=Pin.P15)
    camera.color_init()
    camera.color.add_color(3)
    while True:
        camera.color.recognize()
        if camera.color.id != None:
            print(camera.color.id)
        time.sleep_ms(20)



mPython图形化示例
-----------
.. figure:: /_static/image/example/color/color.png
    :align: center
    :width: 1080