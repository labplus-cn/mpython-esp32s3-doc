:mod:`errno` -- 系统错误代码
===================================

.. module:: errno
   :synopsis: 系统错误代码

这个模块实现了相应 :term:`CPython` 模块的一个子集，如下所述。有关更多信息，请参阅原始CPython文档: `errno <https://docs.python.org/3.5/library/errno.html#module-errno>`_

此模块提供访问符号错误代码以进行 :ref:`OSError <OSError>`  异常。特定的代码清单依赖于 :term:`MicroPython port`.


常量
---------

.. data:: EEXIST, EAGAIN, etc.

    错误代码，基于ANSI C/POSIX标准。所有错误代码开头都有“E”。如上所述，代码清单取决于MicroPython端口。错误通常可以访问为 ``exc.errno`` ，其中 ``exc`` 是 ``OSError`` 的一个实例

    示例::

        try:
            os.mkdir("my_dir")
        except OSError as exc:
            if exc.errno == errno.EEXIST:
                print("Directory already exists")

.. data:: errorcode

    字典将数字错误代码映射到带有符号错误代码的字符串（参见上文）::

        >>> print(errno.errorcode[errno.EEXIST])
        EEXIST


===================================  ================  ====================================
异常                                  值                描述
``errno.EPERM``                      1                Operation not permitted
``errno.ENOENT``                     2                No such file or directory
``errno.ESRCH``                      3                No such process
``errno.EINTR``                      4                Interrupted system call
``errno.EIO``                        5                I/O error
``errno.ENXIO``                      6                No such device or address
``errno.E2BIG``                      7                Argument list too long
``errno.ENOEXEC``                    8                Exec format error
``errno.EBADF``                      9                Bad file number
``errno.ECHILD``                     10               No child processes
``errno.EAGAIN``                     11               Try again
``errno.ENOMEM``                     12               Out of memory
``errno.EACCES``                     13               Permission denied
``errno.EFAULT``                     14               Bad address
``errno.ENOTBLK``                    15               Block device required
``errno.EBUSY``                      16               Device or resource busy
``errno.EEXIST``                     17               File exists
``errno.EXDEV``                      18               Cross-device link
``errno.ENODEV``                     19               No such device
``errno.ENOTDIR``                    20               Not a directory
``errno.EISDIR``                     21               Is a directory
``errno.EINVAL``                     22               Invalid argument
``errno.ENFILE``                     23               File table overflow
``errno.EMFILE``                     24               Too many open files
``errno.ENOTTY``                     25               Not a typewriter
``errno.ETXTBSY``                    26               Text file busy
``errno.EFBIG``                      27               File too large
``errno.ENOSPC``                     28               No space left on device
``errno.ESPIPE``                     29               Illegal seek
``errno.EROFS``                      30               Read-only file system
``errno.EMLINK``                     31               Too many links
``errno.EPIPE``                      32               Broken pipe
``errno.EDOM``                       33               Math argument out of domain of func
``errno.ERANGE``                     34               Math result not representable
``errno.EWOULDBLOCK``                11               Operation would block
``errno.EOPNOTSUPP``                 95               Operation not supported on transport endpoint
``errno.EAFNOSUPPORT``               97               Address family not supported by protocol
``errno.EADDRINUSE``                 98               Address already in use
``errno.ECONNABORTED``               99               Software caused connection abort
``errno.ECONNRESET``                 104              Connection reset by peer
``errno.ENOBUFS``                    105              No buffer space available
``errno.EISCONN``                    106              Transport endpoint is already connected
``errno.ENOTCONN``                   107              Transport endpoint is not connected
``errno.ETIMEDOUT``                  110              Connection timed out
``errno.ECONNREFUSED``               111              Connection refused
``errno.EHOSTUNREACH``               113              No route to host
``errno.EALREADY``                   114              Operation already in progress
``errno.EINPROGRESS``                115              Operation now in progress
===================================  ================  ====================================