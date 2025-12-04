blink示例
----------------------------------

硬件连接

打开示例

硬件通过USB连接到电脑后，打开Arduino IDE，依次点击「文件」→「示例」→「01.Basics」→「Blink」，打开示例代码。

1.选择mPython V3开发板

.. figure:: /_static/image/c_program/arduino_IDE/board_select.png
    :align: center
    :width: 800
|

2. 选择板子对应的串口

.. figure:: /_static/image/c_program/arduino_IDE/serial_port.png
    :align: center
    :width: 800
|



编写代码


.. literalinclude:: /_static/examples/c_program/blink.cpp
    :caption: 示例-main.cpp
    :linenos:

编译并上传


代码上传后，掌控板会自动运行代码，LED会闪烁。

analogRead示例
----------------------------------


analogWrite示例
----------------------------------