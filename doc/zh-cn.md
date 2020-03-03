
## 使用Arduino IDE
- 如果使用Dowload ZIP方式下载,并且使用Arduino IDE编译的,请把src/main.cpp 更改为与你目录同名的文件夹,否则会找不到头文件,比如使用下载的文件夹名为`TTGO-EPaper-Series-master`,那么你需要把src中的`main.cpp` 名字改为`TTGO-EPaper-Series.ino`,并且把src目录改为`TTGO-EPaper-Series` , 并且把`lib`目录内的文件夹移动或者复制到 你的Arduino库目录内,默认Arduino的目录为`C:\Users\你的用户名\Documents\Arduino\libraries`,再把data目录放入`TTGO-EPaper-Series.ino`同一个目录内,用于上传资源

## 使用PlatformIO
- 如果你使用PlatformIO方式,跳到下面 只要执行步骤1 ,然后直接编译就行了
  

## 初始配置
1. 刚开始需要选择你使用的板子,在`board_def.h`中 把你使用的板子后面的宏定义改成1,其他没用到的改0
```
#define TTGO_T5_1_2 0
#define TTGO_T5_2_0 0
#define TTGO_T5_2_1 0
#define TTGO_T5_2_2 0
#define TTGO_T5_2_3 0
#define TTGO_T5_2_4 0
#define TTGO_T5_2_8 0   
```
2. 上传资源文件
- 下载[ESP32FS-vX.zip](https://github.com/me-no-dev/arduino-esp32fs-plugin/releases),解压到`<C:\Users\你的用户名\Documents\Arduino\tools>`内,打开ArduinoIDE如下列步骤选择
工具->ESP32 Sketch data Upload->上传


## 程序依赖下面的库,默认已经在lib目录中
- [Button2](https://github.com/lewisxhe/Button2)
- [GxEPD](https://github.com/lewisxhe/GxEPD)
- [Adafruit-GFX-Library](https://github.com/adafruit/Adafruit-GFX-Library)
- [AsyncTCP](https://github.com/me-no-dev/AsyncTCP)
- [ESPAsyncWebServer](https://github.com/me-no-dev/ESPAsyncWebServer)
- [ArduinoJson](https://github.com/bblanchon/ArduinoJson/releases)
- [ESP8266Audio](https://github.com/earlephilhower/ESP8266Audio)