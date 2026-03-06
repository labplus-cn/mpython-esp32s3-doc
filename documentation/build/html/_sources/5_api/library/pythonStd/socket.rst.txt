*******************************
:mod:`socket` -- socket 模块
*******************************

.. module:: socket
   :synopsis: socket 模块

这个模块实现了相应 :term:`CPython` 模块的一个子集，如下所述。有关更多信息，请参阅原始CPython文档: `socket <https://docs.python.org/3.5/library/socket.html#module-socket>`_

该模块提供BSD socket接口的访问。

.. admonition:: 与CPython区别
   :class: attention

    为提高效率与一致性，MicroPython中的套接字对象直接实现 `stream`（类文件）接口。在CPython中，
    需使用 ``makefile()`` 方法来将socket转换为类文件对象。该方法仍由MicroPython（但是是无操作）支持，
    所以在CPython的兼容性问题上，请一定使用该方法。

Socket地址格式
------------------------

``socket`` 模块的本机套接字地址格式是一个由 ``getaddrinfo`` 函数返回的不透明数据类型，
须用其来解析文本地址（包括数字型地址）::

    sockaddr = socket.getaddrinfo('www.micropython.org', 80)[0][-1]
    # 您必须使用getaddrinfo()，即使是用于数字型地址
    sockaddr = socket.getaddrinfo('127.0.0.1', 80)[0][-1]
    # 现在您可以使用这一地址了
    sock.connect(sockaddr)

使用 ``getaddrinfo`` 是处理地址最有效（在内存和处理能力方面皆是如此）且最便捷的方式。

然而，socket模块（注意与这里描述的原生MicroPython socket模块的区别）提供了CPython兼容的方式，使用元组来指定地址，如下所述。请注意，根据MicroPython端口的不同，socket模块可能是内置的，也可能需要从micropython-lib安装（如MicroPython Unix端口的情况），并且一些端口仍然只接受元组格式的数字地址，需要使用getaddrinfo函数来解析域名。

总结：

- 编写可移植应用程序时始终使用getaddrinfo。
- 下面描述的元组地址可以作为快速黑客和交互式使用的快捷方式，如果您的端口支持它们。

socket模块的元组地址格式：

- IPv4: (ipv4_address, port)，其中ipv4_address是带有点表示法的数字IPv4地址的字符串，例如 "8.8.8.8"，port是1-65535范围内的整数端口号。注意，域名不被接受为ipv4_address，它们应该首先使用socket.getaddrinfo()解析。
- IPv6: (ipv6_address, port, flowinfo, scopeid)，其中ipv6_address是带有冒号表示法的数字IPv6地址的字符串，例如 "2001:db8::1"，port是1-65535范围内的整数端口号。flowinfo必须为0。scopeid是链路本地地址的接口作用域标识符。注意，域名不被接受为ipv6_address，它们应该首先使用socket.getaddrinfo()解析。IPv6支持的可用性取决于MicroPython端口。

函数
---------

.. function:: socket.getaddrinfo(host, port, af=0, type=0, proto=0, flags=0, /)

   将主机/端口参数转换为包含创建连接到该服务的套接字所需的所有参数的5元组序列。参数af、type和proto（与socket()函数具有相同的含义）可用于过滤返回哪种类型的地址。如果未指定参数或为零，则可以返回所有地址组合（需要在用户端进行过滤）。

   生成的5元组列表具有以下结构：
   (family, type, proto, canonname, sockaddr)

   下面显示了如何连接到给定的URL：

   ::

     s = socket.socket()
     # 这假设如果未指定"type"，将返回SOCK_STREAM的地址，这可能不成立
     s.connect(socket.getaddrinfo('www.micropython.org', 80)[0][-1])

   推荐使用过滤参数：

   ::

     s = socket.socket()
     # 保证返回可用于流操作的可连接地址
     s.connect(socket.getaddrinfo('www.micropython.org', 80, 0, SOCK_STREAM)[0][-1])

   .. admonition:: 与CPython区别
      :class: attention

      CPython在该函数出错时会引发 ``socket.gaierror`` 异常（OSError子类）。MicroPython没有socket.gaierror，直接引发OSError。注意： ``getaddrinfo()`` 的错误编号形成一个单独的命名空间，可能与errno模块中的系统错误编号不匹配。为了区分 ``getaddrinfo()`` 错误，它们用负数表示，而标准系统错误用正数表示（错误编号可通过异常对象的 e.args[0] 属性访问）。使用负值是临时细节，未来可能会改变。

.. function:: socket.inet_ntop(af, bin_addr)

   将给定地址族af的二进制网络地址bin_addr转换为文本表示：

   ::

     >>> socket.inet_ntop(socket.AF_INET, b"\x7f\0\0\1")
     '127.0.0.1'

.. function:: socket.inet_pton(af, txt_addr)

   将给定地址族af的文本网络地址txt_addr转换为二进制表示：

   ::

     >>> socket.inet_pton(socket.AF_INET, "1.2.3.4")
     b'\x01\x02\x03\x04'

类
============

.. class:: socket.socket(af=AF_INET, type=SOCK_STREAM, proto=IPPROTO_TCP, /)

   使用给定的地址族、套接字类型和协议号创建一个新的套接字。注意，在大多数情况下不需要指定proto（也不推荐，因为某些MicroPython端口可能省略IPPROTO_*常量）。相反，type参数会自动选择所需的协议：

   ::

     # 创建STREAM TCP套接字
     socket(AF_INET, SOCK_STREAM)
     # 创建DGRAM UDP套接字
     socket(AF_INET, SOCK_DGRAM)

方法
-------

.. method:: socket.close()

   标记套接字已关闭并释放所有资源。一旦发生这种情况，套接字对象上的所有未来操作都将失败。如果协议支持，远程端将接收EOF指示。

   内存碎片回收时socket会自动关闭，但还是推荐在必要时用 close() 去关闭

.. method:: socket.bind(address)

   以列表或元组的方式绑定地址和端口号。套接字必须尚未绑定。

   - ``address`` ：一个包含地址和端口号的列表或元组。

   示例::

     addr = ("127.0.0.1",10000)
     s.bind(addr)

.. method:: socket.listen([backlog])

   监听socket，使服务器能够接收连接。如果指定了 ``backlog`` ，则必须至少为0（如果低，则将其设置为0）; 并指定在拒绝新连接之前系统将允许的未接受连接数。如果未指定，则选择默认的合理值。

   -  ``backlog`` ：接受套接字的最大个数，至少为0，如果没有指定，则默认一个合理值。

.. method:: socket.accept()

   接收连接请求。socket需要指定地址并监听连接。返回值是 (conn, address)，
   其中conn是用来接收和发送数据的套接字，address是绑定到另一端的套接字。
   
   - ``conn``：新的套接字对象，可以用来收发消息
   - ``address``：连接到服务器的客户端地址

   .. admonition::

     只能在绑定地址端口号和监听后调用，返回conn和address。

.. method:: socket.connect(address)

   连接到指定地址的远端套接字。

   - ``address``：地址和端口号的元组或列表

   示例::

     host = "192.168.3.147"
     port = 100
     s.connect((host, port))

.. method:: socket.send(bytes)

   将数据发送到套接字。套接字必须连接到远程套接字。返回发送的字节数，可能小于数据长度 ("short write")。

   - ``bytes``：bytes类型数据

.. method:: socket.sendall(bytes)

   将所有数据发送到套接字。套接字必须连接到远程套接字。与 ``send()`` 此不同，此方法将尝试通过连续发送数据块来发送所有数据。

   此方法在非阻塞套接字上的行为未定义。因此，在MicroPython上，建议使用 ``write()`` 方法，它具有相同的"无短写入"策略来阻塞套接字，并将返回在非阻塞套接字上发送的字节数。

   - ``bytes``：bytes类型数据

.. method:: socket.recv(bufsize[, flags])

   从套接字接收数据。返回值是表示接收数据的字节对象。一次接收的最大数据量由 `bufsize` 指定。
   大多数端口支持可选的flags参数。可用的标志在socket模块中定义为常量，与CPython中的含义相同。MSG_PEEK和MSG_DONTWAIT在所有接受flags参数的端口上都受支持。

   - ``bufsize``：指定一次接收的最大数据量

   示例::

     data = conn.recv(1024)

.. method:: socket.sendto(bytes, address)

   将数据发送到套接字。套接字不应连接到远程套接字，因为目标套接字由地址指定。用于UDP通信，返回发送的数据大小。

   - ``bytes``：bytes类型数据
   - ``address``：目标地址和端口号的元组

.. method:: socket.recvfrom(bufsize[, flags])

   从套接字接收数据。返回值是一对（字节，地址），其中bytes是表示接收数据的字节对象，address是发送数据的套接字的地址。用于UDP通信。
   有关可选flags参数的说明，请参见recv函数。

   - ``bufsize``：指定一次接收的最大数据量

.. method:: socket.setsockopt(level, optname, value)

   设置给定套接字选项的值。所需的符号常量在套接字模块中定义（SO_ *等）。该值可以是整数或表示缓冲区的类字节对象。

   - ``level``：套接字选项级别
   - ``optname``：socket 选项
   - ``value``：可以是一个整数，也可以是一个表示缓冲区的bytes类对象。

   示例::

     s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)

.. method:: socket.settimeout(value)

   注意：并非每个端口都支持此方法，见下文。
   
   设置阻塞套接字操作的超时。value参数可以是非负浮点数，表示秒数，也可以是None。如果给出非零值，则如果在操作完成之前超时时间段已过，后续套接字操作将引发OSError异常。如果给出零，则套接字处于非阻塞模式。如果给出None，则套接字处于阻塞模式。

   并非每个MicroPython端口都支持此方法。更可移植和通用的解决方案是使用select.poll对象。这允许同时等待多个对象（不仅是套接字，还包括支持轮询的通用流对象）。示例：

   ::

     # 代替：
     s.settimeout(1.0)  # 时间（秒）
     s.read(10)  # 可能超时

     # 使用：
     poller = select.poll()
     poller.register(s, select.POLLIN)
     res = poller.poll(1000)  # 时间（毫秒）
     if not res:
         # s仍然没有准备好输入，即操作超时

   .. admonition:: 与CPython区别
      :class: attention

      CPython在超时的情况下引发socket.timeout异常，这是OSError的子类。MicroPython直接引发OSError。如果您使用except OSError:来捕获异常，您的代码将在MicroPython和CPython中都有效。

.. method:: socket.setblocking(flag)

   设置socket的阻塞或非阻塞模式：若标记为false，则将该socket设置为非阻塞模式，而非阻塞模式。

   该方法为某些settimeout()调用的简写:

      * ``sock.setblocking(True)`` 相当于 ``sock.settimeout(None)``
      * ``sock.setblocking(False)`` 相当于 ``sock.settimeout(0)``

.. method:: socket.makefile(mode='rb', buffering=0, /)

   返回一个与socket相关联的文件对象。具体的返回类型取决于给定makefile()的参数。该支持仅限于二进制模式（ 'rb'、'wb' 和 'rwb'）。
   CPython的参数：不支持 encoding、errors 和 newline。

   .. admonition:: 与CPython区别
      :class: attention

      由于MicroPython不支持缓冲流，则将忽略缓冲参数的值，且将按照该值为0（未缓冲）时处理。

   .. admonition:: 与CPython区别
      :class: attention

      关闭所有由makefile()返回的文件对象，同样将关闭原始socket。

.. method:: socket.read([size])

   从socket中读取size字节。返回一个字节对象。若未给定 ``size`` ，则读取从套接字可用的所有数据直到EOF；因此，该方法在套接字关闭之前不会返回。此函数尝试读取尽可能多的请求数据（无"短读"）。但对于非阻塞套接字，这可能不可能，然后将返回较少的数据。

.. method:: socket.readinto(buf[, nbytes])

   将字节读取入缓冲区。若指定 nbytes ，则最多读取该数量的字节。否则，最多读取 len(buf) 数量的字节。正如 ``read()`` ，该方法遵循"no short reads"方法。

   返回值：读取并存入缓冲区的字节数量

.. method:: socket.readline()

   接收一行数据，遇换行符结束，并返回接收数据的对象 。

.. method:: socket.write(buf)

   将字节缓冲区写入套接字。此函数将尝试将所有数据写入套接字（无"短写"）。但是，对于非阻塞套接字，这可能是不可能的，并且返回值将小于buf的长度。

   返回值：写入的字节数。

.. exception:: socket.error

   MicroPython没有此异常。

   .. admonition:: 与CPython区别
        :class: attention

        CPython曾经有一个socket.error现已弃用的异常，并且是别名 ``OSError`` 。在MicroPython中，``OSError`` 直接使用。

常数
------

.. data:: AF_INET
          AF_INET6

   地址簇类型。可用性取决于特定的MicroPython端口。

.. data:: SOCK_STREAM
          SOCK_DGRAM

   套接字类型。

.. data:: IPPROTO_UDP
          IPPROTO_TCP

   IP协议号。可用性取决于特定的MicroPython端口。
   注意，您不需要在socket.socket()调用中指定这些，因为SOCK_STREAM套接字类型会自动选择IPPROTO_TCP，而SOCK_DGRAM会选择IPPROTO_UDP。因此，这些常量的唯一实际用途是作为setsockopt()的参数。

.. data:: SOL_*

   套接字选项级别（setsockopt()的参数）。确切的清单取决于MicroPython端口。

.. data:: SO_*

   套接字选项（setsockopt()的参数）。确切的清单取决于MicroPython端口。

WiPy特定的常量：

.. data:: IPPROTO_SEC

   创建SSL兼容套接字的特殊协议值。
