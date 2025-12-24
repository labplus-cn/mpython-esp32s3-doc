6-Axis
----------------------------------

1. 下载驱动库

搜索QMI8658库并安装。

.. figure:: /_static/image/c_program/arduino_IDE/QMI8658.png
    :align: center
    :width: 500
|

2. 示例代码

在arduino IDE中，点击「File」→「Examples」→「QIM8658」→「QMI8658_Basic」打开示例。

.. Attention:: 掌控板QMI8658 6轴连接到IIC接口，SDA接P20(GPIO44)，SCL接P19(GPIO43).找到并修改以下代码行:

    bool success = imu.begin(44, 43);

.. literalinclude:: /_static/examples/c_program/arduino_IDE/QMI8658.cpp 
    :caption: 示例-QMI8658.ino
    :linenos:
|

3. 运行效果

串口打印6轴数据。