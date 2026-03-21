::: currentmodule
machine
:::

# 类 Encoder \-- 正交解码器 {#machine.Encoder}

:::::: {.Encoder(pin_a, .pin_b, .*, .pull=None, .debounce=0)}
构造一个正交解码器对象，用于解码旋转编码器的信号。

*pin_a* 是编码器的A相引脚。 *pin_b* 是编码器的B相引脚。 *pull*
是引脚上拉/下拉设置，可以是None、Pin.PULL_UP或Pin.PULL_DOWN。 *debounce*
是去抖时间（毫秒），默认为0。

::: method
init(pin_a, pin_b, \*, pull=None, debounce=0)

初始化正交解码器。

参数与构造函数相同。
:::

::: method
deinit()

取消初始化正交解码器。
:::

::: method
value(\[value\])

获取或设置编码器值。

如果提供了 *value*，则设置编码器值。 否则，返回当前编码器值。
:::
::::::
