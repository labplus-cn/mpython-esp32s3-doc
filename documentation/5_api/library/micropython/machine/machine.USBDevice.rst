`machine.USBDevice` --- USB设备驱动
====================================================

.. note::

    machine.USBDevice目前仅支持esp32、rp2和samd端口。还需要原生USB支持，并非所有板都支持原生USB。

USBDevice提供了一个低级Python API，用于使用Python代码实现USB设备功能。

.. warning::

    这个低级API假设您熟悉USB标准。在micropython-lib中有高级usb驱动模块，它们提供了更简单的接口和更多内置功能。

术语
----

“运行时”USB设备接口或驱动程序是在MicroPython最初启动后使用此Python API定义的接口或驱动程序。
“内置”USB设备接口或驱动程序是编译到MicroPython固件中的接口或驱动程序，始终可用。例如，通常默认启用的USB-CDC（串行端口）。内置USB-MSC（大容量存储）是某些端口的选项。

生命周期
--------

管理运行时USB接口可能很棘手，特别是如果您通过作为同一USB设备一部分的内置USB-CDC串行端口与MicroPython通信。

MicroPython软重置将始终清除所有运行时USB接口，这会导致整个USB设备与主机断开连接。如果MicroPython还提供内置USB-CDC串行端口，那么在软重置后它会重新出现。

这意味着一些针对USB-CDC串行端口的功能（如mpremote run）如果运行时USB接口处于活动状态，会立即失败，因为当mpremote触发软重置时，端口会消失。操作应该在第二次尝试时成功，因为软重置后不再有运行时USB接口。

要在每次启动时配置运行时USB设备，建议将配置代码放在设备VFS上的boot.py文件中。在每次重置时，此文件在USB子系统初始化之前（在main.py之前）执行，因此它允许板立即启动运行时USB设备。

对于开发或调试，连接硬件串行REPL并完全禁用内置USB-CDC串行端口可能会很方便。并非所有端口都支持此功能（目前只有rp2）。自定义构建应配置为#define MICROPY_HW_USB_CDC (0)和#define MICROPY_HW_ENABLE_UART_REPL (1)。

.. currentmodule:: machine

.. class:: USBDevice

    构造一个USBDevice对象。

    .. note::

        此对象是单例，每次调用此构造函数都返回相同的对象引用。

    .. method:: config(desc_dev, desc_cfg, desc_strs=None, open_itf_cb=None, reset_cb=None, control_xfer_cb=None, xfer_cb=None)

        配置USBDevice单例对象，设置USB运行时设备状态和回调函数：

        - *desc_dev* - 包含新USB设备描述符的类字节对象。
        - *desc_cfg* - 包含新USB配置描述符的类字节对象。
        - *desc_strs* - 可选对象，包含USB字符串描述符值的字符串或字节对象。可以是列表、字典或任何支持整数键下标索引的对象（USB字符串描述符索引）。
          字符串是可选的USB功能，如果设备和配置描述符中未引用任何字符串，或者如果只应使用内置字符串，则可以不设置此参数（默认）。
          除了索引0外，所有字符串值都应该是纯ASCII。索引0是特殊的“语言”USB描述符，由USB标准中定义的自定义格式的字节对象表示。为了使用默认的“英语”语言描述符，可以在索引0处返回None。
          要回退到为给定索引提供内置字符串值，下标查找可以返回None、引发KeyError或引发IndexError。
        - *open_itf_cb* - 此回调在响应USB主机的Set Configuration请求时为每个接口或接口关联描述符调用一次（USB设备对主机可用之前的最后阶段）。
          回调接受一个参数，该参数是主机接受的接口或IAD描述符的memoryview（包括所有关联的描述符）。它是提供给此函数作为单独参数的同一desc_cfg对象的视图。memoryview仅在回调函数返回之前有效。
        - *reset_cb* - 当USB主机执行总线重置时调用此回调。回调不接受任何参数。任何进行中的传输都不会完成。USB主机很可能会通过调用描述符回调然后调用open_itf_cb()来重新枚举USB设备。
        - *control_xfer_cb* - 对于每个USB控制传输（设备端点0），此回调被调用一次或多次。它接受两个参数。
          第一个参数是控制传输阶段。它是以下之一：
          1表示SETUP阶段。
          2表示DATA阶段。
          3表示ACK阶段。
          第二个参数是memoryview，用于读取此阶段的USB控制请求数据。memoryview仅在回调函数返回之前有效。在单个传输的三个阶段中，此memoryview中的数据将保持相同。
          成功传输包括此回调按顺序为三个阶段调用。一般来说，如果设备想要响应控制请求做某事，最好等到ACK阶段以确认主机控制器已按预期完成传输。
          回调应返回以下值之一：
          False以暂停端点并拒绝传输。它不会继续到任何剩余阶段。
          True以继续传输到下一阶段。
          当传输将发送或接收额外数据时，可以在SETUP阶段返回缓冲区对象。通常，当请求中的wLength字段具有非零值时就是这种情况。对于OUT方向传输，这应该是可写缓冲区；对于IN方向传输，这应该是带有数据的可读缓冲区。
        - *xfer_cb* - 每当通过调用USBDevice.submit_xfer()提交的非控制传输完成时，调用此回调。
          回调有三个参数：
          完成传输的端点号。
          结果值：如果传输成功则为True，否则为False。
          成功传输的字节数。在“短”传输的情况下，结果为True，xferred_bytes将小于为传输提交的缓冲区长度。

        .. note::

            如果发生总线重置（参见USBDevice.reset()），xfer_cb不会为任何尚未完成的传输调用。

    .. method:: active([value])

        返回此运行时USB设备的当前活动状态作为布尔值。当运行时USB设备可用于与主机交互时，它是“活动的”，这并不意味着USB主机实际存在。
        如果可选的value参数设置为真值，则USB设备将被激活。
        如果可选的value参数设置为假值，则USB设备被停用。当USB设备停用时，USB主机不会检测到它。
        要模拟USB设备的断开和重新连接，请调用active(False)，然后调用active(True)。如果运行时设备配置已更改，这可能是必要的，以便主机看到新设备。

    .. attribute:: builtin_driver

        此属性保存当前内置驱动程序配置，必须设置为在此对象上定义的USBDevice.BUILTIN_命名常量之一。
        默认情况下，它保存值USBDevice.BUILTIN_NONE。
        设置此字段时，运行时USB设备必须处于非活动状态。必要时调用USBDevice.active()函数以在设置前停用（并在设置后再次激活）。
        如果此值设置为除USBDevice.BUILTIN_NONE之外的任何值，则对USBDevice.config()参数有以下限制：

        - desc_cfg应以可通过USBDevice.builtin_driver属性desc_cfg访问的内置USB接口描述符数据开头。
        - 附加到内置配置描述符后的描述符应使用从USBDevice.builtin_driver属性itf_max、str_max和ep_max中定义的最大内置值开始的接口、字符串和端点编号。
        - 如果任何新接口附加到desc_cfg的末尾，内置配置描述符中的bNumInterfaces字段也需要更新。
        - desc_strs应该是None或列表/字典，其中小于USBDevice.builtin_driver.str_max的索引值缺失或值为None。这为内置驱动程序保留了这些字符串索引。在这些索引中的任何一个处放置不同的字符串会覆盖内置驱动程序中的该字符串。

    .. method:: remote_wakeup()

        如果我们处于挂起模式且主机启用了REMOTE_WAKEUP功能，则唤醒主机。这必须在USB属性中启用，并且在主机上启用。如果远程唤醒已启用且活动且主机已被唤醒，则返回True。

    .. method:: submit_xfer(ep, buffer)

        在端点号ep上提交USB传输。buffer必须是实现缓冲区接口的对象，对于IN端点具有读访问权限，对于OUT端点具有写访问权限。

        .. note::

            ep不能是控制端点号0。控制传输是通过连续执行control_xfer_cb构建的，见上文。

        如果成功返回True，如果传输无法排队（因为USB设备未由主机配置，或因为在此端点上排队了另一个传输）则返回False。
        当USB主机完成传输时，调用xfer_cb回调（见上文）。
        如果USB设备未活动，则引发OSError，原因为MP_EINVAL。

    .. method:: stall(ep, [stall])

        调用此函数获取或设置设备端点的STALL状态。
        ep是端点的编号。
        如果设置了可选的stall参数，这是STALL状态的布尔标志。
        返回值是端点的当前stall状态（在由此函数进行任何更改之前）。
        设置为STALL的端点可能会保持暂停状态，直到再次调用此函数，或者STALL可能会被USB主机自动清除。
        如果USB设备未活动，则引发OSError，原因为MP_EINVAL。

    .. data:: BUILTIN_NONE
    .. data:: BUILTIN_DEFAULT
    .. data:: BUILTIN_CDC
    .. data:: BUILTIN_MSC
    .. data:: BUILTIN_CDC_MSC

        这些常量对象保存编译到MicroPython固件中的内置描述符数据。USBDevice.BUILTIN_NONE和USBDevice.BUILTIN_DEFAULT始终存在。根据固件构建配置和实际内置驱动程序，可能会存在其他对象。

        .. note::

            目前，USBDevice.BUILTIN_CDC、USBDevice.BUILTIN_MSC和USBDevice.BUILTIN_CDC_MSC中最多只有一个被定义，并且将与USBDevice.BUILTIN_DEFAULT是同一个对象。
            定义这些常量是为了允许运行时检测内置驱动程序（如果有）。将来可能会添加对选择多个内置驱动程序配置之一的支持。

        这些值被分配给USBDevice.builtin_driver以获取/设置内置配置。
        每个对象包含以下只读字段：

        - itf_max - 比内置配置描述符中使用的最高bInterfaceNumber值大1。
        - ep_max - 比内置配置描述符中使用的最高bEndpointAddress值大1。不包括任何IN标志位（0x80）。
        - str_max - 比任何内置描述符使用的最高字符串描述符索引值大1。
        - desc_dev - 包含内置USB设备描述符的bytes对象。
        - desc_cfg - 包含完整内置USB配置描述符的bytes对象。