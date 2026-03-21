::: currentmodule
machine
:::

# class SPI \-- a Serial Peripheral Interface bus protocol (master) {#machine.SPI}

SPI is a synchronous serial protocol driven by a master. At the physical
level, the bus consists of 3 lines: SCK, MOSI, MISO. Multiple devices
can share the same bus. Each device should have a separate SS (slave
select) signal to select which device on the bus to communicate with.
The SS signal is usually controlled by a GPIO pin, which should be
managed by user code (via the `machine.Pin`{.interpreted-text
role="class"} class).

::: admonition
什么是SPI？

SPI是串行外设接口(Serial Peripheral Interface)的缩写。是 Motorola
公司推出的一 种同步串行接口技术，是一种高速的，全双工，同步的通信总线。
SPI协议主要用于短距离的通信系统中，特别是嵌入式系统，很多芯片的外围设备，比如LED显示驱动器、I／O接口芯片、UART收发器等都广泛的采用SPI总线协议。
:::

## Constructors

::: {.SPI(id, ....)}
Construct an SPI object on the given bus.

> - `id` - when 1, it\'s hardware SPI. When omitted, it constructs a
>   software SPI.
:::

Hardware SPI construction:

    >>> from machine import SPI
    >>> hspi = SPI(1)
    >>> hspi
    SPI(id=1, baudrate=500000, polarity=0, phase=0, bits=8, firstbit=0, sck=-1, mosi=-1, miso=-1)
    >>> 

Software SPI construction:

    from machine import SPI, Pin

    spi = SPI(baudrate=100000, polarity=1, phase=0, sck=Pin(17), mosi=Pin(27), miso=Pin(18))

## Methods

::: method
SPI.init(baudrate=1000000, \*, polarity=0, phase=0, bits=8,
firstbit=SPI.MSB, sck=None, mosi=None, miso=None, pins=(SCK, MOSI,
MISO))

Initialise the SPI bus with the given parameters:

> - `baudrate` SCK clock frequency.
> - `polarity` 0 or 1, the level the clock is at when idle.
> - `phase` 0 or 1 to sample data on the first or second clock edge
>   respectively.
> - `bits` width of each transfer, in bits. All hardware is guaranteed
>   to support 8 bits.
> - `firstbit` can be `SPI.MSB` or `SPI.LSB`.
> - `sck`, `mosi`, `miso` are pins (machine.Pin) objects for the bus
>   signals. For most hardware SPI blocks (selected by `id` parameter to
>   the constructor), pins are fixed and cannot be changed. In some
>   cases, hardware modules allow 2-3 alternative pin sets for a
>   hardware SPI module. Arbitrary pin assignment is only possible for
>   the bitbanging SPI driver (`id` = -1).
> - `pins` - esp32 does not have `sck`, `mosi`, `miso` parameters, but
>   instead allows specifying them as a tuple via the `pins` parameter.
:::

::: method
SPI.deinit()

Turn off the SPI bus.
:::

::: method
SPI.read(nbytes, write=0x00)

Read the specified number of bytes, `nbytes`, while continuously writing
the single byte given by `write`. Returns a `bytes` object containing
the data read.
:::

::: method
SPI.readinto(buf, write=0x00)

Read into the buffer specified by `buf`, while continuously writing the
single byte given by `write`.

Returns `None`.

Note: On `esp32`, this function returns the number of bytes read.
:::

::: method
SPI.write(buf)

Write the bytes contained in `buf`.

Returns `None`.

Note: On `esp32`, this function returns the number of bytes written.
:::

::: method
SPI.write_readinto(write_buf, read_buf)

Write the bytes from `write_buf` while reading into `read_buf`. The
buffers can be the same or different, but both buffers must have the
same length.

Returns `None`.

Note: On `esp32`, this function returns the number of bytes written.
:::

## Constants

::: data
SPI.MASTER

Used to initialize the SPI bus as a master; this is only used on
`esp32`.
:::

::: data
SPI.MSB

Set the first bit to the most significant bit.
:::

::: data
SPI.LSB

Set the first bit to the least significant bit.
:::
