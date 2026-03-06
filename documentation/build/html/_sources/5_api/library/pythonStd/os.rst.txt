:mod:`os` -- 基本的操作系统
===============================================

.. module:: os
   :synopsis: 操作系统

这个模块实现了相应 :term:`CPython` 模块的一个子集，如下所述。有关更多信息，请参阅原始CPython文档: `os <https://docs.python.org/3.5/library/os.html#module-os>`_

该os模块包含文件系统访问和安装，终端重定向和复制 ``uname`` 以及 ``urandom`` 功能的功能。

一般功能
---------

.. function:: uname()

返回一个元组(可能是一个命名元组)，其中包含关于底层和/或其操作系统的信息。元组有五个字段，每个字段的顺序如下:

  * ``sysname`` -- 底层系统的名称
  * ``nodename`` -- 网络名称（和sysname相同）
  * ``release`` -- 底层系统的版本
  * ``version`` -- MiroPython版本和构建日期
  * ``machine`` --  底层硬件的标识符(eg board, CPU)

示例::

  >>> import os
  >>> os.uname()
  (sysname='esp32', nodename='esp32', release='1.9.1', version='v1.9.1-224-g83d3f3f-dirty on 2017-12-12', machine='ESP32 module with ESP32')


.. function:: urandom(n)

返回一个带有n个随机字节的字节对象。它是由硬件随机数生成器生成。

示例::

  >>> os.urandom(20)
  b'f\x92\x85t28\xa1\xf0\xaf3\xf5\xd9\xcdx\xc3\n\xedm\xf8\xb7'


文件系统访问
---------

.. function:: chdir(path)

更改当前目录。

.. function:: getcwd()

获取当前目录。

示例::

  >>> os.getcwd()
  '/'
  >>> os.chdir("./lib")
  >>> os.getcwd()
  '/lib'
  >>> os.chdir("..")
  >>> os.getcwd()
  '/'


.. function:: ilistdir([dir])

此函数返回一个迭代器，然后生成与列出的目录中的条目对应的元组。没有参数，它列出了当前目录，否则它列出了dir给出的目录。

元组的形式为 *(name, type, inode[, size])*:

  - *name* 是一个字符串（如果dir是一个字节对象，则为字节），并且是条目的名称;
  - *type* 是一个整数，指定条目的类型，目录为0x4000，常规文件为0x8000;
  - *inode* 是对应于文件inode的整数，对于没有这种概念的文件系统可以是0;
  - *size* 是一个整数，可能根据文件系统类型包含。对于文件条目，size表示文件的大小或-1（如果未知）。对于目录条目，其含义目前未定义。

.. function:: listdir([dir])

如果没有参数，请列出当前目录。否则列出给定目录。

示例::
  >>> os.listdir()
  ['boot.py', 'lib']
  >>> os.listdir("./lib")
  ['test.py']


.. function:: mkdir(path)

创建目录，path为创建目录的路径。 

示例::

  >>> os.listdir()
  ['boot.py']
  >>> path = "./lib"
  >>> os.mkdir(path)
  >>> os.listdir()
  ['boot.py', 'lib']

.. function:: remove(path)

删除文件。 

示例::

  >>> os.listdir("./lib")
  ['test.py']
  >>> os.remove("./lib/test.py")
  >>> os.listdir("./lib")
  []


.. function:: rmdir(path)

删除目录。

示例::

  >>> os.listdir()
  ['boot.py', 'lib']
  >>> os.rmdir("./lib")
  >>> os.listdir()
  ['boot.py']


.. function:: rename(old_path, new_path)

重命名文件。 

示例::

  >>> os.listdir(os.getcwd())
  ['test.py']
  >>> os.rename("test.py", "mytest.py")
  >>> os.listdir(os.getcwd())
  ['mytest.py']


.. function:: stat(path)

获取文件或目录的状态。 

示例::

  >>> os.stat("./lib")
  (16384, 0, 0, 0, 0, 0, 0, 0, 0, 0)
  >>> os.stat("./lib/test.py")
  (32768, 0, 0, 0, 0, 0, 1, 0, 0, 0)

.. function:: statvfs(path)

获取文件系统的状态。

返回包含以下顺序的文件系统信息的元组：

  * ``f_bsize`` -- 文件系统块大小
  * ``f_frsize`` -- 片段大小
  * ``f_blocks`` --  f_frsize单位的fs大小
  * ``f_bfree`` -- free blocks数量
  * ``f_bavail`` -- number of free blocks for unpriviliged users
  * ``f_files`` -- inodes数量
  * ``f_ffree`` -- number of free inodes
  * ``f_favail`` -- number of free inodes for unpriviliged users
  * ``f_flag`` -- mount flags
  * ``f_namemax`` -- 最大文件名长度

相关信息节点参数： ``f_files`` ，``f_ffree`` ，``f_avail`` 和 ``f_flags`` 参数可能会返回0。

.. function:: sync()

同步所有文件系统。

终端重定向和复制
---------------

.. function:: dupterm(stream_object, index=0, /)

复制或切换给定类似 ``stream`` 对象上的MicroPython终端（REPL）。所述 `stream_object` 参数必须是一个本地流对象，或从导出 ``io.IOBase`` 并实施 ``readinto()`` 和 ``write()`` 方法。流应处于非阻塞模式，如果没有可用于读取的数据， ``readinto()`` 则应返回 ``None``。

调用此函数后，将在此流上重复所有终端输出，并且流上可用的任何输入都将传递到终端输入。

所述索引参数应该是哪个复制时隙设置一个非负整数，并且指定。给定端口可以实现多个槽（槽0将始终可用），并且在这种情况下，终端输入和输出在所有设置的槽上复制。

如果 ``None`` 作为 `stream_object` 传递，则在索引给出的槽上取消复制。

该函数返回给定槽中的前一个类似流的对象。

.. function:: dupterm_notify(obj_in, /)

通知MicroPython REPL，通过os.dupterm()先前注册的类似流对象上有输入可用。

此函数应由自定义流实现（例如UART、Bluetooth或其他非USB REPL流）调用，以通知REPL输入已准备好读取。正确使用可确保REPL及时处理特殊字符（如用于触发KeyboardInterrupt的Ctrl+C），从而为用户代码启用预期的中断行为。

obj_in参数被os.dupterm_notify()忽略，但需要允许从中断处理程序（如UART.irq()）调用dupterm_notify。

示例::

  from machine import UART
  import os
  uart = UART(0)
  os.dupterm(uart, 0)
  uart.irq(os.dupterm_notify, machine.UART.IRQ_RX)


.. note::

    如果不调用dupterm_notify()函数，来自自定义流的输入可能不会被检测或处理，直到下一次REPL轮询，这可能会延迟KeyboardInterrupt或其他控制信号。
    这对于UART、Bluetooth和其他非标准REPL连接尤为重要，因为自动通知不能保证。


文件系统安装
----------

以下函数和类已移至vfs模块。它们仅在此模块中提供以实现向后兼容性，并将在MicroPython 2版本中删除。

.. function:: mount(fsobj, mount_point, \*, readonly)

    请参阅vfs.mount。

.. function:: umount(mount_point)

    请参阅vfs.umount。

.. class:: VfsFat(block_dev)

    请参阅vfs.VfsFat。

.. class:: VfsLfs1(block_dev, readsize=32, progsize=32, lookahead=32)

    请参阅vfs.VfsLfs1。

.. class:: VfsLfs2(block_dev, readsize=32, progsize=32, lookahead=32, mtime=True)

    请参阅vfs.VfsLfs2。

.. class:: VfsPosix(root=None)

    请参阅vfs.VfsPosix。
