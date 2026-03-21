::: currentmodule
machine
:::

# 类 I2CTarget \-- I2C 从设备 {#machine.I2CTarget}

::::::: {.I2CTarget(scl, .sda, .address, .*, .freq=400000)}
构造一个I2C从设备对象。

*scl* 是SCL引脚。 *sda* 是SDA引脚。 *address* 是I2C设备地址。 *freq*
是I2C总线频率，默认为400kHz。

::: method
init(scl, sda, address, \*, freq=400000)

初始化I2C从设备。

*scl* 是SCL引脚。 *sda* 是SDA引脚。 *address* 是I2C设备地址。 *freq*
是I2C总线频率，默认为400kHz。
:::

::: method
deinit()

取消初始化I2C从设备。
:::

::: method
read(buf)

从I2C控制器读取数据到缓冲区。

*buf* 是读取数据的缓冲区。
:::

::: method
write(buf)

向I2C控制器写入数据。

*buf* 是要写入的数据缓冲区。
:::
:::::::
