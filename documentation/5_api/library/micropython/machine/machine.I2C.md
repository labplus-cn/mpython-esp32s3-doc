::: currentmodule
machine
:::

# 类 I2C \-- 两线串行协议 {#machine.I2C}

I2C是一种用于设备之间通信的两线协议。在物理层面上，它由2根线组成：SCL和SDA，分别是时钟线和数据线。

创建一个与特定总线关联的I2C对象。它们可以在创建时初始化，也可以稍后初始化。

示例:

    from machine import I2C,Pin

    i2c = I2C(scl=Pin(22), sda=Pin(23), freq=400000)          # 创建频率为400kHz的I2C外设
    # 根据端口不同，可能需要额外参数
    # 以选择外设和/或使用的引脚

    i2c.scan()                      # 扫描从设备，返回7位地址的列表

    i2c.writeto(42, b'123')         # 向7位地址为42的从设备写入3字节
    i2c.readfrom(42, 4)             # 从7位地址为42的从设备读取4字节

    i2c.readfrom_mem(42, 8, 3)      # 从从设备42的内存中读取3字节，
                                    #   从从设备的内存地址8开始
    i2c.writeto_mem(42, 2, b'\x10') # 向从设备42的内存写入1字节
                                    #   从地址2开始

## 构造函数

::: {.I2C(id=-1, .*, .scl, .sda, .freq=400000)}
构造并返回具有给定参数的新I2C对象：

> - `id` 标识特定的I2C外设。默认值-1选择I2C的软件实现
> - `scl` 应该是指定用于SCL的引脚对象
> - `sda` 应该是指定用于SDA的引脚对象
> - `freq` 应该是设置SCL最大频率的整数。0 \< freq ≤ 500000(Hz)。
:::

:::: attention
::: title
Attention
:::

I2C可以使用引脚：GPIO 0/2/4/5/9/16/17/18/19/21/22/23/25/26/27
::::

## 通用方法

::: method
I2C.init(scl, sda, \*, freq=400000)

使用给定参数初始化I2C总线：

- `scl` 是SCL线的引脚对象
- `sda` 是SDA线的引脚对象
- `freq` 是SCL时钟速率
:::

::: method
I2C.deinit()

关闭I2C总线。
:::

::: method
I2C.scan()

扫描0x08到0x77之间的所有I2C地址并返回响应的地址列表。如果设备在总线上发送其地址（包括写位）后拉低SDA线，则设备响应。
:::

## 原始I2C操作

以下方法实现原始I2C主总线操作，可以执行任何I2C事务。如果您需要比下面的标准方法更多的事务控制，则提供这些方法。

::: method
I2C.start()

在总线上生成START条件（SDA在SCL为高电平时从高电平转换为低电平）。
:::

::: method
I2C.stop()

在总线上生成STOP条件（SDA在SCL为高电平时从低电平转换为高电平）。
:::

::: method
I2C.readinto(buf, nack=True)
:::

从总线读取字节并将它们存储到 `buf` 中。读取的字节数是 `buf`
的长度。除了可能的最后一个字节外，所有字节后都会在总线上发送
`ACK`。收到最后一个字节后，如果 `nack` 为真，则发送 `NACK`，否则发送
`ACK`（从设备假设稍后会读取更多字节）。

::: method
I2C.write(buf)
:::

将 `buf` 中的字节写入总线。检查每个字节后是否收到 `ACK`，如果收到 `NACK`
则停止发送剩余字节。返回收到的 `ACK` 数量。

## 标准总线操作

以下方法实现给定从设备的标准I2C主读取和写入操作。

::: method
I2C.readfrom(addr, nbytes, stop=True)
:::

从 `addr` 指定的从设备读取 `nbytes` 字节。如果 `stop`
为真，则在传输结束时生成停止条件。返回包含读取数据的 `bytes` 对象。

::: method
I2C.readfrom_into(addr, buf, stop=True)
:::

从 `addr` 指定的从设备读取到 `buf` 中。读取的字节数将是 `buf`
的长度。如果 `stop` 为真，则在传输结束时生成停止条件。

此方法返回 `None`。

::: method
I2C.writeto(addr, buf, stop=True)
:::

将 `buf` 中的字节写入 `addr` 指定的从设备。如果从 `buf`
写入字节后收到NACK，则不发送剩余字节。如果 `stop`
为真，则在传输结束时生成STOP条件，即使收到了NACK。返回收到的ACK数量。

## 寄存器操作

一些I2C设备充当可以读取和写入的存储设备（或寄存器组）。在这种情况下，I2C事务关联两个地址：从设备地址和内存地址。以下方法是与这些设备通信的便捷函数。

::: method
I2C.readfrom_mem(addr, memaddr, nbytes, \*, addrsize=8)
:::

从 `addr` 指定的从设备读取 `nbytes` 字节，从 `memaddr`
指定的内存地址开始。参数 `addrsize` 指定地址大小（位）。
返回包含读取数据的 `bytes` 对象。

::: method
I2C.readfrom_mem_into(addr, memaddr, buf, \*, addrsize=8)
:::

从 `addr` 指定的从设备读取到 `buf` 中，从 `memaddr`
指定的内存地址开始。读取的字节数是 `buf` 的长度。 参数 `addrsize`
指定地址大小（位）。

此方法返回 `None`。

::: method
I2C.writeto_mem(addr, memaddr, buf, \*, addrsize=8)
:::

将 `buf` 写入 `addr` 指定的从设备，从 `memaddr` 指定的内存地址开始。参数
`addrsize` 指定地址大小（位）。

此方法返回 `None`。
