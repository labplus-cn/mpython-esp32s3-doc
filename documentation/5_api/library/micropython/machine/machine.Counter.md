::: currentmodule
machine
:::

# 类 Counter \-- 脉冲计数器 {#machine.Counter}

::::::::: {.Counter(pin, .*, .edge=Counter.RISING, .debounce=0)}
构造一个脉冲计数器对象，用于计算引脚上的脉冲。

*pin* 是要计数脉冲的引脚。 *edge*
是触发边沿，可以是Counter.RISING（上升沿）、Counter.FALLING（下降沿）或Counter.BOTH（双边沿）。
*debounce* 是去抖时间（毫秒），默认为0。

::: method
init(pin, \*, edge=Counter.RISING, debounce=0)

初始化脉冲计数器。

参数与构造函数相同。
:::

::: method
deinit()

取消初始化脉冲计数器。
:::

::: method
value(\[value\])

获取或设置计数器值。

如果提供了 *value*，则设置计数器值。 否则，返回当前计数器值。
:::

::: data
RISING

上升沿触发。
:::

::: data
FALLING

下降沿触发。
:::

::: data
BOTH

双边沿触发。
:::
:::::::::
