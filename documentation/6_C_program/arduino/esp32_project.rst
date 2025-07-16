4.2.3 esp32项目创建
-----------------------

1.新建项目
~~~~~~~~~~~~~~~~~

1.1 **点击左侧栏platformio图标， 打开PIO Home，如下图依次点击：**

.. figure:: /_static/image/c_program/prj_new.png
    :align: center
    :width: 1066
|
1.2 **填写项目信息： Project Name: 自定义名称（如esp32_demo）**

    * Board: 选择 mpython_esp32s3_v3
    * Framework: 选择 Arduino
    * Location: 选择项目保存路径

.. figure:: /_static/image/c_program/prj_name.png
    :align: center
    :width: 500
|
完成后点finish按钮。

2.项目结构说明
~~~~~~~~~~~~~~~~~

esp32_demo/

| ├── .pio/
| ├── include/        # 头文件
| ├── lib/            # 第三方库
| ├── src/            # 源代码
| │   └── main.cpp    # 主程序文件
| ├── test/           # 测试代码
| └── platformio.ini  # 项目配置文件

3.编写代码示例（Arduino框架）

修改main.cpp文件，内容如下：

.. literalinclude:: /_static/examples/c_program/helloworld.c
    :caption: 示例-hello,world.
    :linenos:


4.编译项目

点击底部工具栏的 ✓ 图标（或 Ctrl+Alt+B）

.. figure:: /_static/image/c_program/prj_build.png
    :align: center
    :width: 800
|
5.上传代码

点击底部工具栏的 → 图标（或 Ctrl+Alt+U）

.. figure:: /_static/image/c_program/prj_upload.png
    :align: center
    :width: 800


|
.. Attention:: 如果不能上传，同时按住A B键，再按下复位键，再松开A B键，可强制板子进入烧录态，再执行以上烧录操作。

6.运行结果

- * 点击底部工具栏的 串口监视器图标（或 Ctrl+Shift+M）
- * 默认波特率：115200

.. figure:: /_static/image/c_program/prj_monitor.png
    :align: center
    :width: 800
|
代码正常运行，则会在串口控制台不断输出："hello,world."。
