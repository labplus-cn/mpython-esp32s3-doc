::: currentmodule
machine
:::

# 类 RTC \-- 实时时钟 {#machine.RTC}

RTC是独立的时钟，可以跟踪日期和时间。

示例:

    rtc = machine.RTC()
    rtc.datetime((2020, 1, 21, 2, 10, 32, 36, 0))
    print(rtc.datetime())

## 构建对象

::: {.RTC(id=0, ....)}
创建RTC对象。参见init方法获取初始化参数。
:::

## 方法

::: method
RTC.datetime(\[datetimetuple\])
:::

获取或设置RTC的日期和时间。
无参数时，此方法返回包含当前日期和时间的8元组。
有1个参数（8元组）时，它设置日期和时间。

8元组的格式如下：

(year, month, day, weekday, hours, minutes, seconds, subseconds)

subseconds字段的含义取决于硬件。

::: method
RTC.init(datetime)
:::

初始化RTC。datetime是以下形式的元组：

(year, month, day, hour, minute, second, microsecond, tzinfo)

必须提供所有八个参数。microsecond和tzinfo值目前被忽略，但将来可能会使用。

可用性：CC3200、ESP32、MIMXRT、SAMD。stm32和renesas-ra端口上的rtc.init()方法只是（重新）启动RTC，不接受参数。

::: method
RTC.now()
:::

获取当前日期时间元组。

可用性：WiPy。

::: method
RTC.deinit()
:::

将RTC重置为2015年1月1日的时间，并重新开始运行。

::: method
RTC.alarm(id, time, \*, repeat=False)
:::

设置RTC闹钟。time可以是毫秒值，用于将闹钟设置为当前时间 +
未来的time_in_ms，也可以是日期时间元组。如果传递的时间是毫秒，则repeat可以设置为True以使闹钟周期性触发。

::: method
RTC.alarm_left(alarm_id=0)
:::

获取闹钟到期前的毫秒数。

::: method
RTC.alarm_cancel(alarm_id=0)
:::

取消正在运行的闹钟。

mimxrt端口还将此函数公开为RTC.cancel(alarm_id=0)，但计划在MicroPython
2.0中移除。

::: method
RTC.irq(\*, trigger, handler=None, wake=machine.IDLE)
:::

创建由实时时钟闹钟触发的irq对象。

- trigger必须是RTC.ALARM0
- handler是触发回调时要调用的函数。
- wake指定此中断可以从哪个睡眠模式唤醒系统。

::: method
RTC.memory(\[data\])
:::

RTC.memory(data)将数据写入RTC内存，其中data是支持缓冲区协议的任何对象（包括bytes、bytearray、memoryview和array.array）。RTC.memory()读取RTC内存并返回bytes对象。

写入RTC用户内存的数据在重启后仍然保留，包括软重置和machine.deepsleep()。

ESP32上RTC用户内存的最大长度默认是2048字节，esp8266上是492字节。

可用性：esp32、esp8266端口。

## 常量

::: data
RTC.ALARM0
:::

irq触发源

注意：

- 虽然RTC能够跟踪时间和日期，但是RTC的精度存在一定的缺陷，每过7:45h便会有秒级别的误差溢出，所以建议每隔7小时进行一次时间的校准。
- 由于计时器无法在掉电后进行计时工作，这就会导致你的设备在下次开机前进入初始的时间2000年1月1号。所以如果要对时间进行精准的掌控，我们需要在开机时进行时间的校准。
- 你可以使用 `ntptime`{.interpreted-text role="mod"}
  模块进行网络授时校准时间。
