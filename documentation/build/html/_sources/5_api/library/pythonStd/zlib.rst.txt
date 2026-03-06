:mod:`zlib` -- zlib解压缩
==================================

.. module:: zlib
   :synopsis: zlib decompression

这个模块实现了相应 :term:`CPython` 模块的一个子集，如下所述。有关更多信息，请参阅原始CPython文档: `zlib <https://docs.python.org/3.5/library/zlib.html#module-zlib>`_

该模块允许使用DEFLATE算法（常用于zlib库和gzip压缩程式）对二进制数据进行压缩和解压缩。

.. note::

   建议使用 deflate.DeflateIO 而不是此模块中的函数，因为它提供了压缩和解压缩的流式接口，在处理从文件、套接字或流读取或写入压缩数据时更方便且内存效率更高。

可用性：

从MicroPython v1.21开始，此模块可能不会默认存在于所有MicroPython固件中，因为它重复了deflate模块中可用的功能。
可以从micropython-lib（源）安装（或冻结）此模块的副本。
有关更多信息，请参阅包管理。本文档描述了该模块。
需要内置的deflate模块（自MicroPython v1.21起可用）
只有在内置deflate模块中启用了压缩支持时，才会提供压缩支持。

函数
---------

.. function:: decompress(data, wbits=15, /)

   将数据解压缩为bytes对象。
   wbits参数的工作方式与zlib.compress()相同，具有以下额外的有效值：

   - 0: 自动从zlib头部确定窗口大小（数据必须是zlib格式）。
   - 35到47: 自动检测zlib或gzip格式。

   与zlib.compress()一样，请参阅CPython文档中有关zlib的更多信息，了解wbits参数。与zlib.compress()一样，MicroPython也支持比CPython更小的窗口大小。有关更多MicroPython特定的详细信息，请参阅deflate模块文档。
   如果要解压缩的数据需要更大的窗口大小，它将在解压缩过程中失败。

.. function:: compress(data, wbits=15, /)

   将数据压缩为bytes对象。
   wbits允许你配置DEFLATE字典窗口大小和输出格式。窗口大小允许你权衡内存使用与压缩级别。更大的窗口大小将允许压缩器引用输入中更远的片段。输出格式为"原始"DEFLATE（无头部/尾部）、zlib和gzip，后两者包括头部和校验和。
   wbits绝对值的低四位设置DEFLATE字典窗口大小的以2为底的对数。例如，wbits=10、wbits=-10和wbits=26都将窗口大小设置为1024字节。有效的窗口大小是5到15（对应32到32k字节）。
   wbits的负值在-5到-15之间对应于"原始"输出模式，正值在5到15之间对应于zlib输出模式，正值在21到31之间对应于gzip输出模式。
   有关wbits参数的更多信息，请参阅CPython文档中有关zlib的内容。请注意，MicroPython允许更小的窗口大小，这在内存受限的情况下很有用，同时仍然实现合理的压缩级别。它还可以加快压缩器的速度。有关更多MicroPython特定的详细信息，请参阅deflate模块文档。
