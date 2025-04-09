20类识别
==============

代码
-----------
例程::

    from mpython import *
    import smartcamera_new as smartcamera
    import time

    smart_camera = smartcamera.SmartCamera(tx=Pin.P16, rx=Pin.P15)
    smart_camera.yolo_detect_init(1)
    while True:
        smart_camera.yolo_detect.recognize()
        if smart_camera.yolo_detect.id != None:
            print(str('类别：') + str(smart_camera.yolo_detect.category_list[smart_camera.yolo_detect.id]))
            print(str('置信度：') + str(smart_camera.yolo_detect.max_score))
        time.sleep_ms(20)


mPython图形化示例
-----------
.. figure:: /_static/image/example/yolo_detect/yolo_detect.png
    :align: center
    :width: 1080