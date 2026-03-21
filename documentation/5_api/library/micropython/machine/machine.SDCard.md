# [machine.SDCard]{.title-ref} \-\-- 安全数字存储卡

SD卡是最常见的小型可移动存储介质之一。
SD卡有各种尺寸和物理形式。MMC卡是类似的可移动存储设备，而eMMC设备是设计用于嵌入其他系统的电气类似存储设备。这三种形式共享与主机系统通信的通用协议，它们的高级支持看起来相同。因此，在MicroPython中，它们通过一个名为machine.SDCard的单一类实现。

::: currentmodule
machine
:::

::::: {.SDCard(slot=1, .width=1, .cd=None, .wp=None, .sck=None, .miso=None, .mosi=None, .cs=None, .cmd=None, .data=None, .freq=20000000)}
此类提供对SD或MMC存储卡的访问，使用专用的SD/MMC接口硬件或通过SPI通道。
该类实现了vfs.AbstractBlockDev定义的块协议。
这使得SD卡的挂载可以简单到：

``` python
vfs.mount(machine.SDCard(), "/sd")
```

构造函数接受以下参数：

- *slot* 选择要使用的可用接口之一。不设置将选择默认接口。
- *width* 选择SD/MMC接口的总线宽度。必须有这么多数据引脚连接到SD卡。
- *cd* 可用于指定卡检测引脚。
- *wp* 可用于指定写保护引脚。
- *sck* 可用于指定SPI时钟引脚。
- *miso* 可用于指定SPI miso引脚。
- *mosi* 可用于指定SPI mosi引脚。
- *cs* 可用于指定SPI片选引脚。

以下附加参数仅在ESP32端口上存在：

- *cmd* 可用于指定SD CMD引脚（仅ESP32-S3）。
- *data* 可用于指定SD数据总线引脚的列表或元组（仅ESP32-S3）。
- *freq* 选择SD/MMC接口频率（Hz）。

::: method
init(slot=1, width=1, cd=None, wp=None, sck=None, miso=None, mosi=None,
cs=None, cmd=None, data=None, freq=20000000)

初始化SDCard。

参数与构造函数相同。
:::

::: method
deinit()

取消初始化SDCard。
:::
:::::
