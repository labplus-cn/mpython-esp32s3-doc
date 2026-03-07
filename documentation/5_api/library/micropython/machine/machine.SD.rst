.. currentmodule:: machine
.. _machine.SD:

类 SD -- 安全数字存储卡
======================================

.. warning::

    这是一个非标准类，仅在cc3200端口可用。

SD卡类允许配置和启用WiPy的存储卡模块，并自动将其挂载为文件系统的 ``/sd`` 部分。
有几种引脚组合可用于将SD卡插槽连接到WiPy，使用的引脚可以在构造函数中指定。
请查看引脚分配和备用功能表，了解有关可重新映射用于SD卡的引脚的更多信息。

示例用法::

    from machine import SD
    import vfs
    # 必须传递clk、cmd和dat0引脚以及它们各自的备用功能
    sd = machine.SD(pins=('GP10', 'GP11', 'GP15'))
    vfs.mount(sd, '/sd')
    # 执行正常的文件操作

构建对象
------------

.. class:: SD(id, ...)

   创建SD卡对象。参见init()方法获取初始化参数。

方法
-------

.. method:: SD.init(id=0, pins=('GP10', 'GP11', 'GP15'))

   启用SD卡。为了初始化卡，请提供一个3元组：
   ``(clk_pin, cmd_pin, dat0_pin)``。

.. method:: SD.deinit()

   禁用SD卡。
