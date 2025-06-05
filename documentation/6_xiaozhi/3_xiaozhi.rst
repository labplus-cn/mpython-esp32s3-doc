使用教程
========================

1. 初始配置
--------------------------------

1.1 WIFI配网
^^^^^^^^^^^^^^^^

- WIFI配网：指的是通过开发板 WIFI 的 热点功能，告诉开发板它以后去连接哪一个 WIFI 进行连接网络。

配网模式会在第一次烧录固件后出现，效果如下图：

- 根据屏幕提示，使用手机去搜索 WIFI 名称为：Xiaozhi-xxxx的WIFI，这个WIFI是由掌控板发出的，没有密码。

.. figure:: /../_static/image/xiaozhi/xiaozhi-1.png
    :align: center
    :width: 600

.. Note::

 这个网页是不需要网络的，有一些手机通过浏览器打开不了这个网址，所以如果这个网页打不开，请关闭你手机的网络数据，只开启WIFI连接着，再打开网址即可。

.. figure:: /../_static/image/xiaozhi/xiaozhi-2.png
    :align: center
    :width: 600

.. figure:: /../_static/image/xiaozhi/xiaozhi-3.png
    :align: center
    :width: 600

- 在这个网页中，输入开发板将要连接的WIFI，因为开发板需要网络去调用 AI 大模型的数据，所以你接下来要给开发板配置的WIFI，请确保有网络。

- 完成后在网页中输入我热点的名称和密码。

.. figure:: /../_static/image/xiaozhi/xiaozhi-4.png
    :align: center
    :width: 600

.. figure:: /../_static/image/xiaozhi/xiaozhi-5.png
    :align: center
    :width: 600

- 连接成功后，网页提示设备会重新启动，这个时候等待重启完成即可。

.. figure:: /../_static/image/xiaozhi/xiaozhi-6.png
    :align: center
    :width: 600

.. Note::

  开启的手机热点必须是2.4G频段网络，不然搜索不到。


1.2 激活设备
^^^^^^^^^^^^^^^^
- 在配网完成后，开发板会自动连接WIFI，到最后会卡在激活设备界面。
- 打开浏览器，输入网址：xiaozhi.me。浏览器用手机或者电脑都可以打开。 进入小智AI的网页后，点击控制台，用手机号登录。

.. figure:: /../_static/image/xiaozhi/xiaozhi-7.png
    :align: center
    :width: 600

.. figure:: /../_static/image/xiaozhi/xiaozhi-8.png
    :align: center
    :width: 600

- 登录完成后，在新界面中，点击添加设备。将开发板屏幕显示的 6 位设备码输入到网页上的验证码中。这样就绑定成功了。

.. figure:: /../_static/image/xiaozhi/xiaozhi-9.png
    :align: center
    :width: 600


1.3唤醒你的AI伙伴
^^^^^^^^^^^^^^^^
在重新启动后，你可以直接对开发板说 “你好，小智”，测试是否可以正常对话。