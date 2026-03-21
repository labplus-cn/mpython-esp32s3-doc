# `asyncio`{.interpreted-text role="mod"} \-\-- 异步I/O调度器

::: {.module synopsis="异步I/O调度器"}
asyncio
:::

该模块实现了相应 `CPython`{.interpreted-text role="term"}
模块的一个子集，如下所述。有关更多信息，请参阅原始CPython文档:
[asyncio](https://docs.python.org/3.5/library/asyncio.html#module-asyncio)

该模块提供了用于编写并发代码的基础设施，使用协程、事件循环和Future对象。

快速使用示例:

    import asyncio

    async def blink(led, period_ms):
        while True:
            led.on()
            await asyncio.sleep_ms(5)
            led.off()
            await asyncio.sleep_ms(period_ms)

    async def main(led1, led2):
        asyncio.create_task(blink(led1, 700))
        asyncio.create_task(blink(led2, 400))
        await asyncio.sleep_ms(10_000)

    # 在pyboard上运行
    from pyb import LED
    asyncio.run(main(LED(1), LED(2)))

    # 在通用板上运行
    from machine import Pin
    asyncio.run(main(Pin(1), Pin(2)))

## 核心函数

::: function
asyncio.create_task(coro)

从给定的协程创建一个新任务并安排它运行。 返回相应的Task对象。
:::

::: function
asyncio.current_task()

返回与当前运行的任务关联的Task对象。
:::

::: function
asyncio.run(coro)

从给定的协程创建一个新任务并运行直到完成。 返回coro返回的值。
:::

::: function
asyncio.sleep(t)

睡眠t秒（可以是浮点数）。 这是一个协程。
:::

::: function
asyncio.sleep_ms(t)

睡眠t毫秒。 这是一个协程，是MicroPython扩展。
:::

## 附加函数

::: function
asyncio.wait_for(awaitable, timeout)

等待awaitable完成，但如果超过timeout秒则取消它。如果awaitable不是任务，则会从中创建一个任务。
如果发生超时，它会取消任务并引发asyncio.TimeoutError：这应该被调用者捕获。任务会收到asyncio.CancelledError，它可以被忽略或使用try\...except或try\...finally来运行清理代码。
返回awaitable的返回值。 这是一个协程。
:::

::: function
asyncio.wait_for_ms(awaitable, timeout)

类似于wait_for，但timeout是以毫秒为单位的整数。
这是一个协程，是MicroPython扩展。
:::

::: function
asyncio.gather(\*awaitables, return_exceptions=False)

并发运行所有awaitables。任何不是任务的awaitables都会被提升为任务。
返回所有awaitables的返回值列表。 这是一个协程。
:::

## 类

:::: asyncio.Task
这个对象将协程包装成一个运行中的任务。任务可以使用await
task来等待，这将等待任务完成并返回任务的返回值。
任务不应该直接创建，而是使用create_task来创建它们。

::: method
Task.cancel()

通过向任务注入asyncio.CancelledError来取消任务。任务可能会忽略此异常。清理代码可以通过捕获它或通过try\...finally来运行。
:::
::::

::::::: asyncio.Event
创建一个新的事件，可用于同步任务。事件开始时处于清除状态。

::: method
Event.is_set()

如果事件已设置，返回True，否则返回False。
:::

::: method
Event.set()

设置事件。任何等待事件的任务都将被安排运行。
注意：这必须在任务中调用。从IRQ、调度器回调或其他线程调用此方法是不安全的。请参阅ThreadSafeFlag。
:::

::: method
Event.clear()

清除事件。
:::

::: method
Event.wait()

等待事件被设置。如果事件已经设置，则立即返回。 这是一个协程。
:::
:::::::

:::::: asyncio.ThreadSafeFlag
创建一个新的标志，可用于将任务与在asyncio循环外部运行的代码同步，例如其他线程、IRQ或调度器回调。标志开始时处于清除状态。

::: method
ThreadSafeFlag.set()

设置标志。如果有任务在等待标志，它将被安排运行。
:::

::: method
ThreadSafeFlag.clear()

清除标志。这可用于确保在等待标志之前清除可能先前设置的标志。
:::

::: method
ThreadSafeFlag.wait()

等待标志被设置。如果标志已经设置，则立即返回。标志在从wait返回时自动重置。
一次只能有一个任务等待标志。 这是一个协程。
:::
::::::

:::::: asyncio.Lock
创建一个新的锁，可用于协调任务。锁开始时处于未锁定状态。
除了下面的方法外，锁还可以在async with语句中使用。

::: method
Lock.locked()

如果锁已锁定，返回True，否则返回False。
:::

::: method
Lock.acquire()

等待锁处于未锁定状态，然后以原子方式锁定它。任何时候只有一个任务可以获取锁。
这是一个协程。
:::

::: method
Lock.release()

释放锁。如果有任务在等待锁，队列中的下一个任务将被安排运行，锁保持锁定状态。否则，没有任务在等待，锁变为未锁定状态。
:::
::::::

## TCP流连接

::: function
asyncio.open_connection(host, port, ssl=None)

打开到给定主机和端口的TCP连接。主机地址将使用socket.getaddrinfo解析，这目前是一个阻塞调用。
如果ssl是ssl.SSLContext对象，此上下文用于创建传输；如果ssl为True，则使用默认上下文。
返回一对流：读取器和写入器流。
如果主机无法解析或连接无法建立，将引发特定于套接字的OSError。
这是一个协程。
:::

::: function
asyncio.start_server(callback, host, port, backlog=5, ssl=None)

在给定的主机和端口上启动TCP服务器。回调将被调用以处理传入的、已接受的连接，并被传递2个参数：连接的读取器和写入器流。
如果ssl是ssl.SSLContext对象，此上下文用于创建传输。 返回一个Server对象。
这是一个协程。
:::

::::::::::: asyncio.Stream
这表示一个TCP流连接。为了最小化代码，此类同时实现了读取器和写入器，StreamReader和StreamWriter都别名为此类。

获取流的额外信息，由v给定。v的有效值为：peername。

::: method
Stream.close()

关闭流。
:::

::: method
Stream.wait_closed()

等待流关闭。 这是一个协程。
:::

::: method
Stream.read(n=-1)

读取最多n个字节并返回它们。如果n未提供或为-1，则读取所有字节直到EOF。如果在读取任何字节之前遇到EOF，返回的值将是一个空字节对象。
这是一个协程。
:::

::: method
Stream.readinto(buf)

读取最多n个字节到buf中，n等于buf的长度。 返回读入buf的字节数。
这是一个协程，是MicroPython扩展。
:::

::: method
Stream.readexactly(n)

读取恰好n个字节并将它们作为字节对象返回。
如果流在读取n个字节之前结束，会引发EOFError异常。 这是一个协程。
:::

::: method
Stream.readline()

读取一行并返回它。 这是一个协程。
:::

::: method
Stream.write(buf)

将buf累积到输出缓冲区。数据只有在调用Stream.drain时才会被刷新。建议在调用此函数后立即调用Stream.drain。
:::

::: method
Stream.drain()

排空（写入）所有缓冲的输出数据到流。 这是一个协程。
:::
:::::::::::

::::: asyncio.Server
这表示从start_server返回的服务器类。它可以在async
with语句中使用，以在退出时关闭服务器。

::: method
Server.close()

关闭服务器。
:::

::: method
Server.wait_closed()

等待服务器关闭。 这是一个协程。
:::
:::::

## 事件循环

::: function
asyncio.get_event_loop()

返回用于调度和运行任务的事件循环。请参阅Loop。
:::

::: function
asyncio.new_event_loop()

重置事件循环并返回它。
注意：由于MicroPython只有一个事件循环，此函数只是重置循环的状态，而不是创建一个新的循环。
:::

:::::::::::: asyncio.Loop
这表示调度和运行任务的对象。它不能被创建，请使用get_event_loop代替。

::: method
Loop.create_task(coro)

从给定的coro创建一个任务并返回新的Task对象。
:::

::: method
Loop.run_forever()

运行事件循环直到调用stop()。
:::

::: method
Loop.run_until_complete(awaitable)

运行给定的awaitable直到完成。如果awaitable不是任务，它将被提升为任务。
:::

::: method
Loop.stop()

停止事件循环。
:::

::: method
Loop.close()

关闭事件循环。
:::

::: method
Loop.set_exception_handler(handler)

设置当Task引发未捕获的异常时要调用的异常处理程序。处理程序应接受两个参数：(loop,
context)。
:::

::: method
Loop.get_exception_handler()

获取当前的异常处理程序。返回处理程序，如果没有设置自定义处理程序，则返回None。
:::

::: method
Loop.default_exception_handler(context)

被调用的默认异常处理程序。
:::

::: method
Loop.call_exception_handler(context)

调用当前的异常处理程序。参数context被传递，是一个包含键：\'message\'、\'exception\'、\'future\'的字典。
:::
::::::::::::
