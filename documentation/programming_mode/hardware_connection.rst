硬件连接方式
=======================================

一、AI摄像头与乐动掌控
~~~~~~~~~~~~~~~~~~~~~
1、连接硬件
---------------------

如图示将AI摄像头连接至P15、P16引脚（或其他可用串口的引脚）

.. figure:: /_static/image/hardware_connection/1.jpg
    :align: center
    :width: 600

.. figure:: /_static/image/hardware_connection/2.jpg
    :align: center
    :width: 600


2、编写程序
---------------------
打开mPython软件，连接上乐动掌控，选择连接的引脚，刷入程序

乐动掌控与摄像头成功通信，控制台会输出“==AI摄像头通信成功==”

.. figure:: /_static/image/hardware_connection/3.png
    :align: center
    :width: 1080


二、固件烧录
~~~~~~~~~~~~~~~~~~~~~
将摄像头type-c usb线连接电脑，打开mPython软件，选择4.0摄像头固件刷入

.. Attention:: 摄像头更新固件后，搭配乐动掌控最好也更新一次固件

.. figure:: /_static/image/k210.png
    :align: center
    :width: 1080