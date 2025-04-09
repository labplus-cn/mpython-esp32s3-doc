自定义模型功能-图像分类
==============

代码
-----------
例程::

    from mpython import *
    import smartcamera_new as smartcamera
    import time

    smart_camera = smartcamera.SmartCamera(tx=Pin.P16, rx=Pin.P15)
    smart_camera.kmodel_init(1,'/sd/xxx.kmodel',128,128)
    while True:
        smart_camera.kpu_model.recognize()
        if smart_camera.kpu_model.id != None:
            if smart_camera.kpu_model.max_score >= 0.5:
                print(smart_camera.kpu_model.id)
                print(smart_camera.kpu_model.max_score)
        time.sleep_ms(10)



mPython图形化示例
-----------
.. figure:: /_static/image/example/model_detect/2.png
    :align: center
    :width: 1080
