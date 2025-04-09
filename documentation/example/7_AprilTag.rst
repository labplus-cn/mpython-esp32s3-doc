AprilTag识别
==============

代码
-----------
例程::

    from mpython import *
    import smartcamera_new as smartcamera
    import time

    smart_camera = smartcamera.SmartCamera(tx=Pin.P16, rx=Pin.P15)
    smart_camera.apriltag_init(_choice=1)
    smart_camera.apriltag.set_tag_families(16)
    while True:
        smart_camera.apriltag.recognize()
        if smart_camera.apriltag.tag_family != None:
            print(smart_camera.apriltag.tag_family)
            print(smart_camera.apriltag.tag_id)
        time.sleep_ms(20)


mPython图形化示例
-----------
.. figure:: /_static/image/example/qrcode/AprilTag.png
    :align: center
    :width: 1080

