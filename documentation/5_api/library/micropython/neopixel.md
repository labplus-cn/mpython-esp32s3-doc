# `neopixel`{.interpreted-text role="mod"} \-\-- 控制 WS2812 / NeoPixel LED

::: {.module synopsis="控制 WS2812 / NeoPixel LED"}
neopixel
:::

此模块提供了 WS2818 / NeoPixel LED 的驱动程序。

:::: note
::: title
Note
:::

此模块默认仅包含在 ESP8266、ESP32 和 RP2 端口上。在 STM32 / Pyboard
和其他端口上，您可以使用 `mip`{.interpreted-text role="term"} 安装
`neopixel` 包，或者直接从 `micropython-lib`{.interpreted-text
role="term"} 下载模块并将其复制到文件系统。
::::

## class NeoPixel

此类存储连接到引脚的 WS2812 LED
灯条的像素数据。应用程序应设置像素数据，然后在准备更新灯条时调用
`NeoPixel.write`{.interpreted-text role="meth"}。

例如:

    import neopixel

    # 32 个 LED 灯条连接到 X8。
    p = machine.Pin.board.X8
    n = neopixel.NeoPixel(p, 32)

    # 绘制红色渐变。
    for i in range(32):
        n[i] = (i * 8, 0, 0)

    # 更新灯条。
    n.write()

## 构造函数

::: {.NeoPixel(pin, .n, .*, .bpp=3, .timing=1)}
构造一个 NeoPixel 对象。参数为：

> - *pin* 是 machine.Pin 实例。
> - *n* 是灯条中的 LED 数量。
> - *bpp* 对于 RGB LED 为 3，对于 RGBW LED 为 4。
> - *timing* 对于 400KHz 为 0，对于 800kHz LED 为 1（大多数是
>   800kHz）。您还可以提供 [machine.bitstream()]{.title-ref}
>   接受的时序元组。
:::

## 像素访问方法

::: method
NeoPixel.fill(pixel)

将所有像素的值设置为指定的 *pixel* 值（即 RGB/RGBW 元组）。
:::

::: method
NeoPixel.\_\_len\_\_()

返回灯条中的 LED 数量。
:::

::: method
NeoPixel.\_\_setitem\_\_(index, val)

将 *index* 处的像素设置为值，这是一个 RGB/RGBW 元组。
:::

::: method
NeoPixel.\_\_getitem\_\_(index)

返回 *index* 处的像素作为 RGB/RGBW 元组。
:::

## 输出方法

::: method
NeoPixel.write()

将当前像素数据写入灯条。
:::
