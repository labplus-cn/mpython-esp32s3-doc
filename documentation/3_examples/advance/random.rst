随机数
======================================

有时我们需要做些随机行为或生产随机数。这时你可以使用 :ref:`random<random>` 模块。

例如，以下是如何在oled显示屏上随机显示名称::

  from lv_gui import *
  from mpython import *
  import random

  gui = GUI()

  names = ["Mary", "Yolanda", "Damien", "Alia", "Kushal", "Mei Xiu", "Zoltan" ]

  gui.fill(type=0)
  gui.draw_label(text=str(random.choice(names)), row=1, color=0xffffff, wrap=False)
  gui.update()


列表（names）包含七个定义为字符串的名称。random.choice方法将names列表作为参数并返回随机选择的项目。

你能修改列表以包含你自己的名字吗？

随机显示数字
---------

随机数非常有用。它们在游戏中很常见。为什么我们还有骰子？

MicroPython附带了几个有用的随机数方法。这是如何制作一个简单的骰子::

  from lv_gui import *
  from mpython import *
  import random

  gui = GUI()

  gui.fill(type=0)
  gui.draw_label(text=str(random.randint(1,6)), row=1, color=0xffffff, wrap=False)
  gui.update()


.. Note::

  每次重启掌控板时，它都会显示一个介于1和6之间的数字。``randint()`` 返回的是整形，我们需要使用 ``str()`` 将整形转为字符串(例如，6 -> "6")。
  ``gui.draw_label()`` 将随机数写入屏幕lcd。

假如你想设置随机范围或递增基数，你可以使用random.randrange()::

  from lv_gui import *
  from mpython import *
  import random

  gui = GUI()

  gui.fill(type=0)
  gui.draw_label(text=str(random.randrange(0,10,2)), row=1, color=0xffffff, wrap=False)
  gui.update()


.. Note::

  random.randrange(start, end, step)。``start`` 为随机数开始值，``end`` 为随机数结束值，step为递增基数。
  以上例子是随机显示(0,10)范围的偶数。

有时您需要带小数点的数字。你可以使用 ``random.random`` 方法生成0.0到1.0的随机浮点数。如果你需要较大的随机浮点数加的结果 ``random.uniform`` ::

  from lv_gui import *
  from mpython import *
  import random

  gui = GUI()

  gui.fill(type=0)
  gui.draw_label(text=str(random.random()), row=1, color=0xffffff, wrap=False)
  gui.draw_label(text=str(random.uniform(1,20)), row=2, color=0xffffff, wrap=False)
  gui.update()


随机种子
-------

MicroPython中的随机数其实是一个稳定算法得出的稳定结果序列，而不是一个随机序列。 seed就是这个算法开始计算的第一个值。
所以就会出现只要seed是一样的，那么后续所有“随机”结果和顺序也都完全一致。

指定随机数种子，通常和其他随机数生成函数搭配使用

有时您希望具有可重复的随机行为：可重现的随机源。这就像说每次掷骰子时你需要相同的五个随机值。

