初始化AI摄像头
==============

.. _SmartCamera:

.. class:: SmartCamera(tx=Pin.P16, rx=Pin.P15)
   :synopsis: AI摄像头类

.. method::  SmartCamera(tx=Pin.P16, rx=Pin.P15)

``tx`` 
串口发送引脚

``rx``
串口接收引脚

例如::
    
    from mpython import *
    import smartcamera_new as smartcamera
    smartcamera.SmartCamera(tx=Pin.P16, rx=Pin.P15)


mPython图形化示例
-----------
.. figure:: /_static/image/example/face_detect/face_detect.png
    :align: center
    :width: 1080
