板载传感器
==============


六轴陀螺仪
--------
例程::

    from labplus import *

    accelerometer.set_range(MOTION.Accelerometer.RANGE_8G)

    while 1:
        x = accelerometer.get_x()
        y = accelerometer.get_y()
        z = accelerometer.get_z()
        g_x = gyroscope.get_x()
        g_y = gyroscope.get_y()
        g_z = gyroscope.get_z()
        print(x)
        print(y)
        print(z)
        print('===')
        time.sleep(1)



磁传感器
--------
例程::

    from labplus import *

    magnetic.calibrate()
    while (1):
        time.sleep(1)
        head = magnetic.get_heading()
        print("head:",h)
        print('=====')


气压计
--------
例程::

    from labplus import *

    while True:
        pressure = barometric.pressure()
        temperature = barometric.temperature()
        print("pressure:",pressure)
        print("temperature:",temperature)
        print("=======")
        time.sleep(1)