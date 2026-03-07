.. currentmodule:: machine
.. _machine.Timer:

类 Timer -- 控制硬件定时器
====================================

硬件定时器处理周期和事件的计时。定时器可能是MCU和SoC中最灵活和多样化的硬件类型，具有广泛的不同功能和限制。

Timer类提供了在给定周期（或延迟后）执行回调的基线操作，并允许特定板定义更多非标准行为（因此不会移植到其他板）。

有关Timer回调的重要约束，请参见 :ref:`machine_callbacks`。

.. note::

    无法在中断处理程序（中断）中分配内存，因此在处理程序中引发的异常不会提供太多信息。
    请参阅 :func:`micropython.alloc_emergency_exception_buf` 如何帮助解决此限制。

构造函数
------------

.. class:: Timer(id, ...)

   构造给定id的新定时器对象。

   - ``id`` - 任何正整数


方法
-------

.. method:: Timer.init(*, mode=Timer.PERIODIC, period=-1, callback=None)


   - ``mode`` - 定时器模式，可以是以下之一：

       - ``Timer.ONE_SHOT`` - 定时器运行一次，直到配置的通道周期到期。
       - ``Timer.PERIODIC`` - 定时器以配置的通道频率周期性运行。
   - ``period`` - 定时器执行周期（毫秒），每period毫秒执行一次。周期范围：0 < period <= 3435973836
   - ``callback`` - 定时器回调函数


初始化定时器，示例::

    tim.init(period=100)                         # 周期为100ms的周期性定时器
    tim.init(mode=Timer.ONE_SHOT, period=1000)   # 1000ms后触发一次的一次性定时器


.. method:: Timer.value()

   获取并返回当前定时器计数器值。

::

    value = tim.value()
    print(value)

.. method:: Timer.deinit()


   取消初始化定时器。停止定时器并禁用定时器外设。


常量
---------

.. data:: Timer.ONE_SHOT
.. data:: Timer.PERIODIC


.. literalinclude:: /_static/examples/timer/timer_led_blink.py
    :caption: 定时器控制LED闪烁
    :linenos: