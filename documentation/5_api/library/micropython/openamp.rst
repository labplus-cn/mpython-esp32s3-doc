*********************************************************************
:mod:`openamp` --- 提供标准的非对称多处理 (AMP) 支持
*********************************************************************

.. module:: openamp
   :synopsis: 提供标准的非对称多处理 (AMP) 支持

``openamp`` 模块为 MicroPython 提供标准的处理器间通信基础设施。该模块处理 OpenAMP 的所有细节，例如设置共享资源表、初始化 vring 等。它通过 `Endpoint` 类提供使用 RPMsg 总线基础设施的 API，并通过 `RemoteProc` 类提供处理器生命周期管理 (LCM) 支持，例如加载固件以及启动和停止远程核心。

使用示例::

    import openamp

    def ept_recv_callback(src, data):
        print("在端点上收到消息", data)

    # 创建新的 RPMsg 端点以与远程核心通信
    ept = openamp.Endpoint("vuart-channel", callback=ept_recv_callback)

    # 创建 RemoteProc 对象，加载其固件并启动它
    rproc = openamp.RemoteProc("virtual_uart.elf") # 或入口点地址（例如 0x081E0000）
    rproc.start()

    while True:
        if ept.is_ready():
            ept.send("data")

函数
==========

.. function:: new_service_callback(ns_callback)

    设置新服务回调函数。

    *ns_callback* 参数是一个函数，当远程处理器宣布新服务时将被调用。此时，主机处理器可以选择创建宣布的端点（如果支持此特定服务），或者忽略它（如果不支持）。如果未设置此函数，主机处理器应首先在本地注册端点，当远程宣布服务时，它将被自动绑定。

Endpoint 类
==============

.. class:: Endpoint(name, callback, src=ENDPOINT_ADDR_ANY, dest=ENDPOINT_ADDR_ANY)

   构造新的 RPMsg 端点。端点是两个核心之间的双向通信通道。

   参数：

        - *name* 是端点的名称。
        - *callback* 是一个函数，当端点接收到数据时被调用，参数为远程点的源地址和作为引用传递的数据（字节）。
        - *src* 是端点源地址。如果未提供，库将为端点分配一个。
        - *dest* 是端点目标地址。如果端点是从 new_service_callback 创建的，则必须提供此参数，并且它必须与远程端点的源地址匹配。如果端点在宣布之前在本地注册，则库将在端点绑定时分配目标地址。

.. method:: Endpoint.deinit()

   销毁端点并释放其所有资源。

.. method:: Endpoint.is_ready()

   如果端点准备好发送（即同时具有源地址和目标地址），则返回 ``True``

.. method:: Endpoint.send(src=-1, dest=-1, timeout=-1)

   通过此端点向远程处理器发送消息。

   参数：

        - *src* 是消息的源端点地址。如果未提供，则使用端点绑定的源地址。
        - *dest* 是消息的目标端点地址。如果未提供，则使用端点绑定的目标地址。
        - *timeout* 指定等待空闲缓冲区的时间（以毫秒为单位）。默认情况下，该函数是阻塞的。

RemoteProc 类
==============

.. class:: RemoteProc(entry)

   RemoteProc 对象提供处理器生命周期管理 (LCM) 支持，例如加载固件以及启动和停止远程核心。

   *entry* 参数可以是固件映像的路径，在这种情况下，固件将从文件加载到其目标内存，或者是入口点地址，在这种情况下，固件必须已经加载到给定地址。

.. method:: RemoteProc.start()

   启动远程处理器。

.. method:: RemoteProc.stop()

   停止远程处理器。确切行为取决于平台。例如，在 STM32H7 上，无法停止然后重新启动 Cortex-M4 核心，因此在此函数调用时会执行完整的系统重置。

.. method:: RemoteProc.shutdown()

   关闭会停止远程处理器并释放其所有资源。确切行为取决于平台，但通常会禁用远程核心的电源和时钟。此函数也用作终结器（即，当 ``RemoteProc`` 对象被收集时调用）。请注意，在 STM32H7 上，无法停止然后重新启动 Cortex-M4 核心，因此在此函数调用时会执行完整的系统重置。