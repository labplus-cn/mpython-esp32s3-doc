图像摄像头教程
======================================

乐动掌控v2内置摄像头，可用于实现人脸检测、人脸识别、二维码识别等图形、图像 AI应用编程教学。

.. _lvgl_url: https://docs.lvgl.io/master
.. _lv_micropython: https://github.com/lvgl/lv_micropython


- 模型类型: 

	- **人脸检测**：用于检测人脸的模型，能同时检测多张人脸，可获取人脸位于画面中的位置，以及获取人脸中眼、鼻、嘴等关键部位坐标。

	- **人脸识别**：用于识别是否为固定人员的AI模型，同时也能检测人脸位于画面中的位置，以及获取人脸中眼、鼻、嘴等关键部位坐标。

	- **二维码识别**：用于识别二维码或条形码，能够获取到二维码内容和条形码内容。

	- **运动检测**：用于检测画面是否有人员在运动或画面是否有在移动变化。

	- **猫狗识别**：用于检测是否为猫或狗的模型，可同时识别多只猫或狗。


人脸检测
---------

在控制台打印人脸数量。

**图形化代码**

.. figure:: /_static/image/example/camera/face_detection.png
	:width: 100%
	:align: center

	图形化代码

**Python代码**

::

    # 引入相关库
    from mpython import *
    import AIcamera
    import time

    # 设置检测标记变量，用于更新数据
    isDetect = False

    # 检测回调
    def cb(_):
        global isDetect
        isDetect = True # 当检测到人脸时把标记设为真
    
    # 设置模型
    AIcamera.init(AIcamera.FACE_DETECTION, cb)

    while True:
        if isDetect: # 当标记为真表示检测到了
            # 获取检测结果并把值赋给res变量
            res = AIcamera.get_result()
            print('人脸数量：' + str(len(res)))
            isDetect = False # 清除检测标记
        time.sleep(0.1)

.. Note::

     | 获取检测结果，检测到的人脸框选位置及关键点坐标（口左角，口右角，鼻，左眼，右眼）。结果为元组类型。
     | 结构：({'box': (x1, y1, x2, y2), 'keypoint': (a0, a1, a2, a3, a4, a5, a6, a7, a8, a9)}, ...)
     | ``box`` 为人脸位置，人脸框左上角坐标(x1, y1)，右下角坐标(x2, y2)
     | ``keypoint`` 为关键点，分别为：口左角(a0, a1)、口右角(a2, a3)、鼻(a4, a5)、左眼(a6, a7)、右眼(a8, a9)
	

人脸识别
---------

在控制台打印人脸名称（假设录入了张三和李四）、人脸置信度及人脸位置。

**图形化代码**

【1】录入人脸

.. figure:: /_static/image/example/camera/face_recognition_enter.png
	:width: 400px
	:align: center

	图形化代码

【2】识别人脸

.. figure:: /_static/image/example/camera/face_recognition.png
	:width: 100%
	:align: center

	图形化代码

**Python代码**

【1】录入人脸

::

    # 引入相关库
    from mpython import *
    import AIcamera

    # 设置标记变量，用于更新数据
    isDetect = False

    # 设置模型
    AIcamera.init(AIcamera.FACE_RECOGNITION, lambda _: None)

    # 设置A键按钮回调，当按A键时录入人脸数据
    def on_button_a_pressed(_):
    # 执行录入人脸操作
    AIcamera.send_command(AIcamera.ENROLL)

    # 设置B键按钮回调，当按B键时删除人脸数据
    def on_button_b_pressed(_):
    # 执行删除人脸操作
    AIcamera.send_command(AIcamera.DELETE)

    # 绑定A/B按钮事件
    button_a.event_pressed = on_button_a_pressed
    button_b.event_pressed = on_button_b_pressed

.. Note::

     | 添加人脸或删除人脸时需要画面中检测到人脸才能操作
     | 添加人脸数据时ID会从1递增
     | 删除人脸数据时会从最后一个数据向前删除直到为0
     | 已录入的数据会保留在内存中，不会随程序停止而清空。（建议每次录入前都先删除掉所有数据）

【2】识别人脸

::

    # 引入相关库
    from mpython import *
    import AIcamera
    import time

    # 设置标记变量，用于更新数据
    isDetect = False

    # 识别回调
    def cb(_):
        global isDetect
        isDetect = True # 当识别到人脸时把标记设为真

    # 设置模型
    AIcamera.init(AIcamera.FACE_RECOGNITION, cb)

    while True:
        # 运行识别
        AIcamera.send_command(AIcamera.RECOGNIZE)
        if isDetect: # 当标记为真表示识别到了
            # 获取识别结果并把值赋给res变量
            res = AIcamera.get_result()
            face_id = res.get('id')
            if face_id == 1:
                print('这是张三')
            elif face_id == 2:
                print('这是李四')
            print('置信度：' + str(res.get('Similarity')))
            print('人脸位置：' + str(res.get('box')))
            isDetect = False # 清除识别标记
        time.sleep(0.1)

.. Note::

     | 获取识别结果，检测到的人脸ID、置信度、框选位置及关键点坐标（口左角，口右角，鼻，左眼，右眼）。结果为字典类型。
     | 结构：{'box': (x1, y1, x2, y2), 'Similarity': sim, 'keypoint': (a0, a1, a2, a3, a4, a5, a6, a7, a8, a9)}
     | ``box`` 为人脸位置，人脸框左上角坐标(x1, y1)，右下角坐标(x2, y2)
     | ``Similarity`` 为置信度
     | ``keypoint`` 为关键点，分别为：口左角(a0, a1)、口右角(a2, a3)、鼻(a4, a5)、左眼(a6, a7)、右眼(a8, a9)


二维码识别
-----------

通过识别二维码控制电灯的开和关。

**图形化代码**

.. figure:: /_static/image/example/camera/qr_recognition.png
	:width: 100%
	:align: center

	图形化代码

**Python代码**

::

    # 引入相关库
    from mpython import *
    import AIcamera
    import time

    # 设置识别标记变量，用于更新数据
    isDetect = False

    # 识别回调
    def cb(_):
        global isDetect
        isDetect = True # 当识别到二维码时把标记设为真
    
    # 设置模型
    AIcamera.init(AIcamera.CODE_SCANNER, cb)

    while True:
        if isDetect: # 当标记为真表示识别到了
            try:
                # 获取识别结果并把值赋给res变量
                qr_txt = AIcamera.get_result()
                if qr_txt == 'open':
                    print('开灯')
                elif qr_txt == 'close':
                    print('关灯')
            except: pass
            isDetect = False # 清除识别标记
        time.sleep(0.1)

.. Note::

    获取识别结果，识别结果为二维码内容。结果为字符串类型。



运动检测
-----------

检测是否有在运动，并在控制台打印运动状态

**图形化代码**

.. figure:: /_static/image/example/camera/motion_detection.png
	:width: 100%
	:align: center

	图形化代码

**Python代码**

::

    # 引入相关库
    from mpython import *
    import AIcamera
    import time

    # 设置检测标记变量，用于更新数据
    isDetect = False

    # 识别回调
    def cb(_):
        global isDetect
        isDetect = True # 当检测到运动时把标记设为真
    
    # 设置模型
    AIcamera.init(AIcamera.MOTION_DEECTION, cb)

    while True:
        if isDetect: # 当标记为真表示识别到了
            print('有在运动')
            isDetect = False # 清除识别标记
        else:
            print('没有运动')
        time.sleep(0.1)



猫狗检测
---------

在控制台打印猫脸的数量。

**图形化代码**

.. figure:: /_static/image/example/camera/cat_detection.png
	:width: 100%
	:align: center

	图形化代码

**Python代码**

::

    # 引入相关库
    from mpython import *
    import AIcamera
    import time

    # 设置检测标记变量，用于更新数据
    isDetect = False

    # 检测回调
    def cb(_):
        global isDetect
        isDetect = True # 当检测到猫脸时把标记设为真
    
    # 设置模型
    AIcamera.init(AIcamera.CAT_FACE_DETECTION, cb)

    while True:
        if isDetect: # 当标记为真表示检测到了
            # 获取检测结果并把值赋给res变量
            res = AIcamera.get_result()
            print('猫脸数量：' + str(len(res)))
            isDetect = False # 清除检测标记
        time.sleep(0.1)

.. Note::

     | 获取检测结果，检测到的猫/狗脸框选位置。结果为元组类型。
     | 结构：({'box': (x1, y1, x2, y2), ...}, ...)
     | ``box`` 为猫/狗脸位置，猫/狗脸框左上角坐标(x1, y1)，右下角坐标(x2, y2)