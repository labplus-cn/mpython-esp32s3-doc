拍摄视频存储到TF卡
===================

例程::

    from mpython import *
    import smartcamera_new as smartcamera

    smart_camera = smartcamera.SmartCamera(tx=Pin.P16, rx=Pin.P15)
    smart_camera.video_capture(choice=1, path='/sd/capture.avi', interval=100000, quality=50, width=240, height=240, duration=10)

函数
-----------

.. method::  video_capture(choice=1, path='/sd/', interval=, quality=, width=, height=, duration=)
``choice`` -摄像头序号, 只能填1

``path`` -文件路径,比如/sd/tmp.avi，只支持avi

``interval``-录制的帧间隔，单位是微秒，fps = 1000000/interval， 默认 100000， 即每秒10帧

``quality``-jpeg 压缩质量（%）， 默认50

``width``-录制屏幕宽度， 默认240 

``height``-录制屏幕高度， 默认240

``duration``-录制时长，单位是秒


mPython图形化示例
----------------
.. figure:: /_static/image/example/video.png
    :align: center
    :width: 1080