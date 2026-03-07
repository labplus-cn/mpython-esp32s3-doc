:mod:`bluetooth` --- 低功耗蓝牙
=========================================

.. module:: bluetooth
   :synopsis: 低功耗蓝牙无线电功能

该模块提供对板上蓝牙控制器的接口。
当前，它支持蓝牙低功耗（BLE）在中央、外围设备、广播和观察者角色，以及GATT服务器和客户端和L2CAP面向连接的通道。设备可以同时在多个角色中运行。在某些端口上支持配对（和绑定）。

此API旨在与低功耗蓝牙协议相匹配，并为更高级的抽象(如特定的设备类型)提供构建模块。

.. note:: 对于大多数应用程序，我们建议使用更高级的aioble库。

.. note:: 该模块仍在开发中，其类，功能，方法和常量可能会发生变化。


BLE 类
---------

构造函数
-----------

.. class:: BLE()

    返回单例 BLE 对象


配置
-------------

.. method:: BLE.active([active])

    （可选）更改BLE无线电的活动状态，并返回当前状态。

    在使用此类的任何其他方法之前，必须使无线电处于活动状态。

.. method:: BLE.config('param')
            BLE.config(param=value, ...)

    获取或设置BLE接口的配置值。为了获得一个值，参数名称应该用字符串引号，并且一次只查询一个参数。要设置值，请使用关键字语法，一次可以设置一个或多个参数。

    当前支持的值为:

    - ``'mac'``: 当前使用的地址，取决于当前的地址模式。这返回一个元组 (addr_type, addr)。
      有关地址类型的详细信息，请参阅 gatts_write。
      只有当接口当前处于活动状态时，才能查询此值。

    - ``'addr_mode'``: 设置地址模式。值可以是：

        - 0x00 - PUBLIC - 使用控制器的公共地址。
        - 0x01 - RANDOM - 使用生成的静态地址。
        - 0x02 - RPA - 使用可解析的私有地址。
        - 0x03 - NRPA - 使用不可解析的私有地址。

      默认情况下，如果可用，接口模式将使用PUBLIC地址，否则将使用RANDOM地址。

    - ``'gap_name'``: 获取/设置服务0x1800、特征0x2a00使用的GAP设备名称。可以随时设置并多次更改。

    - ``'rxbuf'``: 获取/设置用于存储传入事件的内部缓冲区的大小（以字节为单位）。该缓冲区是整个BLE驱动程序的全局缓冲区，因此可以处理所有事件（包括所有特征）的传入数据。增加此值可以更好地处理突发的传入数据（例如，扫描结果），并可以使中央设备接收较大的特征值。

    - ``'mtu'``: 获取/设置在ATT MTU交换期间将使用的MTU。
      生成的MTU将是此值和远程设备的MTU的最小值。
      ATT MTU交换不会自动发生（除非远程设备启动），必须使用gattc_exchange_mtu手动启动。
      使用_IRQ_MTU_EXCHANGED事件来发现给定连接的MTU。

    - ``'bond'``: 设置配对期间是否启用绑定。启用时，配对请求将设置"bond"标志，并且密钥将由两个设备存储。

    - ``'mitm'``: 设置配对是否需要MITM保护。

    - ``'io'``: 设置此设备的I/O功能。
      可用选项是：
      _IO_CAPABILITY_DISPLAY_ONLY = const(0)
      _IO_CAPABILITY_DISPLAY_YESNO = const(1)
      _IO_CAPABILITY_KEYBOARD_ONLY = const(2)
      _IO_CAPABILITY_NO_INPUT_OUTPUT = const(3)
      _IO_CAPABILITY_KEYBOARD_DISPLAY = const(4)

    - ``'le_secure'``: 设置是否需要"LE安全"配对。默认为false（即允许"传统配对"）。


事件处理
--------------

.. method:: BLE.irq(handler)

    为BLE堆栈中的事件注册回调。handler接收两个参数，``event`` （看下文的事件代码）和 ``data`` （其是值的特定事件元组）。

    注意：作为防止不必要分配的优化，元组中的addr、adv_data、char_data、notify_data和uuid条目是指向蓝牙内部环形缓冲区的只读memoryview实例，并且仅在IRQ处理程序函数的调用期间有效。
    如果您的程序需要保存这些值之一以在IRQ处理程序返回后访问（例如，通过将其保存在类实例或全局变量中），则需要复制数据，方法是使用bytes()或bluetooth.UUID()，如下所示：
    connected_addr = bytes(addr)  # 等效于：adv_data, char_data, 或 notify_data
    matched_uuid = bluetooth.UUID(uuid)

    例如，扫描结果的IRQ处理程序可能会检查adv_data以确定它是否是正确的设备，然后才复制地址数据以在程序的其他地方使用。
    要在IRQ处理程序中打印数据，需要使用print(bytes(addr))。

    一个事件处理程序显示所有可能的事件::

        def bt_irq(event, data):
            if event == _IRQ_CENTRAL_CONNECT:
                # 中央设备已经连接到这个外围设备
                conn_handle, addr_type, addr = data
            elif event == _IRQ_CENTRAL_DISCONNECT:
                # 中央设备已与此外围设备断开
                conn_handle, addr_type, addr = data
            elif event == _IRQ_GATTS_WRITE:
                # 客户端已写入此特征或描述符
                conn_handle, attr_handle = data
            elif event == _IRQ_GATTS_READ_REQUEST:
                # 客户端已发出读取请求。注意：这仅在STM32上支持。
                # 返回非零整数以拒绝读取（见下文），或返回零（或None）以接受读取。
                conn_handle, attr_handle = data
            elif event == _IRQ_SCAN_RESULT:
                # 一次扫描的结果
                addr_type, addr, adv_type, rssi, adv_data = data
            elif event == _IRQ_SCAN_DONE:
                # 扫描持续时间已完成或手动停止
                pass
            elif event == _IRQ_PERIPHERAL_CONNECT:
                # gap_connect()连接成功
                conn_handle, addr_type, addr = data
            elif event == _IRQ_PERIPHERAL_DISCONNECT:
                # 已连接的外围设备已断开
                conn_handle, addr_type, addr = data
            elif event == _IRQ_GATTC_SERVICE_RESULT:
                # 调用gattc_discover_services()找到的每个服务
                conn_handle, start_handle, end_handle, uuid = data
            elif event == _IRQ_GATTC_SERVICE_DONE:
                # 服务发现完成后调用
                # 注意：状态在成功时为零，否则为实现特定的值
                conn_handle, status = data
            elif event == _IRQ_GATTC_CHARACTERISTIC_RESULT:
                # 调用gattc_discover_services()找到的每个特征
                conn_handle, end_handle, value_handle, properties, uuid = data
            elif event == _IRQ_GATTC_CHARACTERISTIC_DONE:
                # 服务发现完成后调用
                # 注意：状态在成功时为零，否则为实现特定的值
                conn_handle, status = data
            elif event == _IRQ_GATTC_DESCRIPTOR_RESULT:
                # 调用gattc_discover_descriptors()找到的每个描述符
                conn_handle, dsc_handle, uuid = data
            elif event == _IRQ_GATTC_DESCRIPTOR_DONE:
                # 服务发现完成后调用
                # 注意：状态在成功时为零，否则为实现特定的值
                conn_handle, status = data
            elif event == _IRQ_GATTC_READ_RESULT:
                # gattc_read() 已完成
                conn_handle, value_handle, char_data = data
            elif event == _IRQ_GATTC_READ_DONE:
                # gattc_read() 已完成
                # 注意：状态在成功时为零，否则为实现特定的值
                conn_handle, value_handle, status = data
            elif event == _IRQ_GATTC_WRITE_DONE:
                # gattc_write() 已完成
                # 注意：状态在成功时为零，否则为实现特定的值
                conn_handle, value_handle, status = data
            elif event == _IRQ_GATTC_NOTIFY:
                # 服务器已发送通知请求
                conn_handle, value_handle, notify_data = data
            elif event == _IRQ_GATTC_INDICATE:
                # 服务器已发送指示请求
                conn_handle, value_handle, notify_data = data
            elif event == _IRQ_GATTS_INDICATE_DONE:
                # 客户端已确认指示
                # 注意：状态在成功确认时为零，否则为实现特定的值
                conn_handle, value_handle, status = data
            elif event == _IRQ_MTU_EXCHANGED:
                # ATT MTU交换完成（由我们或远程设备发起）
                conn_handle, mtu = data
            elif event == _IRQ_L2CAP_ACCEPT:
                # 已接受新通道
                # 返回非零整数以拒绝连接，或返回零（或None）以接受
                conn_handle, cid, psm, our_mtu, peer_mtu = data
            elif event == _IRQ_L2CAP_CONNECT:
                # 新通道现已连接（作为连接或接受的结果）
                conn_handle, cid, psm, our_mtu, peer_mtu = data
            elif event == _IRQ_L2CAP_DISCONNECT:
                # 现有通道已断开（状态为零），或连接尝试失败（状态非零）
                conn_handle, cid, psm, status = data
            elif event == _IRQ_L2CAP_RECV:
                # 通道上有新数据可用。使用l2cap_recvinto读取。
                conn_handle, cid = data
            elif event == _IRQ_L2CAP_SEND_READY:
                # 先前返回False的l2cap_send现在已完成，通道已准备好再次发送
                # 如果状态非零，则传输缓冲区溢出，应用程序应重新发送数据
                conn_handle, cid, status = data
            elif event == _IRQ_CONNECTION_UPDATE:
                # 远程设备已更新连接参数
                conn_handle, conn_interval, conn_latency, supervision_timeout, status = data
            elif event == _IRQ_ENCRYPTION_UPDATE:
                # 加密状态已更改（可能是配对或绑定的结果）
                conn_handle, encrypted, authenticated, bonded, key_size = data
            elif event == _IRQ_GET_SECRET:
                # 返回存储的密钥
                # 如果key为None，则返回此sec_type的第index个值
                # 否则返回此sec_type和key的对应值
                sec_type, index, key = data
                return value
            elif event == _IRQ_SET_SECRET:
                # 将密钥保存到为此sec_type和key的存储
                sec_type, key, value = data
                return True
            elif event == _IRQ_PASSKEY_ACTION:
                # 在配对期间响应密码请求
                # 有关详细信息，请参阅gap_passkey()
                # action将是与配置的"io"兼容的操作
                # 如果action是"numeric comparison"，则passkey将非零
                conn_handle, action, passkey = data


事件代码::

    from micropython import const
    _IRQ_CENTRAL_CONNECT = const(1)
    _IRQ_CENTRAL_DISCONNECT = const(2)
    _IRQ_GATTS_WRITE = const(3)
    _IRQ_GATTS_READ_REQUEST = const(4)
    _IRQ_SCAN_RESULT = const(5)
    _IRQ_SCAN_DONE = const(6)
    _IRQ_PERIPHERAL_CONNECT = const(7)
    _IRQ_PERIPHERAL_DISCONNECT = const(8)
    _IRQ_GATTC_SERVICE_RESULT = const(9)
    _IRQ_GATTC_SERVICE_DONE = const(10)
    _IRQ_GATTC_CHARACTERISTIC_RESULT = const(11)
    _IRQ_GATTC_CHARACTERISTIC_DONE = const(12)
    _IRQ_GATTC_DESCRIPTOR_RESULT = const(13)
    _IRQ_GATTC_DESCRIPTOR_DONE = const(14)
    _IRQ_GATTC_READ_RESULT = const(15)
    _IRQ_GATTC_READ_DONE = const(16)
    _IRQ_GATTC_WRITE_DONE = const(17)
    _IRQ_GATTC_NOTIFY = const(18)
    _IRQ_GATTC_INDICATE = const(19)
    _IRQ_GATTS_INDICATE_DONE = const(20)
    _IRQ_MTU_EXCHANGED = const(21)
    _IRQ_L2CAP_ACCEPT = const(22)
    _IRQ_L2CAP_CONNECT = const(23)
    _IRQ_L2CAP_DISCONNECT = const(24)
    _IRQ_L2CAP_RECV = const(25)
    _IRQ_L2CAP_SEND_READY = const(26)
    _IRQ_CONNECTION_UPDATE = const(27)
    _IRQ_ENCRYPTION_UPDATE = const(28)
    _IRQ_GET_SECRET = const(29)
    _IRQ_SET_SECRET = const(30)

对于_IRQ_GATTS_READ_REQUEST事件，可用的返回代码是：
    _GATTS_NO_ERROR = const(0x00)
    _GATTS_ERROR_READ_NOT_PERMITTED = const(0x02)
    _GATTS_ERROR_WRITE_NOT_PERMITTED = const(0x03)
    _GATTS_ERROR_INSUFFICIENT_AUTHENTICATION = const(0x05)
    _GATTS_ERROR_INSUFFICIENT_AUTHORIZATION = const(0x08)
    _GATTS_ERROR_INSUFFICIENT_ENCRYPTION = const(0x0f)

对于_IRQ_PASSKEY_ACTION事件，可用的操作是：
    _PASSKEY_ACTION_NONE = const(0)
    _PASSKEY_ACTION_INPUT = const(2)
    _PASSKEY_ACTION_DISPLAY = const(3)
    _PASSKEY_ACTION_NUMERIC_COMPARISON = const(4)

为了节省固件中的空间，这些常量不包括在 :mod:`bluetooth` 。将您需要的从上面的列表中添加到您的程序中。


广播者角色 (Advertiser)
-----------------------------

.. method:: BLE.gap_advertise(interval_us, adv_data=None, *, resp_data=None, connectable=True)

    以指定的时间间隔（以微秒为单位）开始广播。该间隔将向下舍入到最接近的625微秒。要停止广播，请将 `interval_us` 设置 为None。

    *adv_data* 和 *resp_data* 可以是任何实现缓冲区协议的类型（例如 ``bytes``, ``bytearray``, ``str``）。
    *adv_data* 包含在所有广播中，并发送 *resp_data* 以应答有效的扫描。

    注意：如果 *adv_data* （或 *resp_data* ）为None，则将重用传递到上一个调用的数据 ``gap_advertise`` 。
    这样一来，广播者就可以使用来恢复广播 ``gap_advertise(interval_us)`` 。为了清除广播负载，传递一个空的bytes，即b''。


观察者角色 (Scanner)
-----------------------

.. method:: BLE.gap_scan(duration_ms, interval_us=1280000, window_us=11250, active=False)

    运行持续指定时间（以毫秒为单位）的扫描操作。

    要无限期扫描，请将 *duration_ms* 设置为 ``0`` 。
    要停止扫描，请将 *duration_ms* 设置为 ``None`` 。
    
    使用 *interval_us* 和 *window_us* 可以选择配置占空比。
    扫描器将每间隔一微秒运行一次 *window_us* 微秒，总计持续时间为毫秒。默认间隔和窗口分别为1.28秒和11.25毫秒（后台扫描）。

    对于每个扫描结果，*_IRQ_SCAN_RESULT* 将引发该事件，事件数据为 (addr_type, addr, adv_type, rssi, adv_data)。

    addr_type值表示公共或随机地址：
    0x00 - PUBLIC
    0x01 - RANDOM（静态、RPA或NRPA，类型编码在地址本身中）

    adv_type值对应于蓝牙规范：
    0x00 - ADV_IND - 可连接和可扫描的无向广播
    0x01 - ADV_DIRECT_IND - 可连接的定向广播
    0x02 - ADV_SCAN_IND - 可扫描的无向广播
    0x03 - ADV_NONCONN_IND - 不可连接的无向广播
    0x04 - SCAN_RSP - 扫描响应

    如果您希望在结果中接收扫描响应，可以将active设置为True。

    停止扫描（由于持续时间结束或明确停止）时，*_IRQ_SCAN_DONE* 将引发该事件。


中央角色
------------
中央设备可以连接到使用观察者角色（见gap_scan）发现的或具有已知地址的外围设备。

.. method:: BLE.gap_connect(addr_type, addr, scan_duration_ms=2000, min_conn_interval_us=None, max_conn_interval_us=None)

    连接到外围设备。
    有关地址类型的详细信息，请参阅gap_scan。
    要提前取消未完成的连接尝试，请调用gap_connect(None)。
    成功时，将引发_IRQ_PERIPHERAL_CONNECT事件。如果取消连接尝试，将引发_IRQ_PERIPHERAL_DISCONNECT事件。
    设备将等待最多scan_duration_ms以接收来自设备的广播负载。
    可以使用min_conn_interval_us和max_conn_interval_us中的一个或两个以微秒为单位配置连接间隔。否则将选择默认间隔，通常在30000到50000微秒之间。较短的间隔会增加吞吐量，但会增加功耗。


外围角色
----------
外围设备应发送可连接的广播（见gap_advertise）。它通常会作为GATT服务器，首先使用gatts_register_services注册服务和特征。
当中央连接时，将引发_IRQ_CENTRAL_CONNECT事件。


中央和外围角色
----------------

.. method:: BLE.gap_disconnect(conn_handle)

    断开指定的连接句柄。这可以是连接到此设备的中央（如果充当外围设备）或此设备先前连接的外围设备（如果充当中央）。
    成功时，将引发_IRQ_PERIPHERAL_DISCONNECT或_IRQ_CENTRAL_DISCONNECT事件。
    如果连接句柄未连接，返回 ``False`` ,否则返回 ``True`` 。


GATT 服务器
-------------
GATT服务器具有一组注册服务。每个服务可能包含特性，每个特性都有一个值。特征也可以包含描述符，描述符本身具有值。
这些值存储在本地，并通过在服务注册过程中生成的“值柄”进行访问。它们也可以被远程客户端设备读取或写入。此外，服务器可以通过连接句柄向连接的客户端“通知”特征。
中央或外围角色的设备都可以充当GATT服务器，但在大多数情况下，外围设备充当服务器更为常见。
特征和描述符的默认最大大小为20个字节。客户端写入它们的任何内容都会被截断到这个长度。但是，任何本地写入都会增加最大大小，因此如果您希望允许客户端对给定特征进行更大的写入，请在注册后使用gatts_write。例如，gatts_write(char_handle, bytes(100))。

.. method:: BLE.gatts_register_services(services_definition)

    使用指定的服务配置服务器，替换所有现有服务。

    *services_definition* 是一个服务的列表，其中每个服务都是一个包含UUID和特征列表的二元元组。

    每个特征都是一个包含 `UUID`，`flags` 值以及一个可选的描述符列表的2或3元素元组。

    每个描述符是一个包含UUID和一个flags值的二元元组。

    这些标志是下面定义的标志的按位或组合。这些设置特征（或描述符）的行为以及安全和隐私要求。

    返回值是元组的列表（每个服务一个元素）（每个元素是一个值句柄）。特征和描述符句柄按照定义的顺序被展平到相同的元组中。

    以下示例注册了两个服务 (Heart Rate, and Nordic UART)::

        HR_UUID = bluetooth.UUID(0x180D)
        HR_CHAR = (bluetooth.UUID(0x2A37), bluetooth.FLAG_READ | bluetooth.FLAG_NOTIFY,)
        HR_SERVICE = (HR_UUID, (HR_CHAR,),)
        UART_UUID = bluetooth.UUID('6E400001-B5A3-F393-E0A9-E50E24DCCA9E')
        UART_TX = (bluetooth.UUID('6E400003-B5A3-F393-E0A9-E50E24DCCA9E'), bluetooth.FLAG_READ | bluetooth.FLAG_NOTIFY,)
        UART_RX = (bluetooth.UUID('6E400002-B5A3-F393-E0A9-E50E24DCCA9E'), bluetooth.FLAG_WRITE,)
        UART_SERVICE = (UART_UUID, (UART_TX, UART_RX,),)
        SERVICES = (HR_SERVICE, UART_SERVICE,)
        ( (hr,), (tx, rx,), ) = bt.gatts_register_services(SERVICES)

    这三个值柄(``hr``, ``tx``, ``rx``)可与使用 :meth:`gatts_read <BLE.gatts_read>`, :meth:`gatts_write <BLE.gatts_write>`, :meth:`gatts_notify <BLE.gatts_notify>`, 和 :meth:`gatts_indicate <BLE.gatts_indicate>` 。

    注意：注册服务之前，必须停止广告。

    特征和描述符的可用标志是：
    from micropython import const
    _FLAG_BROADCAST = const(0x0001)
    _FLAG_READ = const(0x0002)
    _FLAG_WRITE_NO_RESPONSE = const(0x0004)
    _FLAG_WRITE = const(0x0008)
    _FLAG_NOTIFY = const(0x0010)
    _FLAG_INDICATE = const(0x0020)
    _FLAG_AUTHENTICATED_SIGNED_WRITE = const(0x0040)

    _FLAG_AUX_WRITE = const(0x0100)
    _FLAG_READ_ENCRYPTED = const(0x0200)
    _FLAG_READ_AUTHENTICATED = const(0x0400)
    _FLAG_READ_AUTHORIZED = const(0x0800)
    _FLAG_WRITE_ENCRYPTED = const(0x1000)
    _FLAG_WRITE_AUTHENTICATED = const(0x2000)
    _FLAG_WRITE_AUTHORIZED = const(0x4000)

    至于上面的IRQ，任何需要的常量都应该添加到您的Python代码中。

.. method:: BLE.gatts_read(value_handle)

    读取此句柄的本地值（由gatts_write或远程客户端写入）。

.. method:: BLE.gatts_write(value_handle, data, send_update=False)

    写入此句柄的本地值，客户端可以读取。
    如果send_update为True，则任何订阅的客户端将收到通知（或指示，取决于它们订阅的内容和特征支持的操作）。

.. method:: BLE.gatts_notify(conn_handle, value_handle, data=None)

    向连接的客户端发送通知请求。
    如果data为None（默认值），则将发送当前本地值（由gatts_write设置）。
    否则，如果data不为None，则该值将作为通知的一部分发送给客户端。本地值不会被修改。
    注意：无论客户端对此特征的订阅状态如何，都会发送通知。

.. method:: BLE.gatts_indicate(conn_handle, value_handle, data=None)

    向连接的客户端发送指示请求。
    如果data为None（默认值），则将发送当前本地值（由gatts_write设置）。
    否则，如果data不为None，则该值将作为指示的一部分发送给客户端。本地值不会被修改。
    确认（或失败，例如超时）时，将引发_IRQ_GATTS_INDICATE_DONE事件。
    注意：无论客户端对此特征的订阅状态如何，都会发送指示。

.. method:: BLE.gatts_set_buffer(value_handle, len, append=False)

    设置值的内部缓冲区大小（以字节为单位）。这将限制可以接收的最大写入。默认值为20。
    将 ``append`` 设置为 `True` 会将所有远程写入追加到当前值，而不是替换当前值。这样最多可以缓冲len个字节。
    使用时 :meth:`gatts_read <BLE.gatts_read>` ，将在读取后清除该值。这个功能在实现某些东西时很有用,比如Nordic UART服务。


GATT 客户端
--------------
GATT客户端可以发现并读取/写入远程GATT服务器上的特征。
中央角色设备充当GATT客户端更为常见，但外围设备也可能充当客户端，以发现有关已连接到它的中央的信息（例如，从设备信息服务读取设备名称）。

.. method:: BLE.gattc_discover_services(conn_handle, uuid=None)

    查询连接的服务器的服务。
    可选地指定服务uuid以仅查询该服务。
    对于发现的每个服务，将引发_IRQ_GATTC_SERVICE_RESULT事件，完成后引发_IRQ_GATTC_SERVICE_DONE。

.. method:: BLE.gattc_discover_characteristics(conn_handle, start_handle, end_handle, uuid=None)

    查询连接的服务器在指定范围内的特征。
    可选地指定特征uuid以仅查询该特征。
    您可以使用start_handle=1, end_handle=0xffff在任何服务中搜索特征。
    对于发现的每个特征，将引发_IRQ_GATTC_CHARACTERISTIC_RESULT事件，完成后引发_IRQ_GATTC_CHARACTERISTIC_DONE。

.. method:: BLE.gattc_discover_descriptors(conn_handle, start_handle, end_handle)

    查询连接的服务器在指定范围内的描述符。
    对于发现的每个描述符，将引发_IRQ_GATTC_DESCRIPTOR_RESULT事件，完成后引发_IRQ_GATTC_DESCRIPTOR_DONE。

.. method:: BLE.gattc_read(conn_handle, value_handle)

    向连接的服务器发出远程读取，以获取指定的特性或描述符句柄。
    当值可用时，将引发_IRQ_GATTC_READ_RESULT事件。此外，将引发_IRQ_GATTC_READ_DONE。

.. method:: BLE.gattc_write(conn_handle, value_handle, data, mode=0)

    针对指定的特征或描述符句柄向连接的服务器发出远程写操作。
    参数mode指定写入行为，当前支持的值为：

    - mode=0（默认）是无响应写操作：写操作将发送到远程服务器，但不会返回确认，也不会引发任何事件。
    - mode=1是响应写入：请求远程服务器发送其已接收到数据的响应/确认。

    如果从远程服务器收到响应，将引发_IRQ_GATTC_WRITE_DONE事件。

.. method:: BLE.gattc_exchange_mtu(conn_handle)

    使用通过BLE.config(mtu=value)设置的首选MTU启动与连接服务器的MTU交换。
    MTU交换完成时将引发_IRQ_MTU_EXCHANGED事件。
    注意：MTU交换通常由中央启动。在中央角色中使用BlueKitchen堆栈时，它不支持远程外围设备启动MTU交换。NimBLE适用于两种角色。


L2CAP 面向连接的通道
--------------------------

此功能允许在两个BLE设备之间进行类似套接字的数据交换。
一旦设备通过GAP连接，任一设备都可以监听另一个设备在数字PSM（协议/服务多路复用器）上的连接。
注意：目前仅在STM32和Unix上使用NimBLE堆栈时支持（不支持ESP32）。在给定时间只能有一个L2CAP通道处于活动状态（即，您不能在监听时连接）。
活动的L2CAP通道由它们建立的连接句柄和CID（通道ID）标识。
面向连接的通道具有内置的基于信用的流量控制。与ATT不同，设备协商共享MTU，监听和连接设备各自设置独立的MTU，这限制了远程设备在l2cap_recvinto中完全消耗之前可以发送的最大未完成数据量。

.. method:: BLE.l2cap_listen(psm, mtu)

    开始在指定的psm上监听传入的L2CAP通道请求，本地MTU设置为mtu。
    当远程设备启动连接时，将引发_IRQ_L2CAP_ACCEPT事件，这使监听服务器有机会拒绝传入的连接（通过返回非零整数）。
    一旦连接被接受，将引发_IRQ_L2CAP_CONNECT事件，允许服务器获取通道ID（CID）以及本地和远程MTU。
    注意：当前无法停止监听。

.. method:: BLE.l2cap_connect(conn_handle, psm, mtu)

    连接到指定psm上的监听对等方，本地MTU设置为mtu。
    成功连接后，将引发_IRQ_L2CAP_CONNECT事件，允许客户端获取CID以及本地和远程（对等方）MTU。
    不成功的连接将引发状态非零的_IRQ_L2CAP_DISCONNECT事件。

.. method:: BLE.l2cap_disconnect(conn_handle, cid)

    断开具有指定conn_handle和cid的活动L2CAP通道。

.. method:: BLE.l2cap_send(conn_handle, cid, buf)

    在由conn_handle和cid标识的L2CAP通道上发送指定的buf（必须支持缓冲区协议）。
    指定的缓冲区不能大于远程（对等方）MTU，且不超过本地MTU的两倍。
    如果通道现在"停滞"，这将返回False，这意味着在收到_IRQ_L2CAP_SEND_READY事件之前不得再次调用l2cap_send（这将在远程设备授予更多信用时发生，通常在它接收并处理数据之后）。

.. method:: BLE.l2cap_recvinto(conn_handle, cid, buf)

    从指定的conn_handle和cid接收数据到提供的buf（必须支持缓冲区协议，例如bytearray或memoryview）。
    返回从通道读取的字节数。
    如果buf为None，则返回可用字节数。
    注意：收到_IRQ_L2CAP_RECV事件后，应用程序应继续调用l2cap_recvinto，直到接收缓冲区中没有更多字节可用（通常最多为远程（对等方）MTU的大小）。
    直到接收缓冲区为空，远程设备才会获得更多通道信用，并且将无法发送任何更多数据。


配对和绑定
---------------

配对允许通过交换密钥（通过密码认证进行可选的MITM保护）来加密和认证连接。
绑定是将这些密钥存储到非易失性存储中的过程。
绑定后，设备能够基于存储的身份解析密钥（IRK）从另一设备解析可解析的私有地址（RPA）。
要支持绑定，应用程序必须实现_IRQ_GET_SECRET和_IRQ_SET_SECRET事件。
注意：目前仅在ESP32、STM32和Unix上使用NimBLE堆栈时支持。

.. method:: BLE.gap_pair(conn_handle)

    启动与远程设备的配对。
    调用此之前，确保设置了io、mitm、le_secure和bond配置选项（通过config）。
    成功配对后，将引发_IRQ_ENCRYPTION_UPDATE事件。

.. method:: BLE.gap_passkey(conn_handle, action, passkey)

    响应指定conn_handle和action的_IRQ_PASSKEY_ACTION事件。
    passkey是一个数值，取决于action（这将取决于设置了什么I/O能力）：

    - 当action是_PASSKEY_ACTION_INPUT时，应用程序应提示用户输入显示在远程设备上的密码。
    - 当action是_PASSKEY_ACTION_DISPLAY时，应用程序应生成随机的6位密码并显示给用户。
    - 当action是_PASSKEY_ACTION_NUMERIC_COMPARISON时，应用程序应显示_IRQ_PASSKEY_ACTION事件中提供的密码，然后响应0（取消配对）或1（接受配对）。


UUID 类
----------

构造函数
-----------

.. class:: UUID(value)

    用指定的值创建一个UUID实例。

    该值可以是：

    - 一个16位整数。例如 ``0x2908``.
    - 具有缓冲区协议且长度为2、4或16字节的对象，例如b'\x08\x29'。
    - 128位UUID字符串。例如 ``'6E400001-B5A3-F393-E0A9-E50E24DCCA9E'``.
