# `ustruct`{.interpreted-text role="mod"} \-- 打包和解压缩原始数据类型

::: {.module synopsis="打包和解压缩原始数据类型"}
ustruct
:::

这个模块实现了相应 `CPython`{.interpreted-text role="term"}
模块的一个子集，如下所述。有关更多信息，请参阅原始CPython文档:
[struct](https://docs.python.org/3.5/library/struct.html#module-struct)

## 格式化字符串

格式字符串是用于在打包和解包数据时指定预期布局的机制。它们是从格式字符构建的，它指定打包/解包的数据类型。此外，还有用于控制字节顺序，大小和对齐的特殊字符。

### 字节顺序，大小和对齐

默认情况下，C类型以机器的本机格式和字节顺序表示，并在必要时通过跳过填充字节进行正确对齐（根据C编译器使用的规则）。
或者，根据下表，格式字符串的第一个字符可用于指示打包数据的字节顺序，大小和对齐方式：

  -----------------------------------------------------------
  Character   Byte order               Size       Alignment
  ----------- ------------------------ ---------- -----------
  `@`         native                   native     native

  `=`         native                   standard   none

  `<`         little-endian            standard   none

  `>`         big-endian               standard   none

  `!`         network (= big-endian)   standard   none
  -----------------------------------------------------------

### 格式字符

格式字符具有以下含义;
根据类型，C和Python值之间的转换应该是显而易见的。"标准大小"列是指使用标准大小时打包值的大小（以字节为单位）;
也就是说，当格式字符串中的一个开始\'\<\'，\'\>\'，\'!\'或
\'=\'。使用本机大小时，打包值的大小取决于平台。

  ---------------------------------------------------------------------------------
  Format   C Type                               Python type         Standard size
  -------- ------------------------------------ ------------------- ---------------
  `x`      pad byte                             no value            

  `c`      `char`{.interpreted-text             bytes of length 1   1
           role="c:type"}                                           

  `b`      `signed char`{.interpreted-text      integer             1
           role="c:type"}                                           

  `B`      `unsigned char`{.interpreted-text    integer             1
           role="c:type"}                                           

  `?`      `_Bool`{.interpreted-text            bool                1
           role="c:type"}                                           

  `h`      `short`{.interpreted-text            integer             2
           role="c:type"}                                           

  `H`      `unsigned short`{.interpreted-text   integer             2
           role="c:type"}                                           

  `i`      `int`{.interpreted-text              integer             4
           role="c:type"}                                           

  `I`      `unsigned int`{.interpreted-text     integer             4
           role="c:type"}                                           

  `l`      `long`{.interpreted-text             integer             4
           role="c:type"}                                           

  `L`      `unsigned long`{.interpreted-text    integer             4
           role="c:type"}                                           

  `q`      `long long`{.interpreted-text        integer             8
           role="c:type"}                                           

  `Q`      `unsigned long                       integer             8
           long`{.interpreted-text                                  
           role="c:type"}                                           

  `n`      `ssize_t`{.interpreted-text          integer             
           role="c:type"}                                           

  `N`      `size_t`{.interpreted-text           integer             
           role="c:type"}                                           

  `e`      \(7\)                                float               2

  `f`      `float`{.interpreted-text            float               4
           role="c:type"}                                           

  `d`      `double`{.interpreted-text           float               8
           role="c:type"}                                           

  `s`      `char[]`{.interpreted-text           bytes               
           role="c:type"}                                           

  `p`      `char[]`{.interpreted-text           bytes               
           role="c:type"}                                           

  `P`      `void \*`{.interpreted-text          integer             
           role="c:type"}                                           
  ---------------------------------------------------------------------------------

## 函数

::: function
calcsize(fmt)

返回需存入给定 *fmt* 的字节数量。

- `fmt` - 格式字符类型,见上文格式字符表

> \>\>\> struct.calcsize(\"i\") 4 \>\>\> struct.calcsize(\"B\") 1
:::

::: function
pack(fmt, v1, v2, \...)

根据格式字符串fmt，打包 *v1, v2, \...*
值。返回值为一个解码该值的字节对象。

> \>\>\> struct.pack(\"ii\", 3, 2) b\'x03x00x00x00x02x00x00x00\'
:::

::: function
pack_into(fmt, buffer, offset, v1, v2, \...)

根据格式字符串fmt，将 *v1, v2, \...* 值打包进从 *offset*
开始的缓冲区。从缓冲区的末端计数， *offset* 可能为负值。
:::

::: function
unpack(fmt, data)

根据格式字符串 *fmt* 对数据进行解压。返回值为一个解压值元组。

> \>\>\> buf = struct.pack(\"bb\", 1, 2) \>\>\> print(buf) b\'x01x02\'
> \>\>\> print(struct.unpack(\"bb\", buf)) (1, 2)
:::

::: function
unpack_from(fmt, data, offset=0)

根据格式字符串 `fmt` 从 `offset`
处开始的数据解包。从缓冲区的末尾开始计数的偏移量可能为负。返回值是解压缩值的元组。

> \>\>\> buf = struct.pack(\"bb\", 1, 2) \>\>\>
> print(struct.unpack(\"bb\", buf)) (1, 2) \>\>\>
> print(struct.unpack_from(\"b\", buf, 1)) (2,)
:::
