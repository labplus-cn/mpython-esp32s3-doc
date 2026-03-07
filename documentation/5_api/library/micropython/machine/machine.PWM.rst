.. currentmodule:: machine
.. _machine.PWM:

类 PWM -- 脉冲宽度调制
==================================

脉冲宽度调制（PWM）是一种使用数字手段获得模拟结果的技术。

构造函数
------------

.. class:: PWM(pin, freq, duty)

   创建一个与给定引脚关联的PWM对象。这允许你向引脚写入模拟值。

   - ``pin`` 是支持PWM的引脚对象。ESP32支持在引脚 ``GPIO0``、``GPIO2``、``GPIO4``、``GPIO5``、``GPIO10``、``GPIO12~19``、``GPIO21``、``GPIO22``、``GPIO23``、``GPIO25~27`` 上使用PWM。参见 `ESP32引脚分配. <../../../_images/pinout_wroom_pinout.png>`_
   - ``freq`` 是频率，0 < freq <= 78125 Hz
   - ``duty`` 是占空比，0 ≤ duty ≤ 0x03FF（十进制：0 ≤ duty ≤ 1023）

.. Important:: 可以在所有输出引脚上启用PWM。但是，有一些限制：所有PWM必须具有相同的频率，并且只有8个通道。

示例::

  from machine import PWM, Pin

  pwm = PWM (Pin(2), freq=1000,  duty=1023)    # 创建一个PWM对象


方法
------------

.. method:: PWM.init(freq, duty)

   使用给定的频率和占空比初始化PWM。

示例::

 pwm.init(1000, 500)


.. method:: PWM.freq([freq_val])

   当没有给出参数时，此函数获取并返回PWM频率。当给出参数时，此函数设置PWM频率，无返回值。

   - ``freq_val`` 是PWM频率，0 < freq ≤ 0x0001312D（十进制：0 < freq ≤ 78125 Hz）

示例::

 print(pwm.freq())
 print(pwm.freq(2000)

.. method:: PWM.duty([duty_val])

   当没有给出参数时，此函数获取并返回PWM占空比。当给出参数时，此函数设置PWM占空比。

   - ``duty_val`` 是占空比，0 ≤ duty ≤ 0x03FF（十进制：0 ≤ duty_val ≤ 1023）

示例::

 >>> print(pwm.duty())
 50
 >>> print(pwm.duty(500))
 None


.. method:: PWM.deinit( )

   关闭PWM。使用PWM后，你需要使用 ``deinit()`` 取消初始化它。