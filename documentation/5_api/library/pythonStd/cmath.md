# `cmath`{.interpreted-text role="mod"} \-\-- 复数数学函数

::: {.module synopsis="复数数学函数"}
cmath
:::

该模块实现了相应 `CPython`{.interpreted-text role="term"}
模块的一个子集，如下所述。有关更多信息，请参阅原始CPython文档:
[cmath](https://docs.python.org/3.5/library/cmath.html#module-cmath)

该模块提供了对复数进行数学运算的函数。

可用性：在WiPy和ESP8266上不可用。此模块需要浮点支持。

快速使用示例:

    import cmath

    # 复数运算
    z = 1 + 2j
    print('z =', z)
    print('abs(z) =', abs(z))
    print('phase(z) =', cmath.phase(z))
    print('polar(z) =', cmath.polar(z))
    print('rect(1, cmath.pi/2) =', cmath.rect(1, cmath.pi/2))

    # 三角函数
    print('sin(z) =', cmath.sin(z))
    print('cos(z) =', cmath.cos(z))
    print('tan(z) =', cmath.tan(z))

    # 指数和对数
    print('exp(z) =', cmath.exp(z))
    print('log(z) =', cmath.log(z))
    print('log10(z) =', cmath.log10(z))

    # 平方根
    print('sqrt(z) =', cmath.sqrt(z))

## 常量

::: data
cmath.e

自然对数的底 e，约等于 2.718281828459045。
:::

::: data
cmath.pi

圆周率 π，约等于 3.141592653589793。
:::

## 函数

::: function
cmath.phase(x)

返回复数的相位（辐角），以弧度为单位，范围在 (-pi, +pi\] 之间。
:::

::: function
cmath.polar(x)

返回复数的极坐标表示，作为一个元组 (r, phi)，其中 r 是模，phi 是相位。
:::

::: function
cmath.rect(r, phi)

返回复数，其模为 r，相位为 phi。
:::

::: function
cmath.sin(x)

返回复数的正弦值。
:::

::: function
cmath.cos(x)

返回复数的余弦值。
:::

::: function
cmath.tan(x)

返回复数的正切值。
:::

::: function
cmath.exp(x)

返回 e 的 x 次方。
:::

::: function
cmath.log(x)

返回 x 的自然对数（以 e 为底）。分支切割沿负实轴。
:::

::: function
cmath.log10(x)

返回 x 的以 10 为底的对数。分支切割沿负实轴。
:::

::: function
cmath.sqrt(x)

返回 x 的平方根。
:::
