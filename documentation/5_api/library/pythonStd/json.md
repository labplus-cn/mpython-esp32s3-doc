# `json`{.interpreted-text role="mod"} \-- JSON 编码和解码

::: {.module synopsis="JSON 编码和解码"}
json
:::

这个模块实现了相应 `CPython`{.interpreted-text role="term"}
模块的一个子集，如下所述。有关更多信息，请参阅原始CPython文档:
[json](https://docs.python.org/3.5/library/json.html#module-json)

此模块允许在Python对象和JSON数据格式之间进行转换。

## 函数

::: function
dump(obj, stream, separators=None)

将 *obj* 串行化为 *JSON* 字符串，将其写入给定的 *stream* 。
如果指定，separators 应该是一个 (item_separator, key_separator)
元组。默认值是 (\', \', \': \')。要获得最紧凑的JSON表示，应指定 (\',\',
\':\') 以消除空白。
:::

::: function
dumps(obj, separators=None)

返回表示为JSON字符串的obj。 参数的含义与dump相同。
:::

示例:

    >>> obj = {1:2, 3:4, "a":6}
    >>> print(type(obj), obj) #原来为dict类型
    <class 'dict'> {3: 4, 1: 2, 'a': 6}
    >>> jsObj = json.dumps(obj) #将dict类型转换成str
    >>> print(type(jsObj), jsObj)
    <class 'str'> {3: 4, 1: 2, "a": 6}

::: function
load(stream)

解析给定的 *stream*
，将其解释为JSON字符串并将数据反序列化为Python对象。返回结果对象。
解析继续，直到遇到文件结尾。如果未正确形成流中的数据，则引发
`ValueError`{.interpreted-text role="exc"}
:::

::: function
loads(str)

解析 JSON 字符串并返回对象。如果字符串格式错误将引发 ValueError 异常。
:::

示例:

    >>> obj = {1:2, 3:4, "a":6}
    >>> jsDumps = json.dumps(obj)
    >>> jsLoads = json.loads(jsDumps)
    >>> print(type(obj), obj)
    <class 'dict'> {3: 4, 1: 2, 'a': 6}
    >>> print(type(jsDumps), jsDumps)
    <class 'str'> {3: 4, 1: 2, "a": 6}
    >>> print(type(jsLoads), jsLoads)
    <class 'dict'> {'a': 6, 1: 2, 3: 4}
