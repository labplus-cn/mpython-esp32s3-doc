# `espnow`{.interpreted-text role="mod"} \-- ESP-NOW无线协议支持

::: {.module synopsis="ESP-NOW无线协议支持"}
espnow
:::

该模块提供了ESP-NOW无线协议的支持，这是一种由Espressif开发的低延迟通信协议。

## 类

:::::::::: ESPNow
::: classmethod
\_\_init\_\_()

初始化ESPNow对象。
:::

::: method
active(\[active\])

（可选）更改ESPNow的活动状态，并返回当前状态。

参数:

:   - `active`: 布尔值，True表示激活，False表示禁用
:::

::: method
add_peer(peer)

添加一个对等设备。

参数:

:   - `peer`: 对等设备的MAC地址（bytes对象，长度为6）
:::

::: method
remove_peer(peer)

移除一个对等设备。

参数:

:   - `peer`: 对等设备的MAC地址（bytes对象，长度为6）
:::

::: method
send(peer, data, \[sync=False\])

发送数据到对等设备。

参数:

:   - `peer`: 对等设备的MAC地址（bytes对象，长度为6）
    - `data`: 要发送的数据（类似字节）
    - `sync`: 是否同步发送（默认为False）
:::

::: method
recv(\[timeout\])

接收来自对等设备的数据。

参数:

:   - `timeout`: 超时时间（毫秒，可选）

返回值:

:   元组 (peer, data)，其中peer是发送方的MAC地址，data是接收到的数据
:::

::: method
irq(handler)

注册接收数据的回调函数。

参数:

:   - `handler`: 回调函数，接收参数 (peer, data)
:::
::::::::::
