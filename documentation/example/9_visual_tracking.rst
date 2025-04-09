图像巡线
==============


图像巡线
-----------
例程::

    from mpython import *
    import smartcamera_new as smartcamera
    import time

    smart_camera = smartcamera.SmartCamera(tx=Pin.P16, rx=Pin.P15)
    smart_camera.color_statistics_init(_choice=1)
    smart_camera.color_statistics.set_img_grayscale_threshold((200, 255))
    smart_camera.color_statistics.set_line_grayscale_threshold((230, 255))
    while True:
        smart_camera.color_statistics.recognize()
        print(smart_camera.color_statistics.line_get_regression_data[6])
        time.sleep_ms(20)



mPython图形化示例
-----------
.. figure:: /_static/image/example/visual_tracking/visual_tracking.png
    :align: center
    :width: 1080

