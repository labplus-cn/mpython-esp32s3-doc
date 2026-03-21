# `gc`{.interpreted-text role="mod"} \-- 回收内存碎片

::: {.module synopsis="回收内存碎片"}
gc
:::

这个模块实现了相应 `CPython`{.interpreted-text role="term"}
模块的一个子集，如下所述。有关更多信息，请参阅原始CPython文档:
[gc](https://docs.python.org/3.5/library/gc.html#module-gc)

## 函数

::: function
enable()

启用自动垃圾回收。
:::

::: function
disable()

禁用自动垃圾回收。堆内存仍然可以分配，但可以通过
`gc.collect`{.interpreted-text role="meth"} 函数进行手动垃圾回收。
:::

::: function
collect()

运行垃圾回收。
:::

::: function
mem_alloc()

返回Python代码分配的堆RAM的字节数.

> ::: {.admonition .attention}
> 与CPython的区别
>
> 此功能是MicroPython扩展.
> :::
:::

:::: function
mem_free()

返回Python代码可分配的堆RAM的字节数，如果此数量未知，则返回-1.

::: {.admonition .attention}
与CPython的区别

此功能是MicroPython扩展.
:::
::::

:::: function
threshold(\[amount\])

设置或查询其他GC分配阈值。通常，只有在无法满足新分配时，即在内存不足（OOM）条件下才会触发集合。
如果调用此函数，除了OOM之外，每次分配了amount字节后都会触发一个集合（总共，自从上一次分配了这么多的字节以来）。
amount通常被指定为小于完整堆大小，意图在堆耗尽之前触发集合，并希望早期集合可以防止过多的内存碎片。
这是一种启发式度量，其效果因应用程序而异，以及amount参数的最佳值。

不带参数调用函数将返回阈值的当前值。值-1表示禁用的分配阈值。

::: {.admonition .attention}
与CPython的区别

此函数是MicroPython扩展。CPython具有类似的功能 - `set_threshold()`
但由于不同的GC实现，它的签名和语义是不同的。
:::
::::
