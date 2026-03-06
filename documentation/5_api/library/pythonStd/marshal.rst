:mod:`marshal` --- Python对象序列化
====================================

.. module:: marshal
   :synopsis: Python对象序列化

该模块实现了相应 :term:`CPython` 模块的一个子集，如下所述。有关更多信息，请参阅原始CPython文档: `marshal <https://docs.python.org/3.5/library/marshal.html#module-marshal>`_

该模块实现了Python对象与二进制格式之间的转换。
该格式是MicroPython特有的，但不依赖于机器架构，因此数据可以在不同的MicroPython实例之间传输和使用，只要二进制数据的版本匹配（当前版本与mpy文件版本相同，参见MicroPython .mpy文件）。

函数
~~~~~

.. function:: marshal.dumps(value, /)

    将给定值转换为二进制格式并返回相应的bytes对象。
    目前，代码对象是唯一支持可以转换的值。

.. function:: marshal.loads(data, /)

    将给定的类bytes数据转换为相应的Python对象并返回它。