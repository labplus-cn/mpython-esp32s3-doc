# `heapq`{.interpreted-text role="mod"} \-- 堆队列算法

::: {.module synopsis="堆队列算法"}
heapq
:::

这个模块实现了相应 `CPython`{.interpreted-text role="term"}
模块的一个子集，如下所述。有关更多信息，请参阅原始CPython文档:
[heapq](https://docs.python.org/3.5/library/heapq.html#module-heapq)

该模块实现最小堆队列算法。

堆队列本质上是一个列表，其元素存储方式使得列表的第一个元素始终是最小的。

## 函数

::: function
heappush(heap, item)

将 `item` 推入 `heap`。
:::

::: function
heappop(heap)

从 `heap` 中弹出第一个项目并返回它。如果堆为空，则引发 IndexError。
返回的项目将是堆中最小的项目。
:::

::: function
heapify(x)

将列表 `x` 转换为堆。这是一个原地操作。
:::
