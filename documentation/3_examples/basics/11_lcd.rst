显示
======================================

掌控板2.0 板载1.47英寸lcd显示屏，分辨率320x172。


文本显示
----------

**显示内置思源黑体中文字库文字**

::

	from mpython import *

	display.clear(lcd.GREEN) # 清屏，把背景设置为绿色
	# 英文、葡萄牙语、日文、中文显示”你好，世界！“      
	display.DispChar("hello,world!", 0, 0, lcd.WHITE, False)
	display.DispChar("Olá, mundo!!", 0, 35, lcd.WHITE, False)
	display.DispChar("こんにちは、世界!", 0, 70, lcd.WHITE, False)
	display.DispChar("你好，世界！", 0, 105, lcd.WHITE, False)
	display.show()

.. figure:: /_static/image/example/lcd/helloworld.png
	:width: 300px
	:align: center

	显示效果


屏幕的坐标点
-------------

掌控板屏幕分辨率为 **320 x 172**，左上角坐标为 **(0, 0)**，右下角坐标为 **(320, 172)**。横向向右x坐标增大，纵坐标向下y坐标增大。

.. figure:: /_static/image/example/lcd/lcd_size.png
	:width: 400px
	:align: center


设置颜色
----------

::

	from mpython import *

	display.clear(lcd.BLACK)
	# 文字显示测试(思源黑体24号)
	display.DispChar("你好，世界！", 0, 0, lcd.RED, False)
	display.DispChar("你好，世界！", 0, 35, lcd.GREEN, False)
	display.DispChar("你好，世界！", 0, 70, lcd.BLUE, False)
	display.DispChar("你好，世界！", 0, 105, lcd.WHITE, False)
	display.show()


.. figure:: /_static/image/example/lcd/color_font.png
	:width: 300px
	:align: center

	效果图

.. Note::

	参数 ``color`` 颜色的色值为16进制数值，即 **0x0000 ~ 0xFFFF**，也可以写成 **0 ~ 65535** 。0x0000为黑色，0xFFFF为白色。格式为RGB565.

	lcd模块定义了一些常见的颜色，可直接引用：

	lcd.HOT_PINK		        0xfb56		//热情的粉红

	lcd.DEEP_PINK		        0xF8B2		//深粉色

	lcd.PURPLE		            0x8010		//紫色

	lcd.BLUE		            0x001F		//纯蓝

	lcd.MEDIUM_BLUE		        0x0019		//适中的蓝色

	lcd.DARK_BLUE		        0x0011		//深蓝色

	lcd.LIGHT_SKY_BLUE		    0x867e		//淡蓝色

	lcd.SKY_BLUE		        0x867d		//天蓝色

	lcd.DEEP_SKY_BLUE		    0x05ff		//深天蓝

	lcd.LIGHT_BLUE		        0xaebc		//淡蓝

	lcd.LIGHT_CYAN		        0xdfff		//淡青色

	lcd.CYAN		            0x07ff		//青色

	lcd.DARK_CYAN		        0x0451		//深青色

	lcd.SPRING_GREEN		    0x07ef		//春天的绿色

	lcd.LIGHT_GREEN		        0x9772		//淡绿色

	lcd.GREEN		            0x0400		//纯绿

	lcd.DARK_GREEN		        0x0320		//深绿色

	lcd.GREEN_YELLOW		    0xafe6		//绿黄色

	lcd.LIGHT_YELLOW		    0xfffb		//浅黄色

	lcd.YELLO		            0xffe0		//纯黄

	lcd.GOLD		            0xfea0		//金

	lcd.ORANGE		            0xfd20		//橙色

	lcd.DARK_ORANGE		        0xfc60		//深橙色

	lcd.RED			            0xf800		//纯红

	lcd.DARK_RED		        0x8800		//深红色

	lcd.GUI_PINK		        0xfdf9		//粉红

	lcd.BROWN		            0xa145		//棕色

	lcd.WHITE		            0xFFFF		//纯白

	lcd.LIGHT_GRAY		        0xd69a		//浅灰色

	lcd.DARK_GRAY	            0xad55		//深灰色

	lcd.GRAY		            0x8410		//灰色

	lcd.BLACK		            0x0000		//纯黑

内置数码管字体
--------------------

内部内置了其它几种字体，用于显示数字及拉丁字母：

digiface_16 digiface_21 digiface_30 digiface_44 digiface_it_30 digiface_it_42

dvsm_16 dvsm_21 dvsmb_16 dvsmb_21

::

	from mpython import *
	import font.dvsm_21 as dvsm_21
	import font.digiface_44 as digiface_44

	display.clear(lcd.BLACK)
	# font文件夹下内置的数码管及dvssm字体显示测试,字体由font-to-py工具生成
	display.DispChar_font(dvsm_21, "hello,world", 50, 40, lcd.RED)
	display.DispChar_font(digiface_44, "12:34", 50, 70, lcd.BLUE)
	display.show()	

.. figure:: /_static/image/example/lcd/font_digital.png
	:width: 300px
	:align: center

	效果图

基本形状绘制
-------------------

display继承framebuf,framebuf实现以下功能
1. 创建图形缓存区
2. 图形绘制：点、线、圆...
3. png图片解码
4. 清屏（背景填充）
5. 内置文本显示

以下为基本绘图示例。

::

	from mpython import *

	display.clear()
	# frame_colorbuf 绘图API测试
	# 水平线和垂直线
	display.vline(10, 10, 152, lcd.BLUE)
	display.hline(10, 10, 300, lcd.BLUE)
	display.vline(310, 10, 152, lcd.BLUE)
	display.hline(10, 162, 300, lcd.BLUE)
	# 任意两点线段
	display.line(0, 0, 320, 172, lcd.WHITE)
	display.line(320, 0, 0, 172, lcd.WHITE)
	# 矩形和填充矩形
	display.rect(35, 35, 90, 100, lcd.WHITE)
	display.fill_rect(45, 50, 70, 70, lcd.RED)
	# 圆和填充圆
	display.circle(160, 86, 35, lcd.WHITE)
	display.fill_circle(160, 86, 25, lcd.RED)     
	# 三角形和填充三角形
	display.triangle(200, 50, 280, 50, 240, 130, lcd.WHITE)
	display.fill_triangle(210, 60, 270, 60, 240, 110, lcd.RED)
	# 圆角矩形
	display.RoundRect(30, 21, 260, 140, 11, lcd.BLUE)

	display.show()

.. figure:: /_static/image/example/lcd/draw.png
	:width: 300px
	:align: center

	效果图

显示图片
---------

掌控板支持png图片解码并显示，内置了一些常用png格式图标，以索引的方式调用。同时也支持解码用户放在文件系统中的png图片。

**【1】显示内置图标**
::

	from mpython import *

	display.clear(lcd.WHITE)
	w, h, buff = display.decode_png_internal(70) # 解码索引号为70的内置图片
	fb = framebuf.FrameBuffer(buff, w, h, framebuf.RGB565) # 用解码出的图片创建一个framebuf缓存对象
	display.blit(fb, 0, 0) # 把fb缓存图片数据写入显示（0,0)位置，支持裁剪，超出显示区会截掉

	display.show()
	
.. figure:: /_static/image/example/lcd/draw_internal_icon.png
	:scale: 50 %
	:align: center

	效果图

**【2】显示文件系统中图片文件**
::

	from mpython import *

	display.clear(lcd.GREEN)
	img = Image()
	# 测试文件(大小320*172像素),放入文件系统，加载png文件，生成图片framebuffer对象
	fb = img.load('1.png')
	display.blit(fb, 0, 0) # framebuffer图片刷入显示frambuffer，超出范围会被裁剪。
	display.show()

.. figure:: /_static/image/example/lcd/draw_png.png
	:scale: 50 %
	:align: center

	效果图

进度条
---------------------

::

	from mpython import *

	gui = UI()

	display.clear(lcd.BLACK)
	# 位置(10,30),长180，宽20，进度条位置20%，颜色红色
	gui.ProgressBar(10, 30, 180, 20, 20, lcd.RED)
	# 位置(200,0),长160，宽20，进度条位置50%，颜色蓝色
	gui.stripBar(200, 0, 20, 160, 50, dir=0, color=lcd.BLUE)
	display.show()

.. figure:: /_static/image/example/lcd/progress_bar.png
	:scale: 50 %
	:align: center

	效果图

二维码
---------------------

::

	from mpython import *

	gui = UI()

	display.clear(lcd.BLACK)
	# 位置(100, 10)显示字字符串的二维码，显示比例设为4
	gui.qr_code("Hello, mPython!", 100, 10, scale=4)
	display.show()

.. figure:: /_static/image/example/lcd/qr_code.png
	:scale: 50 %
	:align: center

	效果图

图表-柱状图
---------------------

::

	from mpython import *
	
	# 创建图表，位置(80, 50),值范围(0-10),数据颜色表（红，绿，蓝，白）
	chart = MicroChart(x0 = 80, y0 = 50, val_max = 10, data_colors=[lcd.RED, lcd.GREEN, lcd.BLUE, lcd.WHITE])
	display.clear()
	# 给出样本数据
	bar_data = [[3, 8, 5, 10], [6, 4, 9, 7], [2, 7, 4, 9]]
	chart.draw_bar_chart(bar_data)
	display.show()

.. figure:: /_static/image/example/lcd/chart_bar.png
	:scale: 50 %
	:align: center

	效果图

图表-折线图
---------------------

::

	from mpython import *
	import audio

	# 构建一个图表，位置（40，40）
	chart = MicroChart(x0 = 40, y0 = 40)
	# 显示数据100个，图纸是二维数组，可以显示多组折线图，这里只显示了一组数据。
	line_data = [[0]*100] 

	display.clear(lcd.BLACK) # 清屏
	display.show()
	i = 0
	chart.draw_axis() # 绘制轴
	while True:
		display.clear()
		value = audio.loudness()  # 获取声音响度值
		# 数扰移位，以实现数据动态变化
		for j in range(99):
			line_data[0][j] = line_data[0][j+1]
		line_data[0][99] = value 
		# 绘制图表
		chart.draw_line_chart(line_data, show_grid=False)
		i = (i + 1) % len(line_data[0])
		display.show()
		time.sleep_ms(50)

.. figure:: /_static/image/example/lcd/chart_line.png
	:scale: 50 %
	:align: center

	效果图

表格
---------------------

::

	from mpython import *

	# 1. 创建表格对象     
	table = MicroExcelTable()
	# table = MicroExcelTable(y0=10, cols=2, rows=3, cell_width=100,)

	display.clear()
	# 2. 绘制表头（仅调用一次）
	col_headers = ["温度", "湿度", "光线值"]   # 列表头
	row_headers = ["位置1", "位置2", "位置3", "位置4"] # 列表头
	# col_headers = ["温度", "湿度"]   # 列表头
	# row_headers = ["位置1", "位置2", "位置3"] # 列表头
	table.draw_headers(col_headers, row_headers)

	# 3. 初始化数据（整区更新）
	table.update_data([
		["25℃", "60%", "200"],
		["26℃", "59%", "700"],
		["24℃", "61%", "1210"],
		["25℃", "61%", "120"],
	])

	# table.update_data([
	#     ["25℃", "60%"],
	#     ["26℃", "59%"],
	#     ["24℃", "61%"],
	# ])

	display.show()

	# 4. 模拟实时更新单个单元格（核心演示）
	count = 0
	while True:
		# 仅更新第0行第0列的温度值
		table.update_cell(row=0, col=0, text=f"{(25+count) % 99}℃")
		# 仅更新第2行第3列的电量值
		table.update_cell(row=2, col=2, text=f"{count % 1024}")
		display.show()
		count += 1
		time.sleep(1)

.. figure:: /_static/image/example/lcd/excel_table.png
	:scale: 50 %
	:align: center

