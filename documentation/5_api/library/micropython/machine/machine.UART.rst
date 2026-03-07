.. currentmodule:: machine
.. _machine.UART:

类 UART -- 双工串行通信总线
=============================================

UART 实现标准的 UART/USART 双工串行通信协议。在物理层面，它由 2 条线组成：RX 和 TX。通信使用字节进行（不要与字符串混淆）。

构造函数
--------

.. class:: UART(id, ...)

    构造一个 UART 对象

    - ``id`` - 串口编号: 1, 2  

    .. Attention:: 
    
    ``UART(id=0)`` 用于 REPL，不能使用！

    ::
    
        from machine import UART
        from machine import Pin

        uart = UART(1, baudrate=115200, rx=Pin.P15, tx=Pin.P16, timeout=10)

方法
----

.. method:: UART.init(baudrate=9600, bits=8, parity=None, stop=1, *, ...)

    使用给定参数初始化 UART 总线

    - ``baudrate`` - 波特率
    - ``bits``- 每个字符的位数，7、8 或 9。
    - ``parity``- 校验位: 0 表示偶校验，1 表示奇校验
    - ``rx`` , ``tx`` - UART 读写引脚
    - ``stop`` - 停止位数量: 1 或 2
    - ``timeout``- 超时时间（毫秒）< timeout ≤ 0x7FFF FFFF（十进制: 0 < timeout ≤ 2147483647）
    - ``txbuf`` - 指定 TX 缓冲区的字符长度
    - ``rxbuf`` - 指定 RX 缓冲区的字符长度

    .. Attention:: 

        * 所有引脚都可以用作串行输入 RX，除了 ``P2``、``P3``、``P4``、``P10`` 只能用作输入，其他所有引脚理论上都可以用作输出 TX。
        * ``GPIO 1`` 和 ``GPIO 3`` 用于 mPython 板的 USB 串口。当初始化 UART 定义 ``tx`` 和 ``rx`` 引脚时，通常不使用它们，除非你想使用 mPython 板的 USB 接口作为串行输出。

.. method:: UART.deinit()

   关闭 UART 总线。

.. method:: UART.any()

    返回一个整数，表示可以无阻塞读取的字符数。如果没有可用字符，将返回 0；如果有字符，将返回一个正数。即使有多个字符可用，它也可能返回 1。

   对于更复杂的可用字符查询，请使用 select.poll::

    poll = select.poll()
    poll.register(uart, select.POLLIN)
    poll.poll(timeout)

.. method:: UART.read([nbytes])

    读取字符。如果指定了 ``nbytes``，最多读取该数量的字节，否则读取尽可能多的数据。

    返回值: 包含读取字节的字节对象。超时返回 ``None``。

.. method:: UART.readinto(buf[, nbytes])

   读取字节到 ``buf``。如果指定了 ``nbytes``，最多读取该数量的字节。否则，最多读取 ``len(buf)`` 字节。

   返回值: 读取并存储到 ``buf`` 的字节数，或超时返回 ``None``。

.. method:: UART.readline()

   读取一行，以换行符结束。

   返回值: 读取的行或超时返回 ``None``。

.. method:: UART.write(buf)

   将 ``buf`` 中的字节写入总线。

   返回值: 写入的字节数或超时返回 ``None``。

.. method:: UART.sendbreak()

   在总线上发送一个中断条件。这会使总线保持低电平的时间长于正常传输字符所需的时间。