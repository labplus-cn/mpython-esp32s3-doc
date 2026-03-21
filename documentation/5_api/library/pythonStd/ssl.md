# `ssl`{.interpreted-text role="mod"} \-- SSL/TLS 模块

::: {.module synopsis="TLS/SSL 套接字对象包装器"}
ssl
:::

这个模块实现了相应 `CPython`{.interpreted-text role="term"}
模块的一个子集，如下所述。有关更多信息，请参阅原始CPython文档:
[ssl](https://docs.python.org/3.5/library/ssl.html#module-ssl)

此模块提供对客户端和服务器端网络套接字的传输层安全性（以前称为\"安全套接字层\"）加密和对等身份验证工具的访问。

## 函数

::: function
ssl.wrap_socket(sock, server_side=False, key=None, cert=None,
cert_reqs=CERT_NONE, cadata=None, server_hostname=None,
do_handshake=True)

包装给定的sock并返回一个新的包装套接字对象。此函数的实现是首先创建一个SSLContext，然后在该上下文对象上调用SSLContext.wrap_socket方法。参数sock、server_side和server_hostname原样传递给方法调用。参数do_handshake作为do_handshake_on_connect传递。其余参数具有以下行为：

- `cert_reqs`
  确定对等方（服务器或客户端）是否必须出示有效证书。请注意，对于基于mbedtls的端口，ssl.CERT_NONE和ssl.CERT_OPTIONAL不会验证任何证书，只有ssl.CERT_REQUIRED会。
- `cadata`
  是一个字节对象，包含将验证对等方证书的CA证书链（DER格式）。目前仅支持单个DER编码的证书。

根据特定MicroPython端口中底层模块的实现，上面的一些或所有关键字参数可能不受支持。
:::

:::: warning
::: title
Warning
:::

模块的某些实现不验证服务器证书，这使得建立的SSL连接容易发生中间人攻击。
CPython的wrap_socket返回一个具有典型套接字方法（如send、recv等）的SSLSocket对象。MicroPython的wrap_socket返回一个更类似于CPython的SSLObject的对象，它没有这些套接字方法。
::::

## 类

::::::::::::: SSLContext
::: {.ssl.SSLContext(protocol, ./)}
创建一个新的SSLContext实例。protocol参数必须是PROTOCOL\_\*常量之一。
:::

:::: method
SSLContext.load_cert_chain(certfile, keyfile)

加载私钥和相应的证书。certfile是证书文件路径的字符串。keyfile是私钥文件路径的字符串。

::: {.admonition .attention}
Difference to CPython

MicroPython扩展：certfile和keyfile可以是字节对象而不是字符串，在这种情况下，它们被解释为实际的证书/密钥数据。
:::
::::

::: method
SSLContext.load_verify_locations(cafile=None, cadata=None)

加载将验证对等方证书的CA证书链。cafile是CA证书的文件路径。cadata是包含CA证书的字节对象。应该只提供这些参数中的一个。
:::

::: method
SSLContext.get_ciphers()

获取启用的密码列表，以字符串列表形式返回。
:::

::: method
SSLContext.set_ciphers(ciphers)

设置使用此上下文创建的套接字的可用密码。ciphers应该是IANA密码套件格式的字符串列表。
:::

::: method
SSLContext.wrap_socket(sock, \*, server_side=False,
do_handshake_on_connect=True, server_hostname=None, client_id=None)

采用流sock（通常是SOCK_STREAM类型的socket.socket实例），并返回ssl.SSLSocket的实例，该实例将基础流包装在SSL上下文中。返回的对象具有通常的流接口方法，如
`read()` ，`write()` 等。

- `server_side`
  选择包装的套接字是在服务器端还是客户端。服务器端SSL套接字应该从非SSL侦听服务器套接字上的
  `accept()` 返回的普通套接字创建。
- `do_handshake_on_connect`
  确定握手是作为wrap_socket的一部分完成还是延迟到初始读写时完成。对于阻塞套接字，立即进行握手是标准的。对于非阻塞套接字（即当传递给wrap_socket的sock处于非阻塞模式时），握手通常应该延迟，因为否则wrap_socket会阻塞直到完成。请注意，在AXTLS中，握手可以延迟到第一次读写，但随后会阻塞直到完成。
- `server_hostname`
  用于客户端，设置要对照接收到的服务器证书检查的主机名。它还设置服务器名称指示（SNI）的名称，允许服务器呈现适当的证书。
- `client_id`
  是MicroPython特定的扩展参数，仅在实现DTLS服务器时使用。有关详细信息，请参阅DTLS支持。
:::

::: attribute
SSLContext.verify_mode

设置或获取对等证书验证的行为。必须是CERT\_\*常量之一。
:::

:::: note
::: title
Note
:::

ssl.CERT_REQUIRED要求设备的日期/时间正确设置，例如使用mpremote rtc
\--set或ntptime，并且在客户端时必须指定server_hostname。
::::
:::::::::::::

## DTLS支持

::: {.admonition .attention}
Difference to CPython

这是MicroPython扩展。
:::

在大多数端口上，此模块通过可用于SSLContext的protocol参数的PROTOCOL_DTLS_CLIENT和PROTOCOL_DTLS_SERVER常量支持客户端和服务器模式的DTLS。
在这种情况下，底层套接字应表现为数据报套接字（即类似于使用socket.AF_INET作为af和socket.SOCK_DGRAM作为类型打开的套接字）。
DTLS仅在使用mbedTLS的端口上受支持，并且在大多数配置中默认启用，但可以通过将MICROPY_PY_SSL_DTLS定义为0来手动禁用。

### DTLS服务器支持

MicroPython的DTLS服务器支持配置为\"Hello Verify\"，这是DTLS
1.2所必需的。这对DTLS客户端是透明的，但在MicroPython中实现DTLS服务器时需要考虑以下相关事项：

- 服务器在调用SSLContext.wrap_socket()时应传递额外的参数client_id。此ID必须是一个字节对象（或类似对象），带有表示客户端的传输特定标识符。最简单的方法是将socket.recv_from()返回的(client_ip,
  client_port)元组转换为字节字符串，即： :

      _, client_addr = sock.recvfrom(1, socket.MSG_PEEK)
      sock.connect(client_addr)  # 连接回客户端
      sock = ssl_ctx.wrap_socket(sock, server_side=True,
                                 client_id=repr(client_addr).encode())

- 客户端第一次连接时，服务器对wrap_socket的调用将失败，出现OSError错误\"Hello
  Verify Required\"。这是因为DTLS\"Hello Verify\"
  cookie尚未被客户端知道。如果同一客户端第二次连接，则wrap_socket将成功。

- \"Hello Verify\"的DTLS
  cookie与SSLContext对象相关联，因此应使用相同的SSLContext对象来包装来自同一客户端的后续连接。cookie实现包括超时，并且无论有多少客户端连接，内存使用都是恒定的，因此可以在服务器的整个生命周期中重用同一个SSLContext对象。

## 异常

::: data
ssl.SSLError

此异常不存在。而是使用它的基类OSError。
:::

## 常量

::: data
ssl.PROTOCOL_TLS_CLIENT ssl.PROTOCOL_TLS_SERVER ssl.PROTOCOL_DTLS_CLIENT
(当启用DTLS支持时) ssl.PROTOCOL_DTLS_SERVER (当启用DTLS支持时)

protocol参数的支持值。
:::

::: data
ssl.CERT_NONE ssl.CERT_OPTIONAL ssl.CERT_REQUIRED

cert_reqs参数和SSLContext.verify_mode属性的支持值。
:::
