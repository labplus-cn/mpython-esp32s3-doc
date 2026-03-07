.. currentmodule:: machine
.. _machine.ADC:

类 ADC -- 模数转换
=======================================

ADC类提供了模数转换器的接口，表示一个可以采样连续电压并将其转换为离散值的单个端点。

有关ADC采样的额外控制，请参见 `machine.ADCBlock`。

示例用法：

.. code-block:: python

    from machine import ADC

    adc = ADC(pin)        # 创建一个作用于引脚的ADC对象
    val = adc.read_u16()  # 读取0-65535范围内的模拟值
    val = adc.read_uv()   # 读取微伏单位的模拟值

构造函数
------------

.. class:: ADC(id, *, sample_ns, atten)

   访问与由 ``id`` 标识的源关联的ADC。此id可以是
   整数（通常指定通道号）、Pin对象或底层机器支持的其他值。

   如果提供了额外的关键字参数，它们将配置ADC的各个方面。
   如果未提供，这些设置将采用先前或默认值。设置包括：

   - ``sample_ns`` 是以纳秒为单位的采样时间。
   - ``atten`` 指定输入衰减。

   ESP32可用引脚有：IO39、IO36、IO35、IO33、IO34、IO32。掌控板的ADC引脚有P0、P1、P2、P3、P4、P10。

   详细引脚定义可查阅 `ESP32引脚功能表. <../../../_images/pinout_wroom_pinout.png>`_。

方法
-------

.. method:: ADC.init(*, sample_ns, atten)

   将给定设置应用于ADC。仅更改指定的参数。
   有关参数的描述，请参见上面的ADC构造函数。

.. method:: ADC.block()

   返回与此ADC对象关联的ADCBlock实例。
   此方法仅在端口支持ADCBlock类时存在。

.. method:: ADC.read_u16()

   执行模拟读取并返回0-65535范围内的整数。
   返回的值表示ADC获取的原始读数，缩放后最小值为0，最大值为65535。

.. method:: ADC.read_uv()

   执行模拟读取并返回微伏单位的整数值。
   特定端口决定此值是否经过校准以及如何校准。

ESP32特定方法
----------------------

.. method:: ADC.read( )

   读取ADC并返回结果。

.. method:: ADC.atten(db)

    此方法允许设置ADC输入的衰减级别。这允许更宽的可能输入电压范围，但以精度为代价（相同位数现在表示更宽的范围）。当未设置atten()时，默认值为0DB衰减。可能的衰减选项包括：
    
    - ``db``
 

        =================== ========== ======= ===================================  
        宏定义                衰减量     数值     满量程电压
        =================== ========== ======= =================================== 
        ``ADC.ATTN_0DB``     0dB衰减     0      1V
        ``ADC.ATTN_2_5DB``   2.5dB衰减   1      1.5V
        ``ADC.ATTN_6DB``     6dB衰减     2      2V
        ``ADC.ATTN_11DB``    11dB衰减    3      3.3V
        =================== ========== ======= =================================== 

.. method:: ADC.width(bit)

    设置数据宽度（分辨率）。ADC的分辨率是指它可以将收集的模拟信号转换为数字信号的精度，通常以"位"表示，例如，8位意味着ADC可以将指定范围内的电压信号映射到0 - 2^8-1，即0-255个数字值。更高的分辨率位意味着更精确的表示和更少的信息损失。
    
    - ``bit`` - 宽度选项：

        =================== ========== =============
        宏定义                数值        满量程   
        =================== ========== =============
        ``ADC.WIDTH_9BIT``    0         0x1ff(511)
        ``ADC.WIDTH_10BIT``   1         0x3ff(1023)
        ``ADC.WIDTH_11BIT``   2         0x7ff(2047)
        ``ADC.WIDTH_12BIT``   3         00xfff(4095)
        =================== ========== =============

示例::

      from machine import ADC, Pin

      adc = ADC(Pin(34))      # 创建一个ADC对象
      adc.atten(adc.ATTN_11DB)   # 设置3.3V范围
      x = adc.read()
      print(x)

常量
---------


衰减比
````````
.. data:: ADC.ATTN_0DB


.. data:: ADC.ATTN_2_5DB


.. data:: ADC.ATTN_6DB



.. data:: ADC.ATTN_11DB


数据宽度
````````
.. data:: ADC.WIDTH_9BIT



.. data:: ADC.WIDTH_10BIT



.. data:: ADC.WIDTH_11BIT



.. data:: ADC.WIDTH_12BIT