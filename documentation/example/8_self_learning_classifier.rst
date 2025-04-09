自学习分类
==============

训练保存模型
-----------
例程::

    from mpython import *
    import smartcamera_new as smartcamera

    smart_camera = smartcamera.SmartCamera(tx=Pin.P16, rx=Pin.P15)
    ID = ['class1', 'class2']
    smart_camera.self_learning_classifier_init(3, 15, 11, 1)
    smart_camera.slc.add_class_img()
    smart_camera.slc.add_sample_img()
    smart_camera.slc.train()
    smart_camera.slc.save_classifier('/flash/classify.classifier')



mPython图形化示例
-----------
.. figure:: /_static/image/example/self_learning_classifier/1.png
    :align: center
    :width: 1080




加载使用模型
-----------
例程::

    from mpython import *
    import smartcamera_new as smartcamera
    import time

    index = None
    score = None

    smart_camera = smartcamera.SmartCamera(tx=Pin.P16, rx=Pin.P15)
    ID = ['class1', 'class2']
    smart_camera.self_learning_classifier_init(2, 10, 11, 1)
    smart_camera.slc.load_classifier('/flash/classify.classifier')
    while True:
        smart_camera.slc.predict()
        index = smart_camera.slc.id
        score = smart_camera.slc.max_score
        if index != None:
            print(ID[index])



mPython图形化
-----------
.. figure:: /_static/image/example/self_learning_classifier/2.png
    :align: center
    :width: 1080

