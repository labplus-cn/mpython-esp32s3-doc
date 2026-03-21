# `onewire`{.interpreted-text role="mod"} \-\-- 单总线

::: {.module synopsis="单总线"}
onewire
:::

单总线即one-wire总线，是美国DALLAS公司推出的外围串行扩展总线技术。
与SPI、I²C串行数据通信方式不同。它采用单根信号线，既传输时钟又传输数据，而且数据传输是双向的，具有节省I/O口线、资源结构简单、成本低廉、便于总线扩展和维护等诸多优点。

单总线适用于单主机系统，能够控制一个或多个从机设备。主机可以是微控制器，从机可以是单总线器件，它们之间的数据交换只通过一条信号线。
当只有一个从机设备时，系统可按单节点系统操作;当有多个从设备时，系统则按多节点系统操作。图12-1所示是单总线多节点系统。


<img
src="https://ss0.baidu.com/6ONWsjip0QIZ8tyhnq/it/u=3459156120,798055718&amp;fm=173&amp;app=25&amp;f=JPEG?w=574&amp;h=232&amp;s=88A07D3287AC4D091AF4C1DB0000C0B1"
width="400" alt="单总线多节点系统示意图" />
<figcaption aria-hidden="true">单总线多节点系统示意图</figcaption>


## OneWire类

::: OneWire(pin)
构建OneWire类
:::

- `pin` - [machine.Pin]{.title-ref} 实例对象。

::: method
reset(required=False)
:::

::: method
readinto(buf)
:::

读取字节

::: method
write(buf)
:::

写字节

::: method
select_rom(rom)
:::

::: method
scan()
:::

扫描总线上设备

::: method
crc8(data)
:::
