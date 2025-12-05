OneButton
----------------------------------
1. 示例代码

本示例会使用OneButton库来实现板载A B按键功能。

.. Attention:: 掌控板A键连接到P5，B键连接到P11。

+搜索并下载OneButton库，安装到arduino IDE中，如下图。

.. figure:: /_static/image/c_program/arduino_IDE/OneButton.png
    :align: center
    :width: 500
|   

.. literalinclude:: /_static/examples/c_program/arduino_IDE/OneButton.cpp 
    :caption: 示例-OneButton.ino
    :linenos:
|

3. 运行效果

按A键，串口打印"Button A clicked."，按B键打印"Button B clicked."。
