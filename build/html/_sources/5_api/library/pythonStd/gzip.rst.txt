:mod:`gzip` --- gzip压缩和解压缩
==================================

.. module:: gzip
   :synopsis: gzip压缩和解压缩

该模块实现了相应 :term:`CPython` 模块的一个子集，如下所述。有关更多信息，请参阅原始CPython文档: `gzip <https://docs.python.org/3.5/library/gzip.html#module-gzip>`_

该模块允许使用gzip文件格式使用的DEFLATE算法对二进制数据进行压缩和解压缩。

.. note::

   建议使用 deflate.DeflateIO 而不是此模块中的函数，因为它提供了压缩和解压缩的流式接口，在处理从文件、套接字或流读取或写入压缩数据时更方便且内存效率更高。

可用性：

此模块默认不存在于官方MicroPython固件版本中，因为它重复了deflate模块中可用的功能。
可以从micropython-lib（源）安装（或冻结）此模块的副本。
有关更多信息，请参阅包管理。本文档描述了该模块。
只有在内置deflate模块中启用了压缩支持时，才会提供压缩支持。

快速使用示例::

    import gzip

    # 压缩文件
    with gzip.open('example.txt.gz', 'wb') as f:
        f.write(b'Hello, World!')

    # 解压缩文件
    with gzip.open('example.txt.gz', 'rb') as f:
        content = f.read()
        print(content)

函数
~~~~~

.. function:: gzip.open(filename, mode, /)

    内置open()的包装器，返回GzipFile实例。

.. function:: gzip.decompress(data, /)

    将数据解压缩为bytes对象。

.. function:: gzip.compress(data, /)

    将数据压缩为bytes对象。

类
~~~~~

.. class:: gzip.GzipFile(*, fileobj, mode)

    此类可用于包装fileobj，fileobj是任何类似流的对象，如文件、套接字或流（包括io.BytesIO）。它本身是一个流，并实现了标准的read/readinto/write/close方法。

    当mode参数为"rb"时，从GzipFile实例读取将解压缩底层流中的数据并返回解压缩的数据。
    如果启用了压缩支持，则mode参数可以设置为"wb"，写入GzipFile实例的数据将被压缩并写入底层流。

    默认情况下，GzipFile类将使用gzip文件格式读写数据，包括带有校验和的头部和尾部，窗口大小为512字节。

    不支持file、compresslevel和mtime参数。fileobj和mode必须始终作为关键字参数指定。

    .. method:: GzipFile.read(size=-1)

        读取指定大小的数据。

    .. method:: GzipFile.write(data)

        写入数据。

    .. method:: GzipFile.close()

        关闭文件。

示例
~~~~~

gzip.GzipFile的典型用例是从存储中读取或写入压缩文件：

::

    import gzip

    # 读取：
    with open("data.gz", "rb") as f:
        with gzip.GzipFile(fileobj=f, mode="rb") as g:
            # 使用 g.read(), g.readinto(), 等

     # 同样，但使用 gzip.open:
    with gzip.open("data.gz", "rb") as f:
         # 使用 f.read(), f.readinto(), 等

    # 写入：
    with open("data.gz", "wb") as f:
        with gzip.GzipFile(fileobj=f, mode="wb") as g:
            # 使用 g.write(...) 等

    # 同样，但使用 gzip.open:
    with gzip.open("data.gz", "wb") as f:
        # 使用 f.write(...) 等

    # 以gzip格式写入字典作为JSON，使用小（64字节）窗口大小。
    config = { ... }
    with gzip.open("config.gz", "wb") as f:
        json.dump(config, f)

有关使用gzip源和选择窗口大小的指导，请参阅deflate文档末尾的注释。