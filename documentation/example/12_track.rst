寻找色块
===================

例程::

    from mpython import *
    import smartcamera_new as smartcamera
    import time

    smart_camera = smartcamera.SmartCamera(tx=Pin.P16, rx=Pin.P15)
    smart_camera.sensor_config(1,2,1,160,120,0,0,(-1),(-1),1,0,1,0,24000000)
    smart_camera.track_init(_choice=1)
    smart_camera.track_set_up([[0, 100, -128, 127, -128, -46], [0, 80, 15, 127, 15, 127], [0, 80, -70, -10, 0, 30], [40, 100, -25, 42, 7, 127]],100)
    while True:
        smart_camera.track.recognize()
        if smart_camera.track.x != None:
            print(smart_camera.track.x)
            print(smart_camera.track.cx)
            print(smart_camera.track.code)
        print('===')
        time.sleep_ms(20)




mPython图形化示例
----------------
.. figure:: /_static/image/example/track/track_color.png
    :align: center
    :width: 1080