blink
----------------------------------

1. 硬件连接,如下图所示，将LED模块连接到拓展板P0引脚。

.. figure:: /_static/image/c_program/arduino_IDE/blink_led.png
    :align: center
    :width: 300
|

2. 选择mPython V3开发板

.. figure:: /_static/image/c_program/arduino_IDE/board_select.png
    :align: center
    :width: 800
|

3. 选择板子对应的串口

.. figure:: /_static/image/c_program/arduino_IDE/serial_port.png
    :align: center
    :width: 800
|

4. 示例代码

.. literalinclude:: /_static/examples/c_program/arduino_IDE/blink.cpp
    :caption: 示例-blink.ino
    :linenos:

5. 编译并上传


代码上传后，掌控板会自动运行代码，LED会闪烁。

analogRead() analogWrite()
----------------------------------

1. 硬件连接,如下图所示，将LED模块连接到拓展板P1引脚，旋钮电位器接P0。

.. figure:: /_static/image/c_program/arduino_IDE/analog.png
    :align: center
    :width: 300
|

2. 示例代码

.. literalinclude:: /_static/examples/c_program/arduino_IDE/analog.cpp
    :caption: 示例-analog.ino
    :linenos:
|

3. 运行效果

代码上传后，接在P1的LED会根据P0引脚的模拟输入值调整亮度， 串口打印P0采样值及模拟输出值。
