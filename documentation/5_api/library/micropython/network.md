# `network`{.interpreted-text role="mod"} \-\-- 网络配置

::: {.module synopsis="网络配置"}
network
:::

此模块提供网络驱动程序和路由配置。要使用此模块，必须安装具有网络功能的
MicroPython
变体/构建。特定硬件的网络驱动程序在此模块中可用，用于配置硬件网络接口。配置的接口提供的网络服务随后可通过
`socket`{.interpreted-text role="mod"} 模块使用。

例如:

    # 连接/显示特定网络接口的 IP 配置
    # 请参见下面的特定驱动程序示例
    import network
    import time
    nic = network.Driver(...)
    if not nic.isconnected():
        nic.connect()
        print("等待连接...")
        while not nic.isconnected():
            time.sleep(1)
    print(nic.ipconfig("addr4"))

    # 现在像往常一样使用 socket
    import socket
    addr = socket.getaddrinfo('micropython.org', 80)[0][-1]
    s = socket.socket()
    s.connect(addr)
    s.send(b'GET / HTTP/1.1\r\nHost: micropython.org\r\n\r\n')
    data = s.recv(1000)
    s.close()

## 通用网络适配器接口

本节描述了所有网络接口类的（隐含的）抽象基类，这些类由不同硬件的
`MicroPython 端口 <MicroPython port>`{.interpreted-text role="term"}
实现。这意味着 MicroPython 实际上不提供 `AbstractNIC` 类，但任何实际的
NIC 类（如下所述）都实现了此处描述的方法。

::: {.AbstractNIC(id=None, ....)}
实例化网络接口对象。参数取决于网络接口。如果有多个相同类型的接口，第一个参数应该是
[id]{.title-ref}。
:::

::: method
AbstractNIC.active(\[is_active\])

如果传递布尔参数，则激活（\"up\"）或停用（\"down\"）网络接口。否则，如果未提供参数，则查询当前状态。大多数其他方法需要活动接口（在非活动接口上调用它们的行为是未定义的）。
:::

::: method
AbstractNIC.connect(\[service_id, key=None, \*, \...\])

连接接口到网络。此方法是可选的，仅适用于非\"始终连接\"的接口。如果没有给出参数，则连接到默认（或唯一）服务。如果给出单个参数，它是要连接的服务的主要标识符。它可能伴随有访问所述服务所需的密钥（密码）。根据网络媒介类型和/或特定设备，可能有更多任意的仅关键字参数。参数可用于：a）指定替代服务标识符类型；b）提供额外的连接参数。对于各种媒介类型，有不同的预定义/推荐参数集，其中包括：

- WiFi: *bssid* 关键字用于连接到特定的 BSSID（MAC 地址）
:::

::: method
AbstractNIC.disconnect()

断开与网络的连接。
:::

::: method
AbstractNIC.isconnected()

如果连接到网络，则返回 `True`，否则返回 `False`。
:::

::: method
AbstractNIC.scan(\*, \...)

扫描可用的网络服务/连接。返回带有发现的服务参数的元组列表。对于各种网络媒介，有不同的预定义/推荐元组格式，其中包括：

- WiFi: (ssid, bssid, channel, RSSI, security,
  hidden)。可能有特定于特定设备的其他字段。

该函数可能接受额外的关键字参数来过滤扫描结果（例如，扫描特定服务、特定通道、特定集合的服务等），并影响扫描持续时间和其他参数。在可能的情况下，参数名称应与
connect() 中的名称匹配。
:::

::: method
AbstractNIC.status(\[param\])

查询接口的动态状态信息。无参数调用时，返回值描述网络链接状态。否则，\*param\*
应该是要检索的特定状态参数的字符串名称。

返回类型和值取决于网络媒介/技术。可能支持的一些参数是：

- WiFi STA: 使用 `'rssi'` 检索 AP 信号的 RSSI
- WiFi AP: 使用 `'stations'` 检索连接到 AP 的所有 STA 的列表。该列表包含
  (MAC, RSSI) 形式的元组。
:::

::: method
AbstractNIC.ipconfig(\'param\') AbstractNIC.ipconfig(param=value, \...)

获取或设置特定于接口的 IP
配置接口参数。支持的参数如下（特定参数的可用性取决于端口和特定网络接口）：

- `dhcp4` (`True/False`) 通过 DHCP 获取 IPv4 地址、网关和 DNS
  服务器。此方法不会阻塞并等待获取地址。要检查是否获得了地址，请使用只读属性
  `has_dhcp4`。

- `gw4` 获取/设置 IPv4 默认网关。

- `dhcp6` (`True/False`) 通过无状态 DHCPv6 获取 DNS
  服务器。目前未实现通过 DHCPv6 获取 IP 地址。

- `autoconf6` (`True/False`) 通过路由器通告中共享的网络前缀获取无状态
  IPv6 地址。要检查是否获得了无状态地址，请使用只读属性
  `has_autoconf6`。

- `addr4` (例如 `192.168.0.4/24`) 获取当前 IPv4 地址和网络掩码作为
  `(ip, subnet)` 元组，无论此地址是如何获得的。此方法可用于设置静态 IPv4
  地址，既可以作为 `(ip, subnet)` 元组，也可以采用 CIDR 表示法。

- `addr6` (例如 `fe80::1234:5678`) 获取当前 IPv6 地址列表作为
  `(ip, state, preferred_lifetime, valid_lifetime)`
  元组。这包括链路本地、SLAAC 和静态地址。 `preferred_lifetime` 和
  `valid_lifetime` 表示每个 IPv6
  地址的剩余有效和首选生存期（以秒为单位）。 `state`
  指示地址的当前状态：

  - `0x08` - `0x0f` 表示地址是暂定的，计数发送的探测次数。
  - `0x10` 地址已弃用（但仍然有效）
  - `0x30` 地址是首选的（且有效）
  - `0x40` 地址重复，不能使用。

  此方法可用于设置静态 IPv6 地址，方法是将此参数设置为地址，如
  `fe80::1234:5678`。
:::

::::: method
AbstractNIC.ifconfig(\[(ip, subnet, gateway, dns)\])

:::: note
::: title
Note
:::

此函数已弃用，请使用 [ipconfig()]{.title-ref} 代替。
::::

获取/设置 IP 级网络接口参数：IP 地址、子网掩码、网关和 DNS
服务器。无参数调用时，此方法返回包含上述信息的 4
元组。要设置上述值，请传递包含所需信息的 4 元组。例如:

    nic.ifconfig(('192.168.0.4', '255.255.255.0', '192.168.0.1', '8.8.8.8'))
:::::

::: method
AbstractNIC.config(\'param\') AbstractNIC.config(param=value, \...)

获取或设置一般网络接口参数。这些方法允许处理标准 IP
配置之外的其他参数（由 [ipconfig()]{.title-ref}
处理）。这些包括特定于网络和特定于硬件的参数。对于设置参数，应使用关键字参数语法，并且可以一次设置多个参数。对于查询，参数名称应作为字符串引用，并且一次只能查询一个参数:

    # 设置 WiFi 接入点名称（正式称为 SSID）和 WiFi 通道
    ap.config(ssid='My AP', channel=11)
    # 逐个查询参数
    print(ap.config('ssid'))
    print(ap.config('channel'))
:::

## 特定网络类实现

以下具体类实现了 AbstractNIC 接口，并提供了控制各种类型网络接口的方法。

::: {.toctree maxdepth="1"}
network.WLAN.rst network.WLANWiPy.rst network.WIZNET5K.rst
network.LAN.rst network.PPP.rst
:::

## 网络函数

以下是网络模块中可用的函数。

::: function
country(\[code\])

获取或设置用于无线电合规性的两字母 ISO 3166-1 Alpha-2 国家代码。

如果提供了 *code*
参数，国家将设置为此值。如果函数无参数调用，它返回当前国家。

默认代码 `"XX"` 表示\"全球\"区域。
:::

::: function
hostname(\[name\])

获取或设置将在此网络上标识此设备的主机名。它将被所有接口使用。

此主机名用于：

:   - 在客户端请求中发送到 DHCP 服务器。（如果使用 DHCP）
    - 通过 mDNS 广播。（如果启用）

如果提供了 *name*
参数，主机名将设置为此值。如果函数无参数调用，它返回当前主机名。

主机名的更改通常仅在连接期间应用。对于 DHCP，这是因为主机名是 DHCP
客户端请求的一部分，而大多数端口中的 mDNS
实现仅在连接期间初始化主机名一次。因此，您必须在激活/连接网络接口之前设置主机名。

主机名的长度限制为 32 个字符。
`MicroPython 端口 <MicroPython port>`{.interpreted-text role="term"}
可能出于内存原因选择设置更低的限制。如果给定的名称不适合，将引发
[ValueError]{.title-ref}。

默认主机名通常是板的名称。
:::

::: function
ipconfig(\'param\') ipconfig(param=value, \...)

获取或设置全局 IP 配置参数。
支持的参数如下（特定参数的可用性取决于端口和特定网络接口）：

- `dns` 获取/设置 DNS 服务器。此方法可以支持 IPv4 和 IPv6 地址。
- `prefer` (`4/6`) 指定如果域名同时具有 A 和 AAAA
  记录，返回哪种地址类型。请注意，这不会清除本地 DNS
  缓存，因此任何先前获得的地址可能不会更改。
:::

::: function
phy_mode(\[mode\])

获取或设置 PHY 模式。

如果提供了 *mode* 参数，PHY
模式将设置为此值。如果函数无参数调用，它返回当前 PHY 模式。

可能的模式定义为常量：

:   - `MODE_11B` \-- IEEE 802.11b，
    - `MODE_11G` \-- IEEE 802.11g，
    - `MODE_11N` \-- IEEE 802.11n。

可用性：ESP8266。
:::
