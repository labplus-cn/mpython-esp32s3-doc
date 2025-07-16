WiFi
=====================

.. contents:: 目录
   :local:
   :depth: 2

概述
----
介绍其 WiFi 功能的基本使用方法。



WiFi 工作模式
-------------
乐动掌控2.0支持 2.4G WiFi

1. Station 模式（STA）
   - 连接到无线接入点(AP)
2. SoftAP 模式
   - 作为接入点供其他设备连接



Station 接入点模式
-------------------

.. image:: /_static/image/example/wifi/wifi.png
    :width: 70%
    :align: center

.. literalinclude:: /_static/examples/network/wifi.py
    :caption: Station 接入点模式
    :name: Station 接入点模式




SoftAP 热点模式
-------------------

.. image:: /_static/image/example/wifi/ap.png
    :width: 70%
    :align: center

.. literalinclude:: /_static/examples/network/ap.py
    :caption: SoftAP 热点模式
    :name: SoftAP 热点模式


API 参考
-------

主要 WiFi API
~~~~~~~~~~~~

- ``wifi.connectWiFi("ssid, "psd")`` - 连接WiFi
- ``wifi.disconnectWiFi()`` - 断开连接
- ``wifi.sta.isconnected()`` - 检查是否连接成功
- ``wifi.sta.ifconfig()`` - 获取WiFi配置
- ``wifi.enable_APWiFi('ssid', 'psd', channel=)`` - 开启 SoftAP 模式
- ``wifi.disable_APWiFi()`` - 关闭 SoftAP 模式




常见问题
-------

Q: 无法连接到 AP
   - 检查 SSID 和密码是否正确
   - 检查 WiFi 是否是2.4G频段
   - 检查路由器设置
   - 检查信号强度

Q: SoftAP 无法被搜索到
   - 检查是否设置了正确的频道
   - 检查最大连接数是否设置合理

