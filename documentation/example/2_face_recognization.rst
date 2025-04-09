人脸识别
==============

代码
-----------
例程::

    from mpython import *
    import smartcamera_new as smartcamera
    import time

    smart_camera = smartcamera.SmartCamera(tx=Pin.P16, rx=Pin.P15)
    smart_camera.face_recognize_init(3, 80, 1)
    smart_camera.fcr.add_face()
    while True:
        smart_camera.fcr.recognize()
        if smart_camera.fcr.id != None:
            print(smart_camera.fcr.id)
            print(smart_camera.fcr.max_score)
        time.sleep_ms(20)




mPython图形化示例
-----------
.. figure:: /_static/image/example/face_recognization/face_recognization.png
    :align: center
    :width: 1080