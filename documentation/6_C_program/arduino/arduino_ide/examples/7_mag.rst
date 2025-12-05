Magnetic sensor
----------------------------------

1. 示例代码

在arduino IDE中，点击「File」→「Examples」→「MMC56x3」→「magsensor」打开示例。

.. Attention:: 掌控板MMC5603磁传感器连接到IIC接口，SDA接P20(GPIO44)，SCL接P19(GPIO443).
    
.. literalinclude:: /_static/examples/c_program/arduino_IDE/MMC56x3.cpp 
    :caption: 示例-MMC56x3.ino
    :linenos:
|

3. 运行效果

串口打印磁传感器采集数据。
