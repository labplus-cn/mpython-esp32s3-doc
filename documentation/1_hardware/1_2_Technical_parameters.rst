1.2. 技术参数
==============

1.2.1. 板载功能及技术参数
--------------------------------

.. image:: /_static/image/hardware/板载器件图.png
    :align: center
    :width: 1000

.. csv-table:: 硬件参数
    :header: "序号", "硬件", "型号规格"
    :widths: 5, 6, 10

    "1", "CPU", "-- ESP32-S3, 高性能Xtensa® 32 位 LX7 双核处理器,主频240MHz 
    
    -- 512K SRAM
    
    -- Wi-Fi协议：IEEE 802.11 b/g/n (802.11n)，速度高达150 Mbps)

    -- 低功耗蓝牙(Bluetooth LE)：Bluetooth 5、Bluetooth mesh,速率支持125Kbps、500Kbps、1Mbps、2Mbps
    
    -- 单精度浮点运算单元(FPU)

    -- 支持flash在线编程"

    "2", "屏幕", "1.47寸高清lcd彩屏，分辨率：172x320 型号：st7789"
    "3", "实体按键", "(A/B/reset)"
    "4", "触摸按键", "(P/Y/T/H/O/N)"
    "5", "PSRAM", "8MB "
    "6", "存储", "16MB(Flash)"
    "7", "光线传感器", "LTR-308ALS-01"
    "8", "麦克风","型号：CDX4013-C1C2-423(-38dB)，双麦克风"
    "9", "RGB灯", "全彩RGB*3"
    "10", "喇叭", "贴片式，13*13*4MM 1w" 
    "11", "磁传感器", "型号：MMC5603NJ，最小分辨率为0.0625mG，±30G的量程，±1°以内的指向精度"
    "12", "六轴传感器", "型号：QMI8658C，陀螺仪：量程可选，最高可测±2048°/s 三轴加速度计：量程可选，最高可测±16G"
    "13", "显示屏", "1.47寸，分辨率：172x320，全彩屏"
    "14", "音频", "es8388解码芯片，功放芯片：NS4150"

1.2.2. 金手指IO接口
--------------------------------

  - 20通道数字I/O， (其中支持12路PWM，6路触摸输入) 

  - 6通道12bit模拟输入ADC，P0~P4,P6 

  - 支持I2C通讯协议

  - 支持UART通讯协议(1路)，支持115200bps

  - 支持SPI通讯协议

  
1.2.3. 供电
--------------------------------

  * 供电方式：USB 5V供电或金手指3.3V供电
  * 工作电压：3.3V
  * 最大工作电流: 700mA
  * 最大负载电流: 1000mA

1.2.3. 原理图
--------------------------------

  待补充

1.2.4. 器件规格书
--------------------------------


  * :download:`ESP32S3_datasheet </8_datasheet/ESP32S3_datasheet.pdf>`

  * :download:`esp_psram45_datasheet </../8_datasheet/esp-psram64_esp-psram64h_datasheet_cn.pdf>`

  * :download:`es8388 </../8_datasheet/ES8388.pdf>`

  * :download:`LTR-308ALS-01 </../8_datasheet/LTR-308ALS-01_datasheet.pdf>`

  * :download:`MMC5603NJ_datasheet </../8_datasheet/MMC5603NJ.pdf>`

  * :download:`QMI8658C_datasheet </../8_datasheet/QMI8658C.pdf>`

  * :download:`GD25Q128ES1G_datasheet </../8_datasheet/GD25Q128ES1G.pdf>`

  * :download:`TFT_LCD </../8_datasheet/1.47 TFT LCD(HW-014014RP6W1-01).pdf>`