4_light sensor
----------------------------------

1. 下载驱动库

搜索 LTR308_library库并安装。

.. figure:: /_static/image/c_program/arduino_IDE/LTR308.png
    :align: center
    :width: 500
|

2. 示例代码

本示例会使用LTR308_library库获取数字光线传感器数据。在arduino IDE中，点击「File」→「Examples」→「LTR308_library」→「LTR308example」打开示例。

.. literalinclude:: /_static/examples/c_program/arduino_IDE/LTR308.cpp 
    :caption: 示例-LTR308.ino
    :linenos:
|

3. 运行效果

串口打印数字光线采集值。