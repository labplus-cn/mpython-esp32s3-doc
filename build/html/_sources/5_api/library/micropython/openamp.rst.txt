:mod:`openamp` -- 非对称多处理(AMP)支持
==============================================

.. module:: openamp
   :synopsis: 非对称多处理(AMP)支持

该模块提供了标准的非对称多处理(AMP)支持。

类
-------

.. class:: RPMSG

    .. classmethod:: __init__(remote, name, [rx_cb])

        初始化RPMSG通道。

        参数:
            * ``remote``: 远程处理器ID
            * ``name``: 通道名称
            * ``rx_cb``: 接收回调函数（可选）

    .. method:: send(data)

        发送数据到远程处理器。

        参数:
            * ``data``: 要发送的数据（类似字节）

    .. method:: recv([timeout])

        从远程处理器接收数据。

        参数:
            * ``timeout``: 超时时间（毫秒，可选）

        返回值:
            接收到的数据（bytes对象），如果超时则返回None

    .. method:: close()

        关闭RPMSG通道。