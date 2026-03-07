`machine.I2S` --- Inter-IC Sound总线协议
====================================================

I2S是一种用于连接数字音频设备的同步串行协议。
在物理层面，总线由3条线组成：SCK、WS、SD。
I2S类支持控制器操作。不支持外设操作。
I2S类目前作为技术预览版提供。在预览期间，鼓励用户提供反馈。
基于此反馈，I2S类API和实现可能会更改。

I2S对象可以使用以下方式创建和初始化：

.. code-block:: python

    from machine import I2S
    from machine import Pin

    # ESP32
    sck_pin = Pin(14)   # 串行时钟输出
    ws_pin = Pin(13)    # 字时钟输出
    sd_pin = Pin(12)    # 串行数据输出

    # 或

    # PyBoards
    sck_pin = Pin("Y6")   # 串行时钟输出
    ws_pin = Pin("Y5")    # 字时钟输出
    sd_pin = Pin("Y8")    # 串行数据输出

    audio_out = I2S(2,
                    sck=sck_pin, ws=ws_pin, sd=sd_pin,
                    mode=I2S.TX,
                    bits=16,
                    format=I2S.MONO,
                    rate=44100,
                    ibuf=20000)

    audio_in = I2S(2,
                   sck=sck_pin, ws=ws_pin, sd=sd_pin,
                   mode=I2S.RX,
                   bits=32,
                   format=I2S.STEREO,
                   rate=22050,
                   ibuf=20000)

支持3种操作模式：
- 阻塞模式
- 非阻塞模式
- asyncio

**阻塞模式：**

.. code-block:: python

    num_written = audio_out.write(buf) # 阻塞直到缓冲区为空

    num_read = audio_in.readinto(buf) # 阻塞直到缓冲区填满

**非阻塞模式：**

.. code-block:: python

    audio_out.irq(i2s_callback)         # 当缓冲区为空时调用i2s_callback
    num_written = audio_out.write(buf)  # 立即返回

    audio_in.irq(i2s_callback)          # 当缓冲区填满时调用i2s_callback
    num_read = audio_in.readinto(buf)   # 立即返回

**asyncio：**

.. code-block:: python

    swriter = asyncio.StreamWriter(audio_out)
    swriter.write(buf)
    await swriter.drain()

    sreader = asyncio.StreamReader(audio_in)
    num_read = await sreader.readinto(buf)

一些编解码设备如WM8960或SGTL5000需要单独初始化才能与I2S类一起工作。
对于这些设备，提供了单独的驱动程序，这些驱动程序还提供了控制音量、音频处理和其他功能的方法。

.. currentmodule:: machine

.. class:: I2S(id, *, sck, ws, sd, mck=None, mode, bits, format, rate, ibuf)

    构造给定id的I2S对象：

    *id* 标识特定的I2S总线；它是特定于板和端口的

    所有端口支持的关键字参数：

    - *sck* 是串行时钟线的引脚对象
    - *ws* 是字选择线的引脚对象
    - *sd* 是串行数据线的引脚对象
    - *mck* 是主时钟线的引脚对象；主时钟频率是采样率 * 256
    - *mode* 指定接收或发送
    - *bits* 指定样本大小（位），16或32
    - *format* 指定通道格式，STEREO或MONO
    - *rate* 指定音频采样率（Hz）；这是ws信号的频率
    - *ibuf* 指定内部缓冲区长度（字节）

    对于所有端口，DMA在后台连续运行，允许用户应用程序在样本数据在内部缓冲区和I2S外设单元之间传输时执行其他操作。
    增加内部缓冲区的大小有可能增加用户应用程序在发生下溢（例如write方法）或溢出（例如readinto方法）之前可以执行非I2S操作的时间。

    .. method:: init(sck, ...)

        参见构造函数的参数描述

    .. method:: deinit()

        取消初始化I2S总线

    .. method:: readinto(buf)

        将音频样本读入由buf指定的缓冲区。buf必须支持缓冲区协议，如bytearray或array。
        "buf"字节顺序是小端序。对于立体声格式，左声道样本先于右声道样本。对于单声道格式，使用左声道样本数据。
        返回读取的字节数

    .. method:: write(buf)

        写入包含在buf中的音频样本。buf必须支持缓冲区协议，如bytearray或array。
        "buf"字节顺序是小端序。对于立体声格式，左声道样本先于右声道样本。对于单声道格式，样本数据被写入左右声道。
        返回写入的字节数

    .. method:: irq(handler)

        设置回调函数。当缓冲区为空（write方法）或变满（readinto方法）时调用handler。
        设置回调会将write和readinto方法更改为非阻塞操作。
        handler在MicroPython调度器的上下文中被调用。

    .. staticmethod:: shift(*, buf, bits, shift)

        对buf中包含的所有样本进行按位移位。bits指定样本大小（位）。shift指定每个样本要移位的位数。
        正数表示左移，负数表示右移。
        通常用于音量控制。每位移位会使样本音量变化6dB。

    .. data:: RX

        用于将I2S总线模式初始化为接收

    .. data:: TX

        用于将I2S总线模式初始化为发送

    .. data:: STEREO

        用于将I2S总线格式初始化为立体声

    .. data:: MONO

        用于将I2S总线格式初始化为单声道