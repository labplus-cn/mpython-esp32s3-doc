:mod:`machine` --- 与硬件相关的功能
====================================================

.. module:: machine
   :synopsis: 与硬件相关的功能

该 ``machine`` 模块包含与特定电路板上的硬件相关的特定功能。该模块中的大多数功能允许直接和不受限制地访问和控制系统上的硬件块（如CPU，定时器，总线等）。
使用不当，可能导致故障，锁定，电路板崩溃，以及在极端情况下硬件损坏。

.. _machine_callbacks:

关于 :mod:`machine` 模块的函数和类方法使用的回调的注释：所有这些回调应被视为在中断上下文中执行。
这对于ID> = 0的物理设备和具有负ID（例如-1）的"虚拟"设备都是如此（这些"虚拟"设备在真实硬件和实际硬件中断之上仍然是薄的垫片）。
请参见 :ref:`isr_rules`。

内存访问
---------

模块公开了三个用于原始内存访问的对象。

.. data:: mem8

    读取/写入8位内存。

.. data:: mem16

    读取/写入16位内存。

.. data:: mem32

    读取/写入32位内存。

使用下标表示法 ``[...]`` 来索引这些对象，使用感兴趣的地址。请注意，无论访问的内存大小如何，地址都是字节地址。

示例使用（寄存器特定于stm32微控制器）：

.. code-block:: python3

    import machine
    from micropython import const

    GPIOA = const(0x48000000)
    GPIO_BSRR = const(0x18)
    GPIO_IDR = const(0x10)

    # set PA2 high
    machine.mem32[GPIOA + GPIO_BSRR] = 1 << 2

    # read PA3
    value = (machine.mem32[GPIOA + GPIO_IDR] >> 3) & 1

复位相关函数
------------

.. function:: reset()

   以类似于按下外部RESET按钮的方式对设备进行硬复位。

.. function:: soft_reset()

   对解释器执行软复位，删除所有Python对象并重置Python堆。

.. function:: reset_cause()

   获取复位原因。有关可能的返回值，请参见 :ref:`常量 <machine_constants>`。

.. function:: bootloader([value])

   重置设备并进入其引导加载程序。这通常用于将设备置于可以用新固件编程的状态。

   一些端口支持传入可选的 *value* 参数，该参数可以控制进入哪个引导加载程序，向其传递什么，或其他事情。

中断相关函数
-------------

以下函数允许控制中断。一些系统需要中断才能正常运行，因此长时间禁用它们可能会损害核心功能，例如看门狗定时器可能会意外触发。
中断应该只在最短的时间内禁用，然后重新启用到它们之前的状态。例如：

.. code-block:: python3

    import machine

    # 禁用中断
    state = machine.disable_irq()

    # 在这里做少量时间关键的工作

    # 启用中断
    machine.enable_irq(state)


.. function:: disable_irq()

   禁用中断请求。
   返回先前的IRQ状态，该状态应被视为不透明值。
   此返回值应传递给 `enable_irq()` 函数，以在调用 `disable_irq()` 之前将中断恢复到其原始状态。

.. function:: enable_irq(state)

   重新启用中断请求。
   *state* 参数应该是从最近一次调用 `disable_irq()` 函数返回的值。

电源相关函数
-------------

.. function:: freq([hz])

    返回CPU频率（以赫兹为单位）。

    在某些端口上，这也可以通过传入 *hz* 来设置CPU频率。

.. function:: idle()

   对CPU进行时钟门控，在短期或长期内任何时候都有助于降低功耗。外设继续工作，一旦触发任何中断，或在CPU暂停后最多一毫秒，执行就会恢复。

   建议在任何持续检查外部变化（即轮询）的紧密循环中调用此函数。这将减少功耗，而不会显著影响性能。要进一步降低功耗，请参见 :func:`lightsleep`、:func:`time.sleep()` 和 :func:`time.sleep_ms()` 函数。

.. function:: sleep()

   .. note:: 此函数已弃用，请改用无参数的 :func:`lightsleep()`。

.. function:: lightsleep([time_ms])
              deepsleep([time_ms])

   停止执行以尝试进入低功率状态。

   如果指定了 *time_ms*，则这将是睡眠持续的最长时间（以毫秒为单位）。否则，睡眠可以无限期地持续。

   无论是否有超时，如果有需要处理的事件，执行都可能随时恢复。这些事件或唤醒源应该在睡眠之前配置，如 `Pin` 更改或 `RTC` 超时。

   lightsleep和deepsleep的精确行为和省电能力在很大程度上取决于底层硬件，但一般属性是：

   * lightsleep具有完整的RAM和状态保留。唤醒后，执行从请求睡眠的点继续，所有子系统都可操作。

   * deepsleep可能不会保留RAM或系统的任何其他状态（例如外设或网络接口）。唤醒后，执行从主脚本继续，类似于硬复位或上电复位。`reset_cause()` 函数将返回 `machine.DEEPSLEEP`，这可用于区分深度睡眠唤醒与其他复位。

.. function:: wake_reason()

   获取唤醒原因。有关可能的返回值，请参见 :ref:`常量 <machine_constants>`。

   可用性：ESP32，WiPy。

其他函数
---------

.. function:: unique_id()

   返回一个字节字符串，其中包含板/SoC的唯一标识符。如果底层硬件允许，它将从板/SoC实例变化到另一个实例。
   长度因硬件而异（如果您需要短ID，请使用完整值的子字符串）。在某些MicroPython端口中，ID对应于网络MAC地址。

.. function:: time_pulse_us(pin, pulse_level, timeout_us=1000000, /)

   在给定的 *pin* 上测试脉冲，并以微秒为单位返回脉冲的持续时间。 *pulse_level* 参数应为0以测试低脉冲或1以测试高脉冲。

   如果引脚的当前输入值与 *pulse_level* 不同，该函数首先（*）等待，直到引脚输入变为等于 *pulse_level*，然后（**）测量引脚等于 *pulse_level* 的持续时间。
   如果引脚已经等于 *pulse_level*，则计时立即开始。

   如果在等待上面标记为（*）的条件时超时，函数将返回-2，如果在上面标记为（**）的主要测量期间超时，则返回-1。两种情况的超时相同，由 *timeout_us* 给出（以微秒为单位）。

.. function:: bitstream(pin, encoding, timing, data, /)

   通过位翻转指定的 *pin* 来传输 *data*。*encoding* 参数指定位的编码方式，*timing* 是特定于编码的时序规范。

   支持的编码有：

     - ``0`` 表示"高低"脉冲持续时间调制。这将以定时脉冲的形式传输0和1位，从最高有效位开始。
       *timing* 必须是纳秒的四元组，格式为 ``(high_time_0, low_time_0, high_time_1, low_time_1)``。例如，
       ``(400, 850, 800, 450)`` 是800kHz下WS2812 RGB LED的时序规范。

   时序的准确性因端口而异。在48MHz的Cortex M0上，最佳精度为+/- 120ns，而在更快的MCU（ESP8266，ESP32，STM32，Pyboard）上，
   精度将接近+/-30ns。

   .. note:: 对于控制WS2812 / NeoPixel条带，请参阅 :mod:`neopixel` 模块以获取更高级的API。

.. function:: rng()

   返回一个24位软件生成的随机数。

   可用性：WiPy。

.. _machine_constants:

常量
-----

.. data:: machine.IDLE
          machine.SLEEP
          machine.DEEPSLEEP

    IRQ唤醒值。

.. data:: machine.PWRON_RESET
          machine.HARD_RESET
          machine.WDT_RESET
          machine.DEEPSLEEP_RESET
          machine.SOFT_RESET

    复位原因。

.. data:: machine.WLAN_WAKE
          machine.PIN_WAKE
          machine.RTC_WAKE

    唤醒原因。

类
---

.. toctree::
   :maxdepth: 1

   machine.Pin.rst
   machine.Signal.rst
   machine.ADC.rst
   machine.ADCBlock.rst
   machine.PWM.rst
   machine.UART.rst
   machine.SPI.rst
   machine.I2C.rst
   machine.I2CTarget.rst
   machine.I2S.rst
   machine.RTC.rst
   machine.Timer.rst
   machine.Counter.rst
   machine.Encoder.rst
   machine.WDT.rst
   machine.SD.rst
   machine.SDCard.rst
   machine.USBDevice.rst