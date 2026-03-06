:mod:`deflate` -- deflate压缩与解压缩
=========================================

.. module:: deflate
   :synopsis: deflate压缩与解压缩

该模块提供了deflate压缩与解压缩功能。

函数
-------

.. function:: compress(data, level=6)

    压缩数据。

    参数:
        * ``data``: 要压缩的数据（类似字节）
        * ``level``: 压缩级别（0-9，默认为6）

    返回值:
        压缩后的数据（bytes对象）

.. function:: decompress(data)

    解压缩数据。

    参数:
        * ``data``: 要解压缩的数据（类似字节）

    返回值:
        解压缩后的数据（bytes对象）