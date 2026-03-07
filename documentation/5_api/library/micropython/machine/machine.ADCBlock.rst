.. currentmodule:: machine
.. _machine.ADCBlock:

类 ADCBlock -- 控制 ADC 外设
======================================

.. class:: ADCBlock(id, *, bits=12)

   构造一个ADC块对象，用于控制ADC外设。

   *id* 是ADC块的标识符，例如0。

   *bits* 是ADC的分辨率，默认为12位。

   可用性：ESP32。

   .. method:: init(*, bits=12)

      初始化ADC块。

      *bits* 是ADC的分辨率。

   .. method:: deinit()

      取消初始化ADC块。

   .. method:: read_u16(pin)

      读取指定引脚上的ADC值并返回16位无符号整数。

      *pin* 是要读取的引脚。