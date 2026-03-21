------------------------------------------------------------------------

::: {.module synopsis="高效的数值数组"}
array
:::

这个模块实现了相应 `CPython`{.interpreted-text role="term"}
模块的一个子集，如下所述。有关更多信息，请参阅原始CPython文档:
[array](https://docs.python.org/3.5/library/array.html#module-array)

支持的格式的代码： `b`, `B`, `h`, `H`, `i`, `I`, `l`, `L`, `q`, `Q`,
`f`, `d` (后者2取决于浮点支持).

# 类

::: {.array.array(typecode[, .iterable])}
使用给定类型的元素创建数组。数组的初始内容由 [iterable]{.title-ref}
给出。如果未提供，则创建空数组。

除了下面的方法外，数组对象还实现了缓冲区协议。这意味着整个数组的内容可以通过memoryview或其他使用此协议的接口作为原始字节访问。

> ::: method
> append(val)
>
> 将新元素val附加到数组的末尾，使其增长.
> :::
>
> ::: method
> extend(iterable)
>
> 将迭代中包含的新元素追加到数组的末尾，增长它.
> :::
>
> ::: method
> \_\_getitem\_\_(index)
>
> 数组的索引读取，调用方式为 a\[index\]（其中a是数组）。
> 如果index是int，返回一个值；如果index是slice，返回一个数组。
> 负索引从末尾计数，如果索引超出范围，将抛出IndexError。
> 注意：\_\_getitem\_\_不能直接调用（a.\_\_getitem\_\_(index)会失败），也不在\_\_dict\_\_中，但a\[index\]可以工作。
> :::
>
> ::: method
> \_\_setitem\_\_(index, value)
>
> 数组的索引写入，调用方式为 a\[index\] = value（其中a是数组）。
> 如果index是int，value是单个值；如果index是slice，value是一个数组。
> 负索引从末尾计数，如果索引超出范围，将抛出IndexError。
> 注意：\_\_setitem\_\_不能直接调用（a.\_\_setitem\_\_(index,
> value)会失败），也不在\_\_dict\_\_中，但a\[index\] = value可以工作。
> :::
>
> ::: method
> \_\_len\_\_()
>
> 返回数组中的项目数，调用方式为 len(a)（其中a是数组）。
> 注意：\_\_len\_\_不能直接调用（a.\_\_len\_\_()会失败），方法也不在\_\_dict\_\_中，但len(a)可以工作。
> :::
>
> ::: method
> \_\_add\_\_(other)
>
> 返回一个新数组，是该数组与other的连接，调用方式为 a +
> other（其中a和other都是数组）。
> 注意：\_\_add\_\_不能直接调用（a.\_\_add\_\_(other)会失败），也不在\_\_dict\_\_中，但a +
> other可以工作。
> :::
>
> ::: method
> \_\_iadd\_\_(other)
>
> 将数组与other原地连接，调用方式为 a +=
> other（其中a和other都是数组）。相当于extend(other)。
> 注意：\_\_iadd\_\_不能直接调用（a.\_\_iadd\_\_(other)会失败），也不在\_\_dict\_\_中，但a
> += other可以工作。
> :::
>
> ::: method
> \_\_repr\_\_()
>
> 返回数组的字符串表示，调用方式为 str(a) 或 repr(a)（其中a是数组）。
> 返回字符串 \"array(\<type\>,
> \[\<elements\>\])\"，其中\<type\>是数组的类型代码字母，\<elements\>是数组元素的逗号分隔列表。
> 注意：\_\_repr\_\_不能直接调用（a.\_\_repr\_\_()会失败），也不在\_\_dict\_\_中，但str(a)和repr(a)都可以工作。
> :::
:::
