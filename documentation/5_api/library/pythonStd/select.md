# `select`{.interpreted-text role="mod"} \-- 高效地等待I/O

::: {.module synopsis="wait for events on a set of streams"}
select
:::

这个模块实现了相应 `CPython`{.interpreted-text role="term"}
模块的一个子集，如下所述。有关更多信息，请参阅原始CPython文档:
[select](https://docs.python.org/3.5/library/select.html#module-select)

该模块提供了有效等待多个事件 `streams`（准备好操作的选择流）的功能。

## 函数

::: function
poll()

创建Poll类的实例。
:::

::: function
select(rlist, wlist, xlist\[, timeout\])

等待对象上的活动。
此函数由一些MicroPython端口提供以实现兼容性，效率不高。推荐使用Poll代替。

- `rlist`：等待读就绪的文件描述符数组
- `wlist`：等待写就绪的文件描述符数组
- `xlist`：等待异常的数组
- `timeout`：等待时间（单位：秒）
:::

## 类 Poll

### 方法

::: method
poll.register(obj\[, eventmask\])

注册一个用以监控的对象, [eventmask]{.title-ref} 是逻辑OR：

- `obj` :被监控的对象

  - `select.POLLIN` - 读取可用数据
  - `select.POLLOUT` - 写入更多数据

  注意：像标志 `select.POLLHUP` 和 `select.POLLERR` 不是有效的输入
  [eventmask]{.title-ref}（这些是从poll()返回的不请自来的事件，无论他们是否被要求）。
  这个语义是按POSIX。

`eventmask` 默认为 `select.POLLIN | select.POLLOUT`.

可以多次为同一个 [obj]{.title-ref} 调用此函数。连续调用将更新obj的
[eventmask]{.title-ref} 到的值 [eventmask]{.title-ref}（即会表现为
`modify()` ）。
:::

::: method
poll.unregister(obj)

从轮询中取消注册obj。
:::

::: method
poll.modify(obj, eventmask)

修改已注册的对象 `obj` 的eventmask。如果未注册obj，OSError
则会出现ENOENT错误。
:::

:::: method
poll.poll(timeout=-1, /)

等待至少一个已注册的对象准备就绪或具有异常条件，可选的超时（以毫秒为单位）（如果
未指定超时 arg或-1，则没有超时）。

返回列表( `obj`, `event`,
\...)的元组。元组中可能还有其他元素，具体取决于平台和版本，因此不要假设其大小为2.

event元素指定流发生的事件，并且是 `select.POLL*`
上述常量的组合。需要注意的是标志 `select.POLLHUP` 和 `select.POLLERR`
可以在任何时候（即使不要求）返回的，必须采取相应的行动（从调查未注册并有可能关闭相应的流），否则所有的进一步调用
`poll()` 可以用这些标志设置立即返回再次为这个流。

如果超时，则返回空列表。

调用poll.poll保证在进入轮询循环之前调用待处理的回调函数。

::: {.admonition .attention}
与CPython区别

返回的元组可能包含超过2个元素，如上所述。
:::
::::

:::: method
poll.ipoll(timeout=-1, flags=0, /)

与 `poll.poll`{.interpreted-text role="meth"}
类似，但是返回一个产生被调用函数所有元组的迭代器。该函数提供高效的、无位置的在流中进行轮询的方法。

如果flags为1，则采用事件的一次性行为：发生事件的流将自动重置其事件掩码（相当于poll.modify(obj,
0)），因此在使用poll.modify()设置新掩码之前，不会处理此类流的新事件。此行为对异步I/O调度程序很有用。

调用poll.ipoll保证在进入轮询循环之前调用待处理的回调函数。

::: {.admonition .attention}
与CPython区别

该函数是MicroPython的扩展。
:::
::::
