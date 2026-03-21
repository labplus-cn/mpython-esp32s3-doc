# `btree`{.interpreted-text role="mod"} \-- 简单的 BTree 数据库

::: {.module synopsis="简单的 BTree 数据库"}
btree
:::

`btree`
模块使用外部存储（磁盘文件，或在一般情况下为随机访问流）实现简单的键值数据库。
键存储在数据库中并保持排序，除了通过键值进行高效检索外，数据库还支持高效的有序范围扫描（检索给定范围内键的值）。
在应用程序接口方面，B树数据库尽可能以与标准 dict
类型相似的方式工作，一个显著区别是键和值都必须是类字节对象（因此，
如果您想要存储其他类型的对象，需要首先将它们序列化为 str 或 bytes
或其他支持缓冲区协议的类型）。

该模块基于著名的 BerkeleyDB 库，版本 1.xx。

示例:

    import btree

    # First, we need to open a stream which holds a database
    # This is usually a file, but can be in-memory database
    # using io.BytesIO, a raw flash partition, etc.
    # Oftentimes, you want to create a database file if it doesn't
    # exist and open if it exists. Idiom below takes care of this.
    # DO NOT open database with "a+b" access mode.
    try:
        f = open("mydb", "r+b")
    except OSError:
        f = open("mydb", "w+b")

    # Now open a database itself
    db = btree.open(f)

    # The keys you add will be sorted internally in the database
    db[b"3"] = b"three"
    db[b"1"] = b"one"
    db[b"2"] = b"two"

    # Assume that any changes are cached in memory unless
    # explicitly flushed (or database closed). Flush database
    # at the end of each "transaction".
    db.flush()

    # Prints b'two'
    print(db[b"2"])

    # Iterate over sorted keys in the database, starting from b"2"
    # until the end of the database, returning only values.
    # Mind that arguments passed to values() method are *key* values.
    # Prints:
    #   b'two'
    #   b'three'
    for word in db.values(b"2"):
        print(word)

    del db[b"2"]

    # No longer true, prints False
    print(b"2" in db)

    # Prints:
    #  b"1"
    #  b"3"
    for key in db:
        print(key)

    db.close()

    # Don't forget to close the underlying stream!
    f.close()

## 函数

::: function
open(stream, \*, flags=0, pagesize=0, cachesize=0, minkeypage=0)

从随机存取的
stream（类似一个打开的文件）中打开一个数据库。所有其他的参数都是可选的，且都只为关键字，并允许对数据库操作的高级参数进行调整（大多数用户并不会需要这个）:

- *flags* - 当前未使用。
- *pagesize* -
  B树中用于节点的页面大小。可接受范围为512-65536。如果为0，将使用特定于端口的默认值，针对端口的内存使用和/或性能进行了优化。
- *cachesize* -
  以字节计的建议内存缓存大小。对于内存充足的板，使用更大值可能会提高性能。
  缓存策略如下：整个缓存不会一次性分配；相反，访问数据库中的新页面会为其分配内存缓冲区，直到达到
  cachesize 指定的值。 然后，这些缓冲区将使用
  LRU（最近最少使用）策略进行管理。如果需要，仍可能分配更多缓冲区（例如，如果数据库包含大键和/或值）。
  分配的缓存缓冲区不会被回收。
- *minkeypage* - 每个页面存储的键的最小数量。默认值为0等同于2。

返回一个B树对象，该对象实现一个字典协议（方法集）和下述的一些附加方法。
:::

## 方法

::: method
btree.close()

关闭数据库。处理结束时关闭数据库是强制性的，因为某些未写入的数据可能仍留在缓存中。注意：这并不会关闭随数据库打开的基础流，基础流应单独关闭（这也是强制性的，以确保从缓冲区中刷新的数据进入底层存储）。
:::

::: method
btree.flush()

将缓存中的任何数据刷新到底层流。
:::

::: method
btree.\_\_getitem\_\_(key) btree.get(key, default=None, /)
btree.\_\_setitem\_\_(key, val) btree.\_\_delitem\_\_(key)
btree.\_\_contains\_\_(key)

标准字典方法。
:::

::: method
btree.\_\_iter\_\_()

B树对象可被直接迭代（与字典相似）以按顺序访问所有键。
:::

::: method
btree.keys(\[start_key\[, end_key\[, flags\]\]\])
btree.values(\[start_key\[, end_key\[, flags\]\]\])
btree.items(\[start_key\[, end_key\[, flags\]\]\])

这些方法类似于标准字典方法，但也可使用可选参数来迭代一个键子范围，而不是整个数据库。
注意：这三种方法中， *start_key* 和 *end_key* 参数都代表键值。例如，
values() 方法将迭代与给定键范围对应的值。 *start_key* 为 None
表示\"从首个键开始\"，无 *end_key* 或其值为 None
则表示\"直到数据库结束\"。 默认情况下，范围包括 *start_key* ，而不包括
*end_key* ，您可以通过传递 btree.INCL 的标记来将 *end_key*
包括在迭代中。 您可以通过传递 btree.DESC
的标记来按照键的降序方向进行迭代。标记值可以按位或组合使用。
:::

## 常量

::: data
INCL

keys(), values(), items() 方法的标记，指定扫描应该包含结束键。
:::

::: data
DESC

keys(), values(), items() 方法的标记，指定扫描应按照键的降序方向进行。
:::
