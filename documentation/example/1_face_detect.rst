人脸检测
==============

代码
-----------
例程::

    from mpython import *
    import smartcamera_new as smartcamera
    import time

    smart_camera = smartcamera.SmartCamera(tx=Pin.P16, rx=Pin.P15)
    smart_camera.face_detect_init(1)
    while True:
        smart_camera.face_detect.recognize()
        if smart_camera.face_detect.face_num != None:
            print(str('人脸数量：') + str(smart_camera.face_detect.face_num))
            print(str('置信度：') + str(smart_camera.face_detect.max_score))
        time.sleep_ms(20)




mPython图形化示例
-----------
.. figure:: /_static/image/example/face_detect/face_detect.png
    :align: center
    :width: 1080


方法
-----------


.. _face_detect:

.. class:: smart_camera.face_detect
   :synopsis: 人脸检测实例化对象

.. method::  face_detect_init(_choice=1)

``_choice`` -整型 摄像头序号 内置摄像头1

例::

    smart_camera.face_detect_init(1)

.. method::  face_detect.recognize() 
运行人脸识别

.. method::  face_detect.face_num
人脸检测数量 整型

.. method::  face_detect.max_score
人脸检测概率 浮点型 范围：[0-1]