# `platform`{.interpreted-text role="mod"} \-\-- 访问底层平台的标识数据

::: {.module synopsis="访问底层平台的标识数据"}
platform
:::

该模块实现了相应 `CPython`{.interpreted-text role="term"}
模块的一个子集，如下所述。有关更多信息，请参阅原始CPython文档:
[platform](https://docs.python.org/3.5/library/platform.html#module-platform)

该模块尝试检索尽可能多的平台标识数据。它通过函数API提供这些信息。

快速使用示例:

    import platform

    # 获取平台信息
    print('Platform:', platform.platform())
    print('Python compiler:', platform.python_compiler())
    print('Libc version:', platform.libc_ver())
    print('Processor:', platform.processor())

## 函数

::: function
platform.platform()

返回一个标识底层平台的字符串。此字符串由以下顺序的几个子字符串组成，以连字符(-)分隔：

- 平台系统的名称（例如 Unix、Windows 或 MicroPython）
- MicroPython 版本
- 平台的架构
- 底层平台的版本
- MicroPython 链接的 libc 的名称及其对应版本的连接。

例如，这可能是
\"MicroPython-1.20.0-xtensa-IDFv4.2.4-with-newlib3.0.0\"。
:::

::: function
platform.python_compiler()

返回一个标识用于编译 MicroPython 的编译器的字符串。
:::

::: function
platform.libc_ver()

返回字符串元组 (lib, version)，其中 lib 是 MicroPython 链接的 libc
的名称，version 是该 libc 的对应版本。
:::

::: function
platform.processor()

返回一个包含处理器详细名称的字符串（如果可用）。
如果不知道处理器的名称，它将返回一个空字符串。 这目前仅在 RISC-V
目标（32位和64位）上可用。
:::
