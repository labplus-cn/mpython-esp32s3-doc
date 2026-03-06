.. _tutorials_radio:

无线广播
===============

掌控板提供2.4G的无线射频通讯,共 13 Channel。可实现一定区域内的简易组网通讯。在相同通道下,成员可接收广播消息。就类似,对讲机一样。在相同频道下,实现通话。

.. figure:: /_static/image/tutorials/radio/radio.png
    :align: center
    :width: 200

    对讲机

radio
--------

.. literalinclude:: /_static/examples/radio/radio.py
    :caption: 发送广播消息示例
    :linenos:

.. literalinclude:: /_static/examples/radio/radio2.py
    :caption: 发送数据给特定mac地址设备示例
    :linenos:

.. literalinclude:: /_static/examples/radio/radio3.py
    :caption: 接收消息示例
    :linenos:


.. class:: MPythonESPNow(wifi_ch=0)
    :noindex:

    实例化Radio

    :param wifi_ch: 设置信道 0-14
    :type wifi_ch: int


.. class:: MPythonESPNow

    .. function:: get_mac(mode)
        :noindex:

        获取自身网卡mac地址

        :param mode: 0 sta地址/1 ap地址 
        :type mode: int
        :return: 16进制字符串mac地址
        :rtype: str



.. class:: MPythonESPNow

    .. function:: broadcast_data(msg) 
        :noindex:

        发送无线广播数据，群发

        :param msg: 无线广播数据
        :type msg: str


.. class:: MPythonESPNow

    .. function:: set_add_peer(peer_mac) 
        :noindex:

        将提供的mac地址注册为对等地址,私发需要注册，群发不需要

        :param peer_mac: mac地址 16进制字符串
        :type peer_mac: str


.. class:: MPythonESPNow

    .. function:: send_msg(peer_mac, msg)
        :noindex:

        发送无线广播数据，私发

        :param peer_mac: mac地址 16进制字符串
        :type peer_mac: str
        :param msg: 无线广播数据
        :type msg: str



.. class:: MPythonESPNow

    .. function:: set_irq_callback(espnow_recv_callback)
        :noindex:

        设置接收消息回调处理函数

        :param espnow_recv_callback: 回调函数
        :type espnow_recv_callback: function



.. function:: espnow_recv_callback(espnow_obj)
    :noindex:

     espnow_mac, espnow_data, espnow_rssi = espnow_obj.recv_msg() 接收消息对象

    :var str espnow_mac: 广播消息设备mac地址
    :var str espnow_data: 接收消息
    :var str espnow_rssi: 广播信号强度 dBm


