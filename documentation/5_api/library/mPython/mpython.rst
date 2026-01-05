
.. _mpython.py:

.. module:: mpythons
   :synopsis: 掌控板板载硬件相关功能函数

:mod:`mpython` --- 板载硬件相关函数
=========================================================

``mpython`` 是基于掌控板封装的专有模块,内含掌控板板载资源相关功能函数。 详细代码实现可查阅 :ref:`mpython.py源码 <mpython_code>` 。

tft显示屏
----------------

掌控板板载1.47寸320*172分辨率显示屏，可以用来显示彩色文字、图片、简单动画。

通过display对象，可以实现相关显示功能。

.. method:: display.DispChar(str, x, y, color=lcd.WHITE, auto_wrap = False)

内置思源中文字体显示函数，参数：

- ``str`` 待显示的字符串

- ``x`` 显示坐标x

- ``y`` 显示坐标y

- ``color`` 字体颜色，默认白色

- ``auto_wrap`` 是否换行，默认不换行

.. method:: display.DispChar_font(font, str, x, y, color=lcd.WHITE, auto_wrap = False)

内置数码管及dvsm字体显示函数，这些字体由font-to-py.py制作，内置的只有英文和数字，用户可用这个工具自已制字体，参数：

- ``font`` 待显示的字体名

- ``str`` 待显示的字符串

- ``x`` 显示坐标x

- ``y`` 显示坐标y

- ``color`` 字体颜色，默认白色

- ``auto_wrap`` 是否换行，默认不换行

.. method:: display.clear(color = lcd.BLACK)

清屏（背景设置）函数

- ``color`` 背景颜色,默认黑色

.. method:: display.show():

缓存内容送显示屏显示

.. Attention:: display继承自micropython framebuf对象，并实例了一个framebuf缓存做显存。因此display实现了framebuf一些api,下面是相关api:

.. method:: class framebuf.FrameBuffer(buffer, width, height, format, stride=width, /)

构造一个 FrameBuffer 对象。

- ``buffer`` 缓存区

- ``width height`` 缓存区宽度、高度

- ``format`` 像素点类型，掌控板V3强制为RGB565

- ``stride`` 行像素点字节数

.. method:: display.fill(color)

显存填充函数，通常用来设置显示背景, 通常不会直接调用，使用上面的display.clear(color = lcd.BLACK)。

- ``color`` 待填充颜色

.. method:: display.fill_rect(x, y, w, h, color)

显存局部区域填充函数, 通常用来清除局部区域内容。

- ``x y`` 起点坐标

- ``w h`` 区域宽度、高度

- ``color`` 填充颜色

.. method:: display.pixel(x, y, color)

设置/获取相应坐标点颜色。

- ``x y`` 显示坐标

- ``color`` 填充颜色,无此参数时，为获取点颜色

.. method:: display.hline(x, y, w, color)

画水平线。

- ``x y`` 起点坐标

- ``w`` 水平线长

- ``color`` 填充颜色

.. method:: display.vline(x, y, h, color)

画垂直线。

- ``x y`` 起点坐标

- ``h`` 垂直线长

- ``color`` 填充颜色

.. method:: display.rect(x, y, w, h, color)

画矩形。

- ``x y`` 起点坐标

- ``w h`` 矩形宽度、高度

- ``color`` 填充颜色

.. method:: display.line(x1, y1, x2, y2, color)

画直线。

- ``x1 y1`` 起点坐标

- ``x2 y2`` 终点坐标

- ``color`` 填充颜色

.. method:: display.circle(x, y, radio, color)

画圆。

-- ``x y`` 圆心坐标

- ``radio`` 半径

- ``color`` 圆弧颜色

.. method:: display.quarter_circle(x, y, radio, cornername, color)

画1/4圆。

-- ``x y`` 圆心坐标

- ``radio`` 半径

- ``cornername`` 所在象限

- ``color`` 圆弧颜色

.. method:: display.fill_circle(x, y, radio, color)

画实心圆。

-- ``x y`` 圆心坐标

- ``radio`` 半径

- ``color`` 填充颜色

.. method:: display.triangle(x0, y0, x1, y1, x2, y2, color)

画三角形。

- ``x0 y0 x1 y1 x2 y2`` 三个角点坐标

- ``color`` 边颜色

.. method:: display.fill_triangle(x0, y0, x1, y1, x2, y2, color)

画实心三角形。

- ``x0 y0 x1 y1 x2 y2`` 三个角点坐标

- ``color`` 填充颜色

.. method:: display.RoundRect(x, y, w, h, r, color)
.. method:: display.round_rect(x, y, w, h, r, color)

画圆角矩形。

- ``x y`` 起点坐标

- ``w h`` 矩形宽高

- ``r`` 倒角半径

- ``color`` 边颜色

.. method:: display.ellipse(x, y, xr, yr, color, mask)

画椭圆弧。

- ``x y`` 起点坐标

- ``xr yr`` x y轴半径

- ``color`` 边颜色

- ``mask``  0x01:画第一象限 0x02:画第二象限 0x04:画第三象限 0x08:画第四象限 0xff:画完整椭圆 0x10:填充椭圆

.. method:: display.blit(fb, x, y, key=-1, palette=None)

将一个缓存区，绘入显示framebuf给定位置。

- ``fb`` 待绘制缓存区

- ``x y`` 起点坐标

- ``key`` 如果指定了键，那么它应该是一个颜色整数，相应的颜色将被视为透明：所有具有该颜色值的像素都不会被绘制

- ``palette`` palette 参数支持在不同格式的帧缓冲区之间进行位块传输。典型用法是将单色或灰度的字形 / 图标渲染到彩色显示器上。该调色板是一个帧缓冲区实例，其格式与当前帧缓冲区的格式一致。调色板的高度为 1 个像素，其像素宽度等于源帧缓冲区中的颜色数量。N 位源的调色板需要 2**N 个像素；单色源的调色板有 2 个像素，分别代表背景色和前景色。应用程序为调色板中的每个像素分配一种颜色。当前像素的颜色将与调色板中某个像素的颜色一致，该像素的 x 坐标即为对应源像素的颜色。

.. method:: display.text(str, x, y, color)

绘制micropython内置字体，不能显示中文，掌控板上显示过小，一般不用。

- ``str`` 待显示的字符串

- ``x y`` 显示坐标

- ``color`` 字体颜色，默认白色

.. method:: display.decode_png_internal(index)

解码内置png图片，返回图片宽高及framebuf对象。

- ``index`` 内置图片索引

.. method:: display.background_color(color)

设置/获取背景颜色，有参数为设置，否帽获取

- ``color`` 背景颜色

GUI库
----------------

GUI库实现一些基础GUI功能：进度条、二维码、时钟、图象解码、图表、表格。

.. method:: class gui.UI()

构造一个UI对象。

.. method:: ui.ProgressBar(x, y, width, height, progress, color= lcd.WHITE)

绘制一个进度条。

- ``x y`` 显示坐标

- ``width height`` 矩形宽高

- ``progress`` 进度值

- ``color`` 颜色

.. method:: ui.stripBar(self, x, y, width, height, progress, dir=1, frame_color=lcd.WHITE, color=lcd.WHITE)

绘制一个进度条。

- ``x y`` 显示坐标

- ``width height`` 矩形宽高

- ``progress`` 进度值

- ``frame_color`` 边框颜色

- ``color`` 颜色

.. method:: ui.qr_code(str, x, y, scale = 4)

绘制一个二维码。

- ``str`` 二维码内容

- ``x y`` 显示坐标

- ``scale`` 缩放比例

.. method:: class gui.Image()

构造一个Image对象,用于加载Image图象，当前支持png格式。

.. method:: ui.load(path, invert=0)

加载并解码图片文件。

- ``path`` 图片文件路径

- ``invert`` 图片反转，参数暂未用

.. method:: class gui.MicroExcelTable(self, display = display, x0=0, y0=0, cols=3, rows=4, cell_width=85, cell_height=30, col_header_text_color=lcd.RED, row_header_width=60, row_header_text_color=lcd.RED, data_text_color=lcd.WHITE, border_color=lcd.GREEN, show_border=True, font_size=(16, 16), cross_text="")

构造一个表格对象。

- ``cols rows`` 行列数

- ``cell_width cell_height`` 单元格宽高

- ``col_header_text_color`` 列表头文本颜色

- ``row_header_width`` 行表头宽

- ``row_header_text_color`` 行表头文本颜色

- ``data_text_color`` 数据区文本颜色

- ``border_color`` 数据区边框颜色

- ``show_border`` 是否显示边框

- ``font_size`` 字体宽高

- ``cross_text`` 表头交叉处文本

.. method:: exectable.draw_headers(col_header_data, row_header_data)

绘制表头内容。

- ``col_header_data`` 列表头内容，e.g. ["温度", "湿度", "气压"]

- ``row_header_data`` 行表头内容，e.g. ["设备1", "设备2", "设备3"]

.. method:: exectable.update_data(new_data)

更新整个数据区内容。

- ``new_data`` 数据区内容

.. method:: exectable.update_cell(row, row, text)

更新整个数据区内容。

- ``row row`` 待更新表格行列值

- ``text`` 待更新内容

.. method:: exectable.clear_all()

    清除内容。

.. method:: class gui.MicroChart(display = display, x0=0, y0=0, width=200, height=100, val_min = 0, val_max = 100, bg_color=lcd.BLACK, axis_color=lcd.WHITE, data_colors=[lcd.RED, lcd.GREEN, lcd.BLUE], padding=10)

构造一个图表对象

- ``display`` 显示器

- ``x0 y0`` 位置

- ``width height`` 图表宽高

- ``val_min val_max`` 数值范围

- ``bg_color`` 背景颜色

- ``axis_color`` 坐标轴颜色

- ``data_colors`` 数据颜色列表，多条数据线时，可分别设置颜色

- ``padding`` 偏移

.. method:: chart.draw_axis(show_ticks=True)

绘制坐标轴

- ``show_ticks`` 是否显示刻度

.. method:: chart.draw_grid(grid_color=None)

绘制参考点

- ``grid_color`` 点颜色

.. method:: chart.draw_line_chart(data, show_grid=False)

绘制折线图

- ``data`` 待绘制数据

- ``show_grid`` 是否显示参考点

.. method:: chart.draw_bar_chart(data, show_grid=False)

绘制柱状图

- ``data`` 待绘制数据

- ``show_grid`` 是否显示参考点


声音、光线
----------

.. method:: light.read()

读取板载光线传感器值，范围0~4095。


.. method:: sound.read()

读取板载麦克风，范围0~4095。


加速度计
----------

通过accelerometer对象，您可以获取3轴加速度计值，单位g。 加速度范围±2g/±4g/±8g/±16g,默认为±2g。

.. method:: accelerometer.get_x()

获取x轴上的加速度测量值，正整数或负整数，具体取决于方向。

.. method:: accelerometer.get_y()

获取y轴上的加速度测量值，正整数或负整数，具体取决于方向。

.. method:: accelerometer.get_z()

获取z轴上的加速度测量值，正整数或负整数，具体取决于方向。

.. method:: accelerometer.set_range(range)

设置加速度范围,在默认,不修改为,范围在±2g。

加速度范围值为以下常量:

    ========================== ========= =================
        常量                       值      定义
        RANGE_2G                   0        范围±2g
        RANGE_4G                   1        范围±4g
        RANGE_8G                   2        范围±8g
        RANGE_16G                  3        范围±16g
    ========================== ========= =================


.. method:: accelerometer.set_resolution(resolution)

设置加速度分辨率,默认,不修改为10bit分辨率。

分辨率值为以下常量:

    ========================== ========= =================
        常量                       值      定义
        RES_14_BIT                  0      14 bit 分辨率 
        RES_12_BIT                  1      12 bit 分辨率 
        RES_10_BIT                  2      10 bit 分辨率 
    ========================== ========= =================

.. method:: accelerometer.set_offset(x=None, y=None, z=None)

该函数用于校准加速度计的3个轴(x,y,z)的加速值偏差。一般情况下无需校准,只有当遇到加速度偏差较大时修正。
注意,校准数据断电后不会保存。``x`` , ``y`` , ``z`` 为调整偏差值,可修正范围±1g。
掌控板v2.3版本以上，掉电会保存校准数据。

.. method:: accelerometer.roll_pitch_angle()

返回通过加速度计计算得出的欧拉角(横滚角roll、俯仰角pitch)。注意，偏航角(yaw)需要角速度，故无法测得。返回2元组（roll,pitch），单位角度。

假定，掌控板为飞机：

- 横滚角指飞机两翼所在的平面与平行线之间的夹角，机体向右滚为正,范围为[-180,180].
- 俯仰角是指机头与水平面的夹角,当飞机平行时则为0,抬头时则为正,范围为[-180,180]

.. Attention:: 只通过3轴加速度计算方式，只适用于静态下，只受重力下的测量。实际中，会受到其他加速度干扰，如震动。

运动侦测事件
~~~~~~~~~~~~~

提供多种平面倾斜、翻转、敲击（类似鼠标点击）、掉落的运动姿态事件。用户可预先设定回调函数，当事件发生后，触发事件回调。
回调函数定义如，function_callback(event)。`event` 参数为对应事件常量。


.. data:: accelerometer.event_tilt_left

向左倾斜

.. data:: accelerometer.event_tilt_right

向右倾斜

.. data:: accelerometer.event_tilt_up

向前倾斜

.. data:: accelerometer.event_tilt_down

向后倾斜


.. data:: accelerometer.event_face_up

正面朝上

.. data:: accelerometer.event_face_down

正面朝下

.. data:: accelerometer.event_single_click

单次敲击，类似鼠标的单击操作。

.. data:: accelerometer.event_double_click

连续敲击两次，类似鼠标的双击操作。

.. data:: accelerometer.event_freefall

坠落

event事件定义如下:

    ================================== ========= 
        事件                              值     
        accelerometer.TILT_LEFT           0      
        accelerometer.TILT_RIGHT          1    
        accelerometer.TILT_UP             2    
        accelerometer.TILT_DOWN           3   
        accelerometer.FACE_UP             4     
        accelerometer.FACE_DOWN           5   
        accelerometer.SINGLE_CLICK        6    
        accelerometer.DOUBLE_CLICK        7     
        accelerometer.FREEFALL            8    
    ================================== =========

.. Attention:: 掌控板v2.3版本以上,去除加速度计运动侦测事件

.. literalinclude:: /_static/examples/accelerometer/accelerometer_event.py
    :caption: accelerometer 事件的简单应用
    :linenos:

陀螺仪(gyroscope)
--------------------

通过gyroscope对象，您可以获取陀螺仪角速度值，角速度的单位是dps(°/S)。 
角速度范围±16dps/±32dps/±64dps/±128dps/±256dps/±512dps/±1024dps/±2048dps ,默认为±256 dps。

.. method:: gyroscope.get_x()

获取x轴上的角速度测量值，具体取决于方向。

.. method:: gyroscope.get_y()

获取y轴上的角速度测量值，具体取决于方向。

.. method:: gyroscope.get_z()

获取z轴上的角速度测量值，具体取决于方向。

.. method:: gyroscope.set_range(range)

设置角速度范围,默认不修改为,范围在±256 dps。

角速度范围值为以下常量:

    ========================== ========= =================
        常量                       值          定义
        RANGE_16_DPS               0         范围±16 dps
        RANGE_32_DPS               16        范围±32 dps
        RANGE_64_DPS               32        范围±64 dps
        RANGE_128_DPS              48        范围±128 dps
        RANGE_256_DPS              64        范围±256 dps
        RANGE_512_DPS              80        范围±512 dps
        RANGE_1024_DPS             96        范围±1024 dps
        RANGE_2048_DPS             112       范围±2048 dps
    ========================== ========= =================

.. method:: gyroscope.set_offset(x=None, y=None, z=None)

该函数用于校准陀螺仪的3个轴(x,y,z)的角速值偏差。一般情况下无需校准,只有当遇到角速度偏差较大时修正。
``x`` , ``y`` , ``z`` 为调整偏差值,可修正范围±1024dps。    

.. Attention:: 掌控板v2.3版本以上加入陀螺仪传感器


磁力计(magnetic)
-------------------
MMC5983MA磁力计函数接口,可获取3轴磁感应强度、地磁场强度、获取电子罗盘角度。

.. Attention:: 掌控板v2.0版本以上,才有MMC5983MA磁力计！

.. method:: magnetic.get_x()

获取x轴的磁感应值,正整数或负整数,范围±8191,单位mG(毫高斯)。

.. method:: magnetic.get_y()

获取y轴的磁感应值,正整数或负整数,范围±8191,单位mG(毫高斯)。

.. method:: magnetic.get_z()

获取z轴的磁感应值,正整数或负整数,范围±8191,单位mG(毫高斯)。

.. method:: magnetic.get_field_strength()

返回计算后的磁感应值,即3轴磁力的和。计算公式,x^2+y^2+z^2的平方根。

.. method:: magnetic.peeling()

磁力去皮。类似电子秤去皮功能, ``peeling()`` 后,下次 ``get_field_strength()`` 返回的值为减去当前磁力值后计算得出的结果。可用于去除地磁感应值的测量应用。 

.. method:: magnetic.clear_peeling()

磁力去皮功能取消。使用 ``peeling()`` 后,可用该函数,恢复正常地磁测量。

.. method:: magnetic.get_heading()

获取电子罗盘角度,即改方向与地磁北极的夹角,掌控板的正上方,即USB位置视为正北方。单位角度,范围0~360。

.. Attention:: 由于在角度计算并没有做z轴的倾斜补偿,在使用 ``get_heading()`` 读取罗盘角度时,掌控板应保持水平放置！

.. Attention:: 如需得到精准的罗盘角度,请确保周边无强磁场干扰或在使用前 ``calibrate()`` 校准。

.. method:: magnetic.calibrate()

电子罗盘校准。当掌控板周边存在强磁干扰,可使用该函数清除强磁分量,才能计算准确的地磁北偏角。注意,断电后不保存校准偏移值。

校准方法,按照掌控板显示屏指示步骤操作:

    1. 掌控板水平放置,在水平面旋转数圈,过程约15秒。
    2. 掌控板垂直放置,沿着垂直于地面轴旋转数圈,过程约15秒。


.. literalinclude:: /_static/examples/magnetic/compass.py
    :caption: 磁力计应用--指北针
    :linenos:


蜂鸣器(music)
-----------------

由 ``music`` 模块驱动掌控板蜂鸣器,具体操作详见 :mod:`music` 模块。


button_[a,b]对象
-----------------

掌控板上的a,b按键。button_a/button_b 是 ``Button`` 类的实例对象。使用 :ref:`machine.Pin.irq<Pin.irq>` 中断实现。定义了
``event_pressed`` 和 ``event_released`` 按键按下、释放事件。 用户可轻易的实现事件回调。除此外，还实现当前或过去按键状态、按键次数等函数方法。

.. class:: Button(pin_num, reverse=False)

Button类，按键抽象类。

    - ``pin_num`` - IO引脚号
    - ``reverse`` - 默认为reverse为False。适用于触发为低电平按键。如是触发为高电平按键，将reverse设为True，翻转下。

掌控板上button_a、button_b的实例::

    button_a = Button(Pin.P5)
    button_b = Button(Pin.P11)


当按键事件发生，触发事件回调。回调函数定义如，function_callback(pin), ``pin`` 为该引脚的machine.Pin对象返回。

.. data:: Button.event_pressed

按键按下事件。

.. data:: Button.event_released

按键释放事件。


.. literalinclude:: /_static/examples/button/button_event.py
    :caption: Button 事件回调的简单应用
    :linenos:



.. method:: Button.value()

获取按键引脚电平状态。1为高电平，0位低电平。

::

    >>> button_a.value()
    >>> 1
    >>> button_a.value()
    >>> 0


.. method:: Button.is_pressed()

返回当前是否按住。 ``True`` 表示按键按下，``False`` 则未按下。

.. method:: Button.was_pressed()

返回 ``True`` 或 ``False`` 指示自设备启动以来或上次调用此方法以来是否按下按钮。调用此方法将清除按下状态，因此必须再次按下按钮，然后才能再次返回 ``True`` 。

.. method:: Button.get_presses()

返回按键的按下总数，并在返回之前将该总数重置为零。注意，计数器超过100将不再计数。


.. _button.irq:

.. method:: Button.irq(handler=None, trigger=(Pin.IRQ_FALLING | Pin.IRQ_RISING), priority=1, wake=None)

配置在引脚的触发源处于活动状态时调用的中断处理程序。用法与 machine.Pin.irq 一样。

参数:

     - ``handler`` 是一个可选的函数，在中断触发时调用。

     - ``trigger`` 配置可以触发中断的事件。可能的值是：

       - ``Pin.IRQ_FALLING`` 下降沿中断
       - ``Pin.IRQ_RISING`` 上升沿中断
       - ``Pin.IRQ_LOW_LEVEL`` 低电平中断
       - ``Pin.IRQ_HIGH_LEVEL`` 高电平中断

       这些值可以一起进行 ``OR`` 运算以触发多个事件。


     - ``priority`` 设置中断的优先级。它可以采用的值是特定于端口的，但是更高的值总是代表更高的优先级。

     - ``wake`` 选择此中断可唤醒系统的电源模式。它可以是 ``machine.IDLE`` ， ``machine.SLEEP`` 或 ``machine.DEEPSLEEP`` 。

     这些值也可以进行 ``OR`` 运算，使引脚在多种功耗模式下产生中断。


此方法返回一个回调对象。

::

    >>> from mpython import *
    >>> button_a.irq(trigger=Pin.IRQ_FALLING, handler=lambda p:print("button-a press！")) 


touch对象
----------
掌控板上共有6个触摸引脚分别touchpad_p/y/t/h/o/n。是Touch类的实例对象，具体包含函数方法如下。


.. class:: Touch(pin)


.. data:: Touch.event_pressed

触摸按键按下事件。当按键事件发生，触发事件回调。回调函数定义如，function_callback(value), ``value`` 为该触摸按键的状态值。

.. data:: Touch.event_released

触摸按键释放事件。

.. method:: Touch.read()

返回触摸值

.. method:: Touch.config(threshold)

触摸阈值设置

.. method:: Touch.is_pressed()

返回当前是否按住。 ``True`` 表示按键按下，``False`` 则未按下。

.. method:: Touch.was_pressed()

返回 ``True`` 或 ``False`` 指示自设备启动以来或上次调用此方法以来是否按下按钮。调用此方法将清除按下状态，因此必须再次按下按钮，然后才能再次返回 ``True`` 。

.. method:: Touch.get_presses()

返回按键的按下总数，并在返回之前将该总数重置为零。注意，计数器超过100将不再计数。

rgb对象
------------
用于控制掌控板的3颗RGB ws2812灯珠。rgb对象为neopixel的衍生类，继承neopixel的方法。更多的使用方法请查阅 :ref:`neopixel<neopixel>` 。 

.. method:: rgb.write()

把数据写入RGB灯珠中。 

.. Hint::

    通过给rgb[n]列表赋值来写入RGB颜色值。如，rgb[0]=(50,0,0)

::

    from mpython import *

    rgb[0] = (255, 0, 0)  # 设置为红色，全亮度
    rgb[1] = (0, 128, 0)  # 设定为绿色，半亮度
    rgb[2] = (0, 0, 64)   # 设置为蓝色，四分之一亮度

    rgb.write()

.. method:: rgb.fill(rgb_buf)

填充所有LED像素。

.. method:: rgb.brightness(brightness)

亮度调节,范围0~1.0

i2c对象
-------

mPython掌控板已实例 ``I2C`` 类，P19、P20 为I2C的SCL、SDA引脚。I2C设备可连接掌控板I2C总线进行操作。


详细有关I2C的读写操作，请查看 :ref:`machine.I2C<machine.I2C>` 模块或 :ref:`I2C基础教程<tutorials_i2c>` 章节。

MPythonPin类
------------

.. class:: MPythonPin(pin, mode=PinMode.IN,pull=None)

构建Pin对象

- ``pin`` 掌控板定义引脚号，具体定义看查看 :ref:`掌控板引脚定义<mpython_pinout>` 。

- ``mode`` 引脚模式。未设定时,默认 `mode` = `PinMode.IN`

        - ``PinMode.IN`` 等于1，数字输入模式
        - ``PinMode.OUT`` 等于2，数字输出模式
        - ``PinMode.PWM`` 等于3，模拟输出模式
        - ``PinMode.ANALOG``

映射
----------

.. method:: numberMap(inputNum,bMin,bMax,cMin,cMax)

映射函数，参数：

- ``inputNum`` 为需要映射的变量

- ``bMin`` 为需要映射的最小值

- ``bMax`` 为需要映射的最大值

- ``cMin`` 为映射的最小值

- ``cMax`` 为映射的最大值