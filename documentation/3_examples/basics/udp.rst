UDP通信
=============================

.. contents:: 目录
   :local:
   :depth: 2


概述
----

本章节介绍如何在 MicroPython 中使用 UDP（User Datagram Protocol）进行网络通信。UDP 是一种无连接、面向数据报的协议，适用于对实时性要求高但不要求数据可靠性的场景。

MicroPython 提供了轻量级的 ``usocket`` 模块，允许在受限设备上实现 UDP 通信。

前提条件
--------

- 已成功连接 Wi-Fi 或 Ethernet 网络（取决于设备）
- 设备支持 ``usocket`` 模块

UDP 客户端示例
--------------

以下示例展示如何创建一个 UDP 客户端，向指定地址和端口发送数据：

.. code-block:: python

    import usocket

    udp = usocket.socket(usocket.AF_INET, usocket.SOCK_DGRAM)

    server_ip = "192.168.1.100"
    server_port = 5005
    message = b"Hello, UDP Server"

    udp.sendto(message, (server_ip, server_port))
    udp.close()

UDP 服务器示例
--------------

以下示例展示如何创建一个 UDP 服务器，监听指定端口并接收数据：

.. code-block:: python

    import usocket

    udp = usocket.socket(usocket.AF_INET, usocket.SOCK_DGRAM)
    udp.bind(("0.0.0.0", 5005))

    print("Listening on UDP port 5005...")

    while True:
        data, addr = udp.recvfrom(1024)
        print("Received from {}: {}".format(addr, data))

注意事项
--------

- UDP 是无连接协议，不保证数据包的到达与顺序。
- 数据大小受限于 MTU，一般建议每次发送小于 1472 字节。
- 关闭 socket 前需调用 ``close()``，避免资源泄露。

应用场景
--------

- 局域网广播或组播通信
- 低延迟 IoT 数据上传
- 实时传感器数据传输

相关模块
--------

- ``usocket``: MicroPython 的 socket 接口模块
- ``network``: 用于网络接口配置（如 WLAN）

参考资料
--------

- MicroPython 官方文档: https://docs.micropython.org
- UDP 协议介绍: https://tools.ietf.org/html/rfc768

