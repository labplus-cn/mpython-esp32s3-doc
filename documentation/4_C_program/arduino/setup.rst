4.2.2 开发环境搭建
--------------------

安装VSCode
~~~~~~~~~~~~~~~~~

从官网:https://code.visualstudio.com/ 下载并安装最新版VSCode。

安装PlatformIO插件
~~~~~~~~~~~~~~~~~~~~

1.打开VSCode

2.进入扩展市场（快捷键 Ctrl+Shift+X 或点击左侧扩展图标），搜索 “PlatformIO IDE” 并安装。

.. figure:: /_static/image/c_program/install.png
    :align: center
    :width: 1066


3.安装完成后重启VSCode。

4.安装完成后，左侧栏有platformio图标，点选，可进入开发页面。

.. figure:: /_static/image/c_program/create.png
    :align: center
    :width: 1066


安装Python 3.7+
~~~~~~~~~~~~~~~~~

●下载安装程序

访问官网:https://www.python.org/downloads/，将鼠标移动到 “Downloads” 菜单，选择 “Windows” 菜单项。根据系统是 32 位还是 64 位，选择带有 “x86” 或 “x86-64” 字样的压缩包，通常建议下载最新的稳定版本。

●运行安装程序

双击下载好的安装文件，在安装向导初始界面，务必勾选 “Add Python 3.x to PATH” 选项，这会自动配置环境变量。也可点击 “Customize installation” 进行自定义安装，选择安装组件和路径，然后点击 “Install” 开始安装。

●验证安装

安装完成后，打开命令提示符（CMD），输入 “python” 或 “python -V”，若能看到 Python 的交互式解释器启动或显示版本号，则表示安装成功。


platformIO配置掌控板V3.0
~~~~~~~~~~~~~~~~~~~~~~~~~~

下载
* :download:`掌控板V3 platformio配置文件 </_static/examples/c_program/mpython_V3_for_platformio.rar>`

1. 解压下载的 mpython_V3_for_platformio.rar 文件
2. 找到并复制 mpython_esp32s3_r8n16.json 文件
3. 将其粘贴到 C:/Users/[用户名]/.platformio/platforms/espressif32/boards 目录下
4. 找到并复制 mpython_V3_ESP32S3 文件夹
5. 将其粘贴到 C:/Users/[用户名]/.platformio/packages/framework-arduinoespressif32/variants 目录下

.. Note:: 请将[用户名]替换为你的Windows用户名。如果找不到对应文件夹，请先参考4.2.3章节，创建一个ESP32项目先。



