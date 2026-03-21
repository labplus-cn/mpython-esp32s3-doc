# `deflate`{.interpreted-text role="mod"} \-- deflate压缩与解压缩

::: {.module synopsis="deflate压缩与解压缩"}
deflate
:::

该模块允许使用DEFLATE算法压缩和解压缩二进制数据
（通常在zlib库和gzip归档器中使用）。

可用性：

- 在MicroPython v1.21中添加。
- 解压缩：通过MICROPY_PY_DEFLATE构建选项启用，在具有\"额外功能\"级别或更高的端口上默认启用（大多数板）。
- 压缩：通过MICROPY_PY_DEFLATE_COMPRESS构建选项启用，在具有\"完整功能\"级别或更高的端口上默认启用（通常这意味着您需要构建自己的固件来启用此功能）。

## 类

::: {.DeflateIO(stream, .format=AUTO, .wbits=0, .close=False, ./)}
此类可用于包装流，该流是任何类似流的对象，如文件、套接字或流（包括io.BytesIO）。
它本身是一个流，并实现了标准的read/readinto/write/close方法。

流必须是阻塞流。当前不支持非阻塞流。

format可以设置为下面定义的任何常量，默认为AUTO，对于解压缩，它会自动检测gzip或zlib流，
对于压缩，它会生成原始流。

wbits参数设置DEFLATE字典窗口大小的以2为底的对数。例如，将wbits设置为10会将窗口大小设置为1024字节。
有效值为5到15（对应于32到32k字节的窗口大小）。

如果wbits设置为0（默认值），则对于压缩，将使用256字节的窗口大小（就像wbits设置为8一样）。
对于解压缩，它取决于格式：

- RAW将使用256字节（对应于wbits设置为8）。
- ZLIB（或检测到zlib的AUTO）将使用zlib头中的值。
- GZIP（或检测到gzip的AUTO）将使用32千字节（对应于wbits设置为15）。

有关窗口大小、zlib和gzip流的更多信息，请参见下面的窗口大小说明。

如果close设置为True，则当deflate.DeflateIO流关闭时，基础流将自动关闭。
这在您希望返回包装另一个流的deflate.DeflateIO流，而不需要调用者了解管理基础流时很有用。

如果启用了压缩，给定的deflate.DeflateIO实例同时支持读取和写入。
例如，可以包装双向流（如套接字），这允许在两个方向上进行压缩/解压缩。
:::

## 常量

::: data
AUTO
:::

::: data
RAW
:::

::: data
ZLIB
:::

::: data
GZIP

format参数的支持值。
:::

## 示例

deflate.DeflateIO的典型用例是从存储中读取或写入压缩文件：

    import deflate

    # 写入zlib压缩流（使用默认的256字节窗口大小）。
    with open("data.gz", "wb") as f:
        with deflate.DeflateIO(f, deflate.ZLIB) as d:
            # 使用d.write(...)等

    # 读取zlib压缩流（自动检测窗口大小）。
    with open("data.z", "rb") as f:
        with deflate.DeflateIO(f, deflate.ZLIB) as d:
            # 使用d.read()、d.readinto()等。

因为deflate.DeflateIO是一个流，它可以用于例如json.dump()和json.load()（以及任何其他可以使用流的地方）：

    import deflate, json

    # 将字典作为JSON以gzip格式写入，使用小（64字节）窗口大小。
    config = { ... }
    with open("config.gz", "wb") as f:
        with deflate.DeflateIO(f, deflate.GZIP, 6) as f:
            json.dump(config, f)

    # 读回该字典。
    with open("config.gz", "rb") as f:
        with deflate.DeflateIO(f, deflate.GZIP, 6) as f:
            config = json.load(f)

如果源数据不是流格式，您可以使用io.BytesIO将其转换为适合与deflate.DeflateIO一起使用的流：

    import deflate, io

    # 解压缩bytes/bytearray值。
    compressed_data = get_data_z()
    with deflate.DeflateIO(io.BytesIO(compressed_data), deflate.ZLIB) as d:
        decompressed_data = d.read()

    # 压缩bytes/bytearray值。
    uncompressed_data = get_data()
    stream = io.BytesIO()
    with deflate.DeflateIO(stream, deflate.ZLIB) as d:
        d.write(uncompressed_data)
    compressed_data = stream.getvalue()

## Deflate窗口大小

窗口大小限制了（解）压缩器可以引用流中回溯的距离。增加窗口大小将提高压缩率，但会需要更多内存并使压缩器变慢。

如果输入流使用给定的窗口大小压缩，那么使用较小窗口大小的DeflateIO将在解压缩过程中中途失败，并出现OSError，但只有当回引用实际上引用的距离超过了解压缩器的窗口大小时才会发生。
这意味着使用较小的窗口大小可能可以解压缩。例如，如果原始未压缩数据短于窗口大小，情况就是如此。

## 解压缩

zlib格式包含一个头部，指定用于压缩数据的窗口大小。这表示解压缩此流所需的最大窗口大小。
如果此头部值小于指定的wbits值（或如果wbits未设置），则将使用头部值。

gzip格式在头部中不包含窗口大小，并假设所有gzip压缩器（例如gzip实用程序或CPython的gzip.GzipFile实现）使用最大32kiB的窗口大小。
因此，如果未设置wbits参数，解压缩器将使用32
kiB的窗口大小（对应于wbits设置为15）。
这意味着要能够解压缩任意gzip流，您必须至少有这么多RAM可用。
如果您控制源数据，考虑改用具有较小窗口大小的zlib格式。

原始格式没有头部，因此不包含有关窗口大小的任何信息。如果未设置wbits，则默认窗口大小为256字节，这对于给定流可能不够大。
因此，建议在使用原始格式时始终显式设置wbits。

## 压缩

对于压缩，MicroPython将为所有格式默认使用256字节的窗口大小。这提供了合理的压缩量，同时具有最小的内存使用和快速的压缩时间，
并将生成可与任何解压缩器一起使用的输出。
