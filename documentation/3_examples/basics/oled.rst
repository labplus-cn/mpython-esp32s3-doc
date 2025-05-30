显示
======================================

掌控板板载1.3英寸OLED显示屏，分辨率128x64。采用 `Google Noto Sans CJK <http://www.google.cn/get/noto/help/cjk/>`_ 开源无衬线字体字体。字体高度16像素点。支持简体中文，繁体中文，日文和韩文语言。


.. Hint::

  oled为 ``machine.framebuf`` 衍生类，所以继承framebuf的方法，详细使用可查阅  :meth:`framebuf`。


文本显示
-------

使用前，须导入mpython模块::

  from mpython import *

`hello,world` 文本显示::

  # 便于看到字符是如何在显示屏上显示的,模式选择像素点翻转模式
  oled.DispChar('hello,world!',0,0,mode=TextMode.rev)
  # 默认模式下,字符背景像素点熄灭
  oled.DispChar('hello,world!',0,16,mode=TextMode.normal)
  oled.show()

.. figure:: /../images/tutorials/display_char_pixel.png
   :width: 500px
   :align: center

   字符像素点是如何在掌控板屏幕上显示


- DispChar(str,x,y)函数可以将左上角为坐标的文本将写入FrameBuffer。``str`` 为显示文本内容，支持简体中文，繁体中文，日文和韩文语言。``x`` ``y`` 为oled显示
  起始xy坐标。`oled.show()` 为将FrameBuffer送至oled刷新并显示屏幕。
- 采用Noto Sans CJK 16像素等高,不等宽字体。不同字符,宽度会有所不一样,如上图所示。


.. literalinclude:: /../../examples/display/helloworld.py
    :caption: 在OLED显示屏上显示hello world的中文或其他语言文本:
    :linenos:


.. figure:: /../images/掌控-正面.png
    :align: center

    多语言 hello,world 显示


::

  oled.fill(0)
  oled.show()

除了可以清空显示屏，还可以将整屏像素点亮::

  oled.fill(1)  
  oled.show()

.. Note::

  fill() 为填充整个FrameBuffer区域。

OLED显示屏还支持设置屏幕的亮度::

  oled.contrast(brightness)

.. Note::

  brightness 表示亮度，取值范围为0~255。


基本形状绘制
-------

.. literalinclude:: /../../examples/display/drawline.py
    :caption: 例：绘制线条。
    :linenos:


.. image:: /../images/tutorials/drawline.gif
   :scale: 100 %
   :align: center


OLED可绘制一些点、直线、矩形等形状。

像素点显示::
                       
  oled.pixel(50,0,1)   #将(50,0)像素点置为1，点亮
  oled.show()          #刷新显示屏

.. Note::

  oled.pixel(x, y, [c] ) 可以显示像素点， ``x`` ， ``y`` 为点坐标(x,y)。``c`` 为颜色值，当为1时，点亮像素点，为0则否。当如果未给出c，则获取指定像素的颜色值。
  如果给出c，则将指定的像素设置为给定的颜色。


绘制线::

  oled.hline(0,1,20,1)  #画水平线,起始点坐标(0,1),线长20
  oled.show()
  oled.vline(10,10,20,1)  #画垂直线,起始点坐标(10,10),线长20
  oled.show()
  oled.line(15,15,80,20,1)  #画起始坐标(15,15),终点坐标(80,20)方向的线
  oled.show()

.. Note::

  * oled.hline(x, y, w, c ) 可以绘制水平线，``x`` ， ``y`` 为点坐标(x,y)， ``w`` 为线宽，``c`` 为颜色值。
  * oled.vline(x, y, l, c ) 可以绘制垂直线，方法同上。
  * oled.line(x1, y1, x2, y2, c) 可以绘制任意方向的线，起始坐标(x1, y1)，终点坐标(x2, y2)， ``c`` 为颜色值。


绘制空心/实心矩形::

  oled.rect(60,25,30,25,1)   #绘制起始坐标(60, 25)，宽30，高25的矩形  
  oled.show()
  oled.fill_rect(100,25,20,25,1)   #绘制起始坐标(100, 25)，宽20，高25填充满颜色的矩形  
  oled.show()

.. Note::

  * oled.rect(x, y, w, h, c)用于绘制矩形外框。起始坐标为(x, y),宽度 ``w`` , 高度 ``h`` 的矩形外框，``c`` 为颜色值。
  * oled.fill_rect(x, y, w, h, c)用于绘制填充颜色的矩形，方法与rect()相同。不同于rect()只绘制矩形外框。

绘制弧角矩形::

  oled.RoundRect(40, 20, 50, 30, 5, 1)   #绘制起始坐标(40, 25),宽50,高30,圆弧角半径为5的弧角矩形
  oled.show()

.. Note::

  oled.RoundRect(x, y, w, h, r, c)用于绘制弧角矩形。起始坐标为(x, y)，宽度 ``w`` ， 高度 ``h`` ，圆弧角半径 ``r`` 的矩形外框，``c`` 为颜色值。
 
更多OLED显示屏操作及形状绘制请查阅 :ref:`oled对象<oled>` 。


显示图片
-------

首先我们需要将图像处理为大小128*64，颜色深度为1或者就是黑白模式的bmp格式。您可以使用Photoshop或者其他的图像处理软件。

接下来是使用取模工具对图片进行取模。网上有PCtoLCD、lcd image converter等取模软件，可根据自己喜好自行选择。以下使用的是 :download:`Img2Lcd工具 </../docs/tools/Image2Lcd.zip>` 。

* 步骤1.导入128x64，bmp格式图片
* 步骤2.选择参数，输出数据类型[C语言数组]、  扫描模式[水平扫描]、输出灰度[单色]、宽高[128*64]
* 步骤3.点击保存，自动生成取模数据。

.. image:: /../images/tutorials/image2lcd.png


将取模数据赋值给bmp数组中，然后显示在OLED显示屏上。

.. literalinclude:: /../../examples/display/chinamap.py
    :linenos:

.. image:: /../images/tutorials/earth.png
  :scale: 50 %
  :align: center

将取模数据赋值给bmp数组后，绘制图片至OLED显示屏上::

  oled.bitmap(0, 0, bmp, 128, 64, 1)
  oled.show()

.. Note::

  oled.bitmap(x, y, bitmap, w, h, c) 可以绘制bitmap图案，``x`` 、``y`` 为左上角起点的坐标x、y，``bitmap`` 为图案btyearray字节数组名称，``w`` 为图案宽度，``h`` 为图案高度，``c`` 为颜色值，``1`` 时像素点亮，``0`` 时像素点灭。


动态显示
-------

结合上面静止帧的显示，可以将要显示的动态图片分割成每帧，送至OLED显示屏上逐帧显示，这样就有动态效果啦！

与上面使用bmp格式图片不同。本次使用pbm(Portable BitMap)格式图片，你可以使用Photoshop转换至pbm格式。

pbm数据格式::

  P4
  #CREATOR：GIMP PNM过滤器版本1.1
  128 64
  <数据>

pbm数据格式的前三行定于为图像标注。然后才是图像数据。第一行表示图像格式，第二行是注释，通常是用于创建它的程序。第三行是图像尺寸。
后面的才是我们需要的图像数据。数据存储每像素bit流，``1`` 表示像素点打开，``0`` 表示像素点关闭。

:download:`动态显示素材下载 </../../examples/display/素材/scatman.zip>`

首先将预先准备好的每帧的pbm图片上传至掌控板的文件系统的根目录下。

.. literalinclude:: /../../examples/display/scatman.py
    :caption: 逐帧读取图像数据流并在OLED显示屏上显示出来:
    :linenos:

.. image:: /../images/tutorials/scatman.gif
  :align: center


导入mpython和framebuf模块::

  from mpython import *
  import framebuf

用二进制只读格式打开每一帧图片::

  with open('scatman.%s.pbm' % n, 'rb') as f:
      f.readline()       # 图像格式
      f.readline()       # 注释
      f.readline()       # 图像尺寸
      data = bytearray(f.read())
  fbuf = framebuf.FrameBuffer(data, 128, 64, framebuf.MONO_HLSB)
  images.append(fbuf)     #将每帧数据赋值到列表


在程序中使用 ``file.read()`` 逐帧读取图像数据流。注意，前三行不是我们需要的数据，使用 ``readlines()`` 将它舍弃。每帧数据流创建FrameBuffer对象，将所有帧缓存储存至images列表。

.. Note::

  open(file, mode) 用于打开一个文件，并返回文件对象。``file`` 为文件名，``mode`` 为文件打开模式，``rb`` 以二进制格式打开一个文件用于只读，一般用于非文本文件如图片等。

.. Note::
 
  framebuf.FrameBuffer(buffer, width, height, format) 可以构建帧缓存对象， ``buffer`` 为缓存区数据，``width`` 为图片宽度，``height`` 为图片高度，``format`` 为FrameBuffer的格式，即对应图片取模时数据输出的扫描模式：``framebuf.MONO_HLSB`` 为水平方向；``framebuf.MONO_VLSB`` 为垂直方向。

对存储好的帧缓存逐帧显示至OLED显示屏::

  oled.blit(i, 0, 0)
  oled.show()

.. Note::

 oled.blit(fbuf, x, y) 使用OLED显示图片帧，``fbuf`` 为FrameBuffer对象，``x`` 、``y`` 为起始点的坐标x、y。

























