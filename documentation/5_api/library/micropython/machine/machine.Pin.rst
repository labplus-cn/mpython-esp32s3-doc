.. currentmodule:: machine
.. _machine.Pin:

类 Pin -- 控制 I/O 引脚
============================

.. class:: Pin(id, mode=-1, pull=-1, *, value=None, drive=0, alt=-1)

   访问与给定 ``id`` 关联的引脚外设（GPIO引脚）。
   如果在构造函数中给出了附加参数，则它们用于初始化引脚。
   未指定的任何设置将保持其先前的状态。

   .. Attention:: mPython 掌控板提供自有的引脚映射,将引脚映射为ESP32的GPIO。如,掌控板的P0引脚对应ESP32的IO33,则你可以使用 ``Pin.P0`` 来替换 ``33`` 。

   参数：

     - ``id`` 是必需的，可以是任何对象。可能的值
       取决于板，但包括整数（用于GPIO编号），
       字符串（用于板特定的引脚名称）和元组（用于端口和
       引脚编号，例如 ``('A', 1)``）。如果使用mPython，可用Pin.P(0~20),例如(Pin.P0)P0引脚提供映射为GPIO。

     - ``mode`` 指定引脚模式，可以是以下之一：

       - ``Pin.IN`` - 引脚配置为输入。如果视为输出，引脚
         处于高阻抗状态。

       - ``Pin.OUT`` - 引脚配置为（正常）输出。

       - ``Pin.OPEN_DRAIN`` - 引脚配置为开漏输出。
         开漏输出的工作方式如下：如果输出值设置为0，引脚
         在低电平有效；如果输出值为1，引脚处于高阻抗状态。
         并非所有端口都实现此模式，或者某些端口可能仅在特定引脚上实现。

       - ``Pin.ALT`` - 引脚配置为执行替代功能，
         这是特定于端口的。对于以此方式配置的引脚，任何其他
         Pin方法（除了 ``Pin.init()``）都不适用（调用它们将
         导致未定义或特定于端口的结果）。并非所有端口都实现
         此模式。

       - ``Pin.ALT_OPEN_DRAIN`` - 与 ``Pin.ALT`` 相同，但引脚配置为开漏。
         并非所有端口都实现此模式。

       - ``Pin.ANALOG`` - 引脚配置为模拟输入（参见 ``ADC`` 类）。
         并非所有端口都实现此模式。

     - ``pull`` 指定引脚是否连接有（弱）上拉电阻，可以是：

       - ``None`` - 无上拉或下拉电阻。
       - ``Pin.PULL_UP`` - 启用上拉电阻。
       - ``Pin.PULL_DOWN`` - 启用下拉电阻。

     - ``value`` 仅对 ``Pin.OUT`` 和 ``Pin.OPEN_DRAIN`` 模式有效，
       指定初始输出引脚值，否则引脚外设的
       状态不变。

     - ``drive`` 指定引脚的输出功率，可以是以下之一
       ``Pin.DRIVE_0``, ``Pin.DRIVE_1`` 等，驱动强度递增。
       实际电流驱动能力取决于端口。
       并非所有端口都实现此参数。

     - ``alt`` 指定替代功能，它可以采用特定于端口的值。
       此参数仅对 ``Pin.ALT`` 和
       ``Pin.ALT_OPEN_DRAIN`` 模式有效。当引脚支持多个
       替代功能时可以使用。如果引脚仅支持一个替代功能
       则不需要此参数。并非所有端口都实现此参数。

   示例用法::

       from machine import Pin

       # 在引脚 #32 上创建输出引脚
       p0 = Pin(32, Pin.OUT)

       # 将值设置为低然后高
       p0.value(0)
       p0.value(1)

       # 在引脚 #33 上创建输入引脚，带有上拉电阻
       p2 = Pin(33, Pin.IN, Pin.PULL_UP)

       # 配置中断回调
       p2.irq(trigger=Pin.IRQ_FALLING, handler=lambda t:print("IRQ"))

.. method:: Pin.init(mode=-1, pull=-1, *, value=None, drive=0, alt=-1)

   使用给定的参数重新初始化引脚。仅设置指定的
   参数，其他参数保持其先前的值。
   有关参数的详细信息，请参见构造函数文档。

   返回 ``None``。

.. method:: Pin.value([x])

   此方法允许获取和设置引脚的值，具体取决于
   是否提供参数 ``x``。

   如果省略参数，则此方法获取引脚的数字逻辑电平，
   返回0或1，分别对应低电压和高电压信号。
   此方法的行为取决于引脚的模式：

     - ``Pin.IN`` - 方法返回引脚上存在的实际输入值。
     - ``Pin.OUT`` - 方法的行为和返回值未定义。
     - ``Pin.OPEN_DRAIN`` - 如果引脚处于状态'0'，则方法的行为和
       返回值未定义。否则，如果引脚处于
       状态'1'，方法返回引脚上存在的实际输入值。

   如果提供参数，则此方法设置引脚的数字逻辑电平。
   参数 ``x`` 可以是任何可转换为布尔值的东西。
   如果转换为 ``True``，引脚设置为状态'1'，否则设置
   为状态'0'。此方法的行为取决于引脚的模式：

     - ``Pin.IN`` - 值存储在引脚的输出缓冲区中。
       引脚状态不变，保持高阻抗模式。存储的
       值将在引脚更改为
       ``Pin.OUT`` 或 ``Pin.OPEN_DRAIN`` 模式时立即在引脚上激活。
     - ``Pin.OUT`` - 输出缓冲区立即设置为给定值。
     - ``Pin.OPEN_DRAIN`` - 如果值为'0'，引脚设置为低电压
       状态。否则引脚设置为高阻抗状态。

   设置值时返回 ``None``。

.. method:: Pin.__call__([x])

   Pin对象是可调用的。调用方法提供了一个（快速）快捷方式来设置和获取
   引脚的值。它等同于 ``Pin.value([x])``。请参阅
   :meth:`Pin.value` 获取更多详细信息。

.. method:: Pin.on()

   将引脚设置为高逻辑电平。

.. method:: Pin.off()

   将引脚设置为低逻辑电平。

.. method:: Pin.low()

   将引脚设置为 ``0`` 输出电平。

   可用性：mimxrt, nrf, renesas-ra, rp2, samd, stm32。

.. method:: Pin.high()

   将引脚设置为 ``1`` 输出电平。

   可用性：mimxrt, nrf, renesas-ra, rp2, samd, stm32。

.. method:: Pin.mode([mode])

   获取或设置引脚模式。

   有关 ``mode`` 参数的更多信息，请参见构造函数文档。

   可用性：cc3200, stm32。

.. method:: Pin.pull([pull])

   获取或设置引脚上拉状态。

   有关 ``pull`` 参数的更多信息，请参见构造函数文档。

   可用性：cc3200, stm32。

.. method:: Pin.drive([drive])

   获取或设置引脚驱动强度。

   有关 ``drive`` 参数的更多信息，请参见构造函数文档。

   可用性：cc3200。

.. method:: Pin.toggle()

   将输出引脚从 ``0`` 切换到 ``1`` 或反之亦然。

   可用性：cc3200, esp32, esp8266, mimxrt, rp2, samd。

.. _Pin.irq:

.. method:: Pin.irq(handler=None, trigger=(Pin.IRQ_FALLING | Pin.IRQ_RISING), *, priority=1, wake=None, hard=False)

   配置当引脚的触发源激活时要调用的中断处理程序。
   如果引脚模式为 ``Pin.IN``，则触发源是引脚上的外部值。
   如果引脚模式为 ``Pin.OUT``，则触发源是引脚的输出缓冲区。
   否则，如果引脚模式为 ``Pin.OPEN_DRAIN``，则触发源是输出
   状态'0'的缓冲区和状态'1'的外部引脚值。

   参数：

     - ``handler`` 是中断触发时要调用的可选函数。
       处理程序必须接受恰好一个参数，即Pin实例。

     - ``trigger`` 配置可以触发中断的事件。可能的值为：

       - ``Pin.IRQ_FALLING`` - 下降沿中断。
       - ``Pin.IRQ_RISING`` - 上升沿中断。
       - ``Pin.IRQ_LOW_LEVEL`` - 低电平中断。
       - ``Pin.IRQ_HIGH_LEVEL`` - 高电平中断。

       这些值可以OR组合以在多个事件上触发。

     - ``priority`` 设置中断优先级级别。它可以采用特定于端口的值，
       但较高的值始终表示较高的优先级。

     - ``wake`` 选择此中断可以唤醒系统的电源模式。
       它可以是 ``machine.IDLE``、``machine.SLEEP`` 或 ``machine.DEEPSLEEP``。这些
       值也可以OR组合，使引脚在多个
       电源模式下生成中断。

     - ``hard`` 如果为True，则使用硬件中断。这减少了引脚
       变化和调用处理程序之间的延迟。硬件中断处理程序不得
       分配内存；有关更多信息，请参见 :ref:`isr_rules`。并非所有端口都支持
       此参数。

   返回一个回调对象。

常量
---------

板自有的引脚映射,将掌控板引脚映射为ESP32的GPIO

.. data:: Pin.P0
          Pin.P1
          Pin.P2
          Pin.P3
          Pin.P4
          Pin.P5
          Pin.P6
          Pin.P7
          Pin.P8
          Pin.P9
          Pin.P10
          Pin.P11
          Pin.P13
          Pin.P14
          Pin.P15
          Pin.P16
          Pin.P19
          Pin.P20
          Pin.P23
          Pin.P24
          Pin.P25
          Pin.P26
          Pin.P27
          Pin.P28

以下常量用于配置引脚对象。请注意，并非所有
常量在所有端口上都可用。

.. data:: Pin.IN
          Pin.OUT
          Pin.OPEN_DRAIN
          Pin.ALT
          Pin.ALT_OPEN_DRAIN
          Pin.ANALOG

   选择引脚模式。

.. data:: Pin.PULL_UP
          Pin.PULL_DOWN
          Pin.PULL_HOLD

   选择是否有上拉/下拉电阻。使用 ``None`` 表示无拉。

.. data:: Pin.DRIVE_0
          Pin.DRIVE_1
          Pin.DRIVE_2

   选择引脚驱动强度。端口可能定义额外的驱动常量，
   数字越大表示驱动强度越大。

.. data:: Pin.IRQ_FALLING
          Pin.IRQ_RISING
          Pin.IRQ_LOW_LEVEL
          Pin.IRQ_HIGH_LEVEL

   选择IRQ触发类型。