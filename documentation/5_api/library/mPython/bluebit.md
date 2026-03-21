::: {.module synopsis="blue:bit驱动"}
bluebit
:::

# `bluebit`{.interpreted-text role="mod"} \-\-- blue:bit驱动

[blue:bit]{.title-ref} 模块提供bluebit套件的掌控板库。

::: contents
:::

![image](http://wiki.labplus.cn/images/0/07/Bluebit套件1.png)

## NTC模块

::: {.autoclass members="" undoc-members="True" exclude-members="" special-members="'__init__'" member-order="bysource"}
bluebit.Thermistor
:::

::: {.autoclass members="" undoc-members="True" exclude-members="" special-members="'__init__'" member-order="bysource"}
bluebit.NTC
:::

## LM35模块

::: {.autoclass members="" undoc-members="True" exclude-members="" special-members="'__init__'" member-order="bysource"}
bluebit.LM35
:::

## 四按键模块

::: {.autoclass members="" undoc-members="True" exclude-members="" special-members="'__init__'" member-order="bysource"}
bluebit.joyButton
:::

## 温湿度模块

::: {.autoclass members="" undoc-members="True" exclude-members="" special-members="'__init__'" member-order="bysource"}
bluebit.SHT20
:::

## 颜色模块

::: {.autoclass members="" undoc-members="True" exclude-members="" special-members="'__init__'" member-order="bysource"}
bluebit.Color
:::

## 数字光线模块

::: {.autoclass members="" undoc-members="True" exclude-members="" special-members="'__init__'" member-order="bysource"}
bluebit.AmbientLight
:::

## 超声波模块

::: {.autoclass members="" undoc-members="True" exclude-members="" special-members="'__init__'" member-order="bysource"}
bluebit.Ultrasonic
:::

## 4段数码管模块

::: {.autoclass members="" undoc-members="True" exclude-members="" special-members="'__init__'" member-order="bysource"}
bluebit.SEGdisplay
:::

## 8x8点阵模块

8x8点阵模块控制类

- `i2c` : I2C实例对象,默认i2c=i2c.

设置像素点闪烁率

- `rate` : 闪烁间隔时间,单位秒.默认None,常亮.

设置像素点亮度

- `brightness` : 亮度级别,范围0\~15.

填充所有

- `color` : 1亮;0灭

显示位图

- `bitmap` : 8x8点阵数据

显示生效

除上述函数方法外,还继承 `FrameBuffer` 类
,有关其他方法,如显示字符,绘制函数。详情可查阅 micropython framebuf模块
[FrameBuffer](https://mpython.readthedocs.io/zh/master/library/micropython/framebuf.html)
类.

## LCD1602模块

::: {.autoclass members="" undoc-members="True" exclude-members="" special-members="'__init__'" member-order="bysource"}
bluebit.LCD1602
:::

## MIDI模块

::: {.autoclass members="" undoc-members="True" exclude-members="" special-members="'__init__'" member-order="bysource"}
bluebit.MIDI
:::

## MP3模块

::: {.autoclass members="" undoc-members="True" exclude-members="" special-members="'__init__'" member-order="bysource"}
bluebit.MP3
:::

## OLED模块

::: {.autoclass members="" undoc-members="True" exclude-members="" special-members="'__init__'" member-order="bysource"}
bluebit.OLEDBit
:::

## 红外接收模块

::: {.autoclass members="" undoc-members="True" exclude-members="" special-members="'__init__'" member-order="bysource"}
bluebit.IRRecv
:::

## 红外发射模块

::: {.autoclass members="" undoc-members="True" exclude-members="" special-members="'__init__'" member-order="bysource"}
bluebit.IRTrans
:::

## 实验探究类

适用的模块有电压、电流、磁场、电导率、PH、光电门、气压、力传感器。

::: {.autoclass members="" undoc-members="True" exclude-members="" special-members="'__init__'" member-order="bysource"}
bluebit.DelveBit
:::

## 编码电机模块

::: {.autoclass members="" undoc-members="True" exclude-members="" special-members="'__init__'" member-order="bysource"}
bluebit.EncoderMotor
:::

## RFID模块

::: {.autoclass members="" undoc-members="True" exclude-members="" member-order="bysource"}
bluebit.Scan_Rfid
:::

::: {.autoclass members="" undoc-members="True" exclude-members="" special-members="'__init__'" member-order="bysource"}
bluebit.Rfid
:::
