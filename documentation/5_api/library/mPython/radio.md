:::: {#radio}
::: {.module synopsis="无线广播相关功能"}
radio
:::
::::

`radio`{.interpreted-text role="mod"} \-\-- radio 无线广播相关功能
\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\--

radio 模块是基于
[ESP-NOW](https://docs.espressif.com/projects/esp-idf/zh_CN/latest/esp32/api-reference/network/esp_now.html)
无连接 Wi-Fi 通信协议而实现无线广播功能,支持13
Channel,在相同的Channel内能接收到成员发出的广播消息,适合30米范围内的多板组网的通讯。

# 函数

开启无线功能

关闭无线功能

配置无线参数

- `channel` (int): 无线通道,范围1\~13

接收无线广播消息,消息以字符串形式返回。最大可接收250字节数据。如果没有接收到消息,则返回
`None` 。当 `receive` 内参数为 `True` ,即 `receive(True)`
,返回(msg,mac)的二元组。默认缺省 `receive(False)` ,即只返回msg。

接收无线广播消息,消息以字节形式返回。其他同 `radio.receive()` 相同。

发送无线广播消息,发送数据类型为字符串。当发送成功后返回True,否则返回False。

发送无线广播消息,发送数据类型为字节。当发送成功后返回True,否则返回False。

::: {.literalinclude caption="无线广播示例" linenos=""}
/\_static/examples/radio/radio.py
:::
