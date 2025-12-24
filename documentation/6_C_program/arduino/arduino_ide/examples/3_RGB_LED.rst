RGB LED
----------------------------------
1. 示例代码

本示例会使用ESP32_WS2812_Lib库来实现板载RGB LED控制。

搜索并下载ESP32_WS2812_Lib库，安装到arduino IDE中，如下图。

.. figure:: /_static/image/c_program/arduino_IDE/esp32_ws2812.png
    :align: center
    :width: 300
|

.. Attention:: 掌控板板载RGB LED数量:3，控制IO为P7.

.. literalinclude:: /_static/examples/c_program/arduino_IDE/RainBow.cpp 
    :caption: 示例-RainBow.ino
    :linenos:
|

3. 运行效果

代码上传后，板载3个灯显示幻彩灯效。