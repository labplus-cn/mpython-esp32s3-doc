角速度
======================================

三轴角速度计（又称三轴陀螺仪）是一种用于测量物体在三维空间中绕X、Y、Z三个轴旋转角速度的传感器。其核心用途是通过实时监测旋转运动，为姿态控制、导航、稳定性分析等提供关键数据。

.. image:: /_static/image/tutorials/gyroscope.png
    :align: center
    :width: 1200


例：通过图表折线图来观察3个轴角速度值的变化
::
    import time
    from mpython import *

    time.sleep_ms(50);print(('__TITLE', '角速度x', '角速度y', '角速度z'));time.sleep_ms(50)
    while True:
        print((gyroscope.get_x(), gyroscope.get_y(), gyroscope.get_z()))
        time.sleep(0.1)


