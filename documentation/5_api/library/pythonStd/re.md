# `re`{.interpreted-text role="mod"} \-- 正则表达式

::: {.module synopsis="正则表达式"}
re
:::

这个模块实现了相应 `CPython`{.interpreted-text role="term"}
模块的一个子集，如下所述。有关更多信息，请参阅原始CPython文档:
[re](https://docs.python.org/3.5/library/re.html#module-re)

该模块实现了正则表达式操作。支持的正则表达式语法是CPython `re`
模块的子集（实际上是POSIX扩展正则表达式的子集）。

支持的运算符和特殊序列是:

`'.'`

:   匹配任何字符。

`'[]'`

:   匹配字符集。支持单个字符和范围，包括否定集（例​​如 `[^a-c]` ）。

`'^'`

:   匹配字符串的开头。

`'$'`

:   匹配字符串的结尾。

`'?'`

:   匹配零个或前一个子模式之一。

`'*'`

:   匹配前一个子模式的零个或多个。

`'+'`

:   匹配前一个子模式中的一个或多个。

`'??'`

:   非贪婪版本?，匹配零或一，偏好为零。

`'*?'`

:   非贪婪版本\*，匹配零或更多，与最短匹配的偏好。

`'+?'`

:   非贪婪版本+，匹配一个或多个，与最短匹配的偏好。

`|`

:   匹配此运算符的左侧或右侧子模式。

`(...)`

:   分组。每个组都在捕获（它捕获的子字符串可以通过
    [match.group()]{.title-ref} 方法访问）。

`\d`

:   匹配数字。相当于 `[0-9]` 。

`\D`

:   匹配非数字。相当于 `[^0-9]` 。

`\s`

:   匹配空白。相当于 `[ \t-\r]`

`\S`

:   匹配非空白。相当于 `[^ \t-\r]`

`\w`

:   匹配\"单词字符\"（仅限ASCII）。相当于 `[A-Za-z0-9_]` 。

`\W`

:   匹配非\"单词字符\"（仅限ASCII）。相当于 `[^A-Za-z0-9_]` 。

`\`

:   转义字符。除了上面列出的那些之外，反斜杠后面的任何其他字符都是字面意思。例如，`\*`
    等同于文字 `*`（不作为 `*` 运算符）。 需要注意的是 `\r` ，`\n`
    等没有特殊处理，并且将相当于文字字母 `r` ，`n`
    等。由于这一点，不推荐使用原始Python字符串（`r""`）为正则表达式。
    例如，`r"\r\n"` 当用作正则表达式时相当于 `"rn"`
    。要匹配CR后跟LF的字符，请使用 `"\r\n"` 。

**不支持**:

- 计算重复次数 (`{m,n}`)
- 命名组 (`(?P<name>...)`)
- 非捕获组 (`(?:...)`)
- 更高级的断言 (`\b`, `\B`)
- 特殊字符逃脱 ，例如 `\r` ，`\n` 使用Python自己的转义
- 等等

示例:

    import re

    # As re doesn't support escapes itself, use of r"" strings is not
    # recommended.
    regex = re.compile("[\r\n]")

    regex.split("line1\rline2\nline3\r\n")

    # Result:
    # ['line1', 'line2', 'line3', '', '']

## 函数

::: function
compile(regex_str\[, flags\])

编译正则表达式，返回 [regex \<regex\>]{.title-ref} 对象。
:::

::: function
match(regex_str, string)

编译 *regex_str* 并匹配 *string* 。匹配始终从字符串中的起始位置开始。
:::

::: function
search(regex_str, string)

编译 [regex_str]{.title-ref} 并在字符串中搜索它。与 `match`
此不同，这将搜索匹配正则表达式的第一个位置的字符串（如果正则表达式已锚定，则仍可能为0）。
:::

::: function
sub(regex_str, replace, string, count=0, flags=0, /)

编译 regex_str 并在 string 中搜索它，用 replace
替换所有匹配项，并返回新字符串。 replace
可以是字符串或函数。如果是字符串，则可以使用形式为 \<number\> 和
g\<number\> 的转义序列来扩展到相应的组（或未匹配组的空字符串）。 如果
replace 是函数，则它必须接受单个参数（匹配项）并应返回替换字符串。
如果指定了 count 且非零，则替换将在此多次替换后停止。flags 参数被忽略。
注意：此函数的可用性取决于MicroPython端口。
:::

::: data
DEBUG

标记值，显示有关已编译表达式的调试信息。
（可用性取决于MicroPython端口。）
:::

## Regex对象

编译后的正则表达式。此类的实例使用 re.compile() 创建。

::: method
regex.match(string\[, pos\[, endpos\]\])
:::

::: method
regex.search(string\[, pos\[, endpos\]\])
:::

::: method
regex.sub(replace, string, count=0, flags=0, /)

类似于模块级函数 match()、search() 和 sub()。
如果相同的正则表达式应用于多个字符串，使用方法（更）更高效。
可选的第二个参数 pos
给出字符串中搜索开始的索引；默认为0。这与切片字符串并不完全等效；\'\^\'
模式字符在字符串的实际开头和换行符之后的位置匹配，但不一定在搜索开始的索引处匹配。
可选参数 endpos 限制字符串搜索的距离；就好像字符串是 endpos
字符长，所以只会搜索从 pos 到 endpos - 1 的字符以寻找匹配项。
:::

::: method
regex.split(string, max_split=-1, /)

使用正则表达式分割字符串。如果给出
max_split，它指定要执行的最大分割数。返回字符串列表（如果指定，最多可能有
max_split+1 个元素）。
:::

## Match对象

由 match() 和 search() 方法返回并传递给 sub() 中的替换函数的匹配对象。

::: method
match.group(index)

返回匹配的（子）字符串。index
为0表示整个匹配，1及以上表示每个捕获组。仅支持数字组。
:::

::: method
match.groups()

返回包含匹配组的所有子字符串的元组。
注意：此方法的可用性取决于MicroPython端口。
:::

::: method
match.start(\[index\])
:::

::: method
match.end(\[index\])

返回原始字符串中匹配的子字符串组的开始或结束的索引。index
默认为整个组，否则它将选择一个组。
注意：这些方法的可用性取决于MicroPython端口。
:::

::: method
match.span(\[index\])

返回 2 元组 (match.start(index), match.end(index))。
注意：此方法的可用性取决于MicroPython端口。
:::
