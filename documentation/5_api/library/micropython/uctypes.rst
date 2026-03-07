*********************************************************************
:mod:`uctypes` --- 以结构化方式访问二进制数据
*********************************************************************

.. module:: uctypes
   :synopsis: 以结构化方式访问二进制数据

此模块为 MicroPython 实现了"外部数据接口"。其背后的思想类似于 CPython 的 ``ctypes`` 模块，但实际 API 不同，经过简化并针对小尺寸进行了优化。该模块的基本思想是定义数据结构布局，其能力与 C 语言允许的大致相同，然后使用熟悉的点语法访问子字段。

.. warning::

    ``uctypes`` 模块允许访问机器的任意内存地址（包括 I/O 和控制寄存器）。不小心使用它可能会导致崩溃、数据丢失甚至硬件故障。

.. seealso::

    模块 :mod:`struct`
        访问二进制数据结构的标准 Python 方法（对于大型复杂结构不适用）。

使用示例::

    import uctypes

    # 示例 1：ELF 文件头的子集
    # https://wikipedia.org/wiki/Executable_and_Linkable_Format#File_header
    ELF_HEADER = {
        "EI_MAG": (0x0 | uctypes.ARRAY, 4 | uctypes.UINT8),
        "EI_DATA": 0x5 | uctypes.UINT8,
        "e_machine": 0x12 | uctypes.UINT16,
    }

    # "f" 是以二进制模式打开的 ELF 文件
    buf = f.read(uctypes.sizeof(ELF_HEADER, uctypes.LITTLE_ENDIAN))
    header = uctypes.struct(uctypes.addressof(buf), ELF_HEADER, uctypes.LITTLE_ENDIAN)
    assert header.EI_MAG == b"\x7fELF"
    assert header.EI_DATA == 1, "Oops, wrong endianness. Could retry with uctypes.BIG_ENDIAN."
    print("machine:", hex(header.e_machine))


    # 示例 2：带指针的内存数据结构
    COORD = {
        "x": 0 | uctypes.FLOAT32,
        "y": 4 | uctypes.FLOAT32,
    }

    STRUCT1 = {
        "data1": 0 | uctypes.UINT8,
        "data2": 4 | uctypes.UINT32,
        "ptr": (8 | uctypes.PTR, COORD),
    }

    # 假设你在 "addr" 中有类型为 STRUCT1 的结构的地址
    # uctypes.NATIVE 是可选的（默认使用）
    struct1 = uctypes.struct(addr, STRUCT1, uctypes.NATIVE)
    print("x:", struct1.ptr[0].x)


    # 示例 3：访问 CPU 寄存器。STM32F4xx WWDG 块的子集
    WWDG_LAYOUT = {
        "WWDG_CR": (0, {
            # 这里的 BFUINT32 表示 WWDG_CR 寄存器的大小
            "WDGA": 7 << uctypes.BF_POS | 1 << uctypes.BF_LEN | uctypes.BFUINT32,
            "T": 0 << uctypes.BF_POS | 7 << uctypes.BF_LEN | uctypes.BFUINT32,
        }),
        "WWDG_CFR": (4, {
            "EWI": 9 << uctypes.BF_POS | 1 << uctypes.BF_LEN | uctypes.BFUINT32,
            "WDGTB": 7 << uctypes.BF_POS | 2 << uctypes.BF_LEN | uctypes.BFUINT32,
            "W": 0 << uctypes.BF_POS | 7 << uctypes.BF_LEN | uctypes.BFUINT32,
        }),
    }

    WWDG = uctypes.struct(0x40002c00, WWDG_LAYOUT)

    WWDG.WWDG_CFR.WDGTB = 0b10
    WWDG.WWDG_CR.WDGA = 1
    print("Current counter:", WWDG.WWDG_CR.T)

定义结构布局
==============

结构布局由"描述符"定义 - 一个 Python 字典，将字段名称编码为键，并将访问它们所需的其他属性编码为关联值::

    {
        "field1": <properties>,
        "field2": <properties>,
        ...
    }

当前，``uctypes`` 需要为每个字段明确指定偏移量。偏移量以从结构开始的字节数给出。

以下是各种字段类型的编码示例：

* 标量类型::

    "field_name": offset | uctypes.UINT32

  换句话说，值是标量类型标识符与字段偏移量（以字节为单位）从结构开始的按位或。

* 递归结构::

    "sub": (offset, {
        "b0": 0 | uctypes.UINT8,
        "b1": 1 | uctypes.UINT8,
    })

  即值是一个 2 元组，第一个元素是偏移量，第二个是结构描述符字典（注意：递归描述符中的偏移量相对于它定义的结构）。当然，递归结构不仅可以通过字面字典指定，还可以通过名称引用（之前定义的）结构描述符字典。

* 基本类型数组::

      "arr": (offset | uctypes.ARRAY, size | uctypes.UINT8),

  即值是一个 2 元组，第一个元素是 ARRAY 标志与偏移量的按位或，第二个是标量元素类型与数组中元素数量的按位或。

* 聚合类型数组::

    "arr2": (offset | uctypes.ARRAY, size, {"b": 0 | uctypes.UINT8}),

  即值是一个 3 元组，第一个元素是 ARRAY 标志与偏移量的按位或，第二个是数组中的元素数量，第三个是元素类型的描述符。

* 指向基本类型的指针::

    "ptr": (offset | uctypes.PTR, uctypes.UINT8),

  即值是一个 2 元组，第一个元素是 PTR 标志与偏移量的按位或，第二个是标量元素类型。

* 指向聚合类型的指针::

    "ptr2": (offset | uctypes.PTR, {"b": 0 | uctypes.UINT8}),

  即值是一个 2 元组，第一个元素是 PTR 标志与偏移量的按位或，第二个是指向类型的描述符。

* 位域::

    "bitf0": offset | uctypes.BFUINT16 | lsbit << uctypes.BF_POS | bitsize << uctypes.BF_LEN,

  即值是包含给定位域的标量值的类型（类型名类似于标量类型，但前缀为 ``BF``），与包含位域的标量值的偏移量按位或，进一步与位域在位域值内的位位置和位长度的值按位或，分别由 BF_POS 和 BF_LEN 位偏移。位域位置从标量的最低有效位（位置为 0）开始计数，是字段最右边位的编号（换句话说，它是标量需要右移以提取位域的位数）。

  在上面的示例中，首先会在偏移量 0 处提取 UINT16 值（此细节在访问硬件寄存器时可能很重要，其中需要特定的访问大小和对齐），然后提取位域，其最右边的位是此 UINT16 的 *lsbit* 位，长度为 *bitsize* 位。例如，如果 *lsbit* 为 0 且 *bitsize* 为 8，则实际上它将访问 UINT16 的最低有效字节。

  请注意，位域操作与目标字节序无关，特别是，上面的示例将在小端和大端结构中访问 UINT16 的最低有效字节。但它依赖于最低有效位编号为 0。某些目标可能在其本机 ABI 中使用不同的编号，但 ``uctypes`` 始终使用上述标准化编号。

模块内容
==============

.. class:: struct(addr, descriptor, layout_type=NATIVE, /)

   基于内存中的结构地址、描述符（编码为字典）和布局类型（见下文）实例化"外部数据结构"对象。

.. data:: LITTLE_ENDIAN

   小端打包结构的布局类型。（打包意味着每个字段恰好占用描述符中定义的字节数，即对齐方式为 1）。

.. data:: BIG_ENDIAN

   大端打包结构的布局类型。

.. data:: NATIVE

   本机结构的布局类型 - 数据字节序和对齐方式符合 MicroPython 运行所在系统的 ABI。

.. function:: sizeof(struct, layout_type=NATIVE, /)

   返回数据结构的大小（以字节为单位）。*struct* 参数可以是结构类或特定的实例化结构对象（或其聚合字段）。

.. function:: addressof(obj)

   返回对象的地址。参数应该是 bytes、bytearray 或其他支持缓冲区协议的对象（实际返回的是此缓冲区的地址）。

.. function:: bytes_at(addr, size)

   捕获给定地址和大小的内存作为 bytes 对象。由于 bytes 对象是不可变的，内存实际上是复制并复制到 bytes 对象中，因此如果内存内容后来更改，创建的对象会保留原始值。

.. function:: bytearray_at(addr, size)

   捕获给定地址和大小的内存作为 bytearray 对象。与上面的 bytes_at() 函数不同，内存是通过引用捕获的，因此它可以被写入，并且您将访问给定内存地址的当前值。

.. data:: UINT8
          INT8
          UINT16
          INT16
          UINT32
          INT32
          UINT64
          INT64

   结构描述符的整数类型。提供了 8、16、32 和 64 位类型的常量，包括有符号和无符号。

.. data:: FLOAT32
          FLOAT64

   结构描述符的浮点类型。

.. data:: VOID

   ``VOID`` 是 ``UINT8`` 的别名，提供用于方便地定义 C 的 void 指针：``(uctypes.PTR, uctypes.VOID)``。

.. data:: PTR
          ARRAY

   指针和数组的类型常量。请注意，没有用于结构的显式常量，它是隐式的：没有 ``PTR`` 或 ``ARRAY`` 标志的聚合类型是结构。

结构描述符和实例化结构对象
==============================

给定结构描述符字典及其布局类型，您可以使用 :class:`uctypes.struct()` 构造函数在给定的内存地址实例化特定的结构实例。内存地址通常来自以下来源：

* 预定义地址，当在裸机系统上访问硬件寄存器时。在特定 MCU/SoC 的数据手册中查找这些地址。
* 作为对某些 FFI（外部函数接口）函数调用的返回值。
* 从 `uctypes.addressof()`，当您想向 FFI 函数传递参数时，或者作为替代方案，访问一些 I/O 数据（例如，从文件或网络套接字读取的数据）。

结构对象
==============

结构对象允许使用标准点表示法访问各个字段：``my_struct.substruct1.field1``。如果字段是标量类型，获取它将产生对应于字段中包含的值的原始值（Python 整数或浮点数）。标量字段也可以被赋值。

如果字段是数组，其各个元素可以使用标准下标运算符 ``[]`` 访问 - 既可读取也可赋值。

如果字段是指针，可以使用 ``[0]`` 语法解引用（对应于 C ``*`` 运算符，尽管 ``[0]`` 在 C 中也有效）。也支持使用 0 以外的整数值对指针进行下标操作，具有与 C 中相同的语义。

总结一下，访问结构字段通常遵循 C 语法，除了指针解引用时，您需要使用 ``[0]`` 运算符而不是 ``*``。

限制
==============

1. 访问非标量字段会导致分配中间对象来表示它们。这意味着在需要在内存分配被禁用时（例如从中断）访问的结构的布局时，应特别小心。建议是：

* 避免访问嵌套结构。例如，不要使用 ``mcu_registers.peripheral_a.register1``，而是为每个外设定义单独的布局描述符，以 ``peripheral_a.register1`` 的方式访问。或者只是缓存特定的外设：``peripheral_a = mcu_registers.peripheral_a``。如果寄存器由多个位域组成，您需要缓存对特定寄存器的引用：``reg_a = mcu_registers.peripheral_a.reg_a``。
* 避免其他非标量数据，如数组。例如，不要使用 ``peripheral_a.register[0]``，而是使用 ``peripheral_a.register0``。同样，另一种方法是缓存中间值，例如 ``register0 = peripheral_a.register[0]``。

2. ``uctypes`` 模块支持的偏移范围是有限的。支持的确切范围被视为实现细节，一般建议是将结构定义拆分为最多覆盖几千字节到几十千字节。在大多数情况下，这无论如何都是自然的情况，例如，将 MCU 的所有寄存器（分布在 32 位地址空间中）定义在一个结构中是没有意义的，而是逐个外设块定义。在一些极端情况下，您可能需要人为地将结构拆分为几个部分（例如，如果访问中间有多兆字节数组的本机数据结构，尽管这将是一个非常合成的情况）。