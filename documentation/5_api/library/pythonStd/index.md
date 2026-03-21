# Python标准库 {#pythonStd}

MicroPython提供了与Python标准库功能相似的内置模块（例如
`os`、`time`），以及MicroPython特定的模块（例如
`bluetooth`、`machine`）。大多数Python标准库模块实现了等效Python模块功能的子集，在少数情况下提供了一些MicroPython特定的扩展（例如
`array`、`os`）。

由于资源限制或其他限制，某些端口或固件版本可能不包含本文档中记录的所有功能。

为了允许扩展，一些内置模块可以从加载到设备文件系统的Python代码中进行扩展。

以下是已被"微型化"以符合MicroPython理念的标准Python库。它们提供了该模块的核心功能，旨在作为标准Python库的直接替代品。

> ::: {.toctree maxdepth="1"}
> array.rst asyncio.rst binascii.rst builtins.rst cmath.rst
> collections.rst errno.rst gc.rst gzip.rst hashlib.rst heapq.rst io.rst
> json.rst marshal.rst math.rst os.rst platform.rst
> ../micropython/random.rst re.rst select.rst socket.rst ssl.rst
> struct.rst sys.rst time.rst zlib.rst ../micropython/\_thread.rst
> :::
