TTGO Badge & TTGO EPaper Series
========================



![](images/4.png)

## BOARD PINS
| Name                | T5 V1.2 / V2.4 | T5 V2.0   | T5 V2.1   | T5 V2.2   | T5 V2.3   | T5 V2.8   | T5 xxxx   |
| ------------------- | -------------- | --------- | --------- | --------- | --------- | --------- | --------- |
| EPaper BUSY         | 4              | 4         | 4         | 4         | 4         | 4         | 4         |
| EPaper RST          | 16             | 16        | 16        | 12        | 16        | 16        | 12        |
| EPaper DC           | 17             | 17        | 17        | 19        | 17        | 17        | 13        |
| EPaper CS           | 5              | 5         | 5         | 5         | 5         | 5         | 2         |
| EPaper MOSI         | 23             | 23        | 23        | 23        | 23        | 23        | 15        |
| EPaper MISO         | N/A            | N/A       | N/A       | N/A       | N/A       | N/A       | N/A       |
| EPaper SCLK         | 18             | 18        | 18        | 18        | 18        | 18        | 14        |
| SDCard CS           | 13             | 13        | 13        | 13        | 13        | 13        | N/A       |
| SDCard MOSI         | 15             | 15        | 15        | 23        | 15        | 15        | N/A       |
| SDCard MISO         | 2              | 2         | 2         | 2         | 2         | 2         | N/A       |
| SDCard SCLK         | 14             | 14        | 14        | 18        | 14        | 14        | N/A       |
| Button 1            | 37             | 39        | 37        | 37        | 39        | 37        | 37        |
| Button 2            | 38             | N/A       | 38        | 38        | N/A       | 38        | 38        |
| Button 3            | 39             | N/A       | 39        | 39        | N/A       | 39        | 39        |
| DAC OUT             | 25             | N/A       | 25        | 25        | N/A       | Note1     | N/A       |
| DS3231 SDA          | N/A            | N/A       | N/A       | N/A       | N/A       | N/A       | 21        |
| DS3231 SCL          | N/A            | N/A       | N/A       | N/A       | N/A       | N/A       | 22        |
| LORA MOSI           | N/A            | N/A       | N/A       | N/A       | N/A       | N/A       | 27        |
| LORA MISO           | N/A            | N/A       | N/A       | N/A       | N/A       | N/A       | 19        |
| LORA SCLK           | N/A            | N/A       | N/A       | N/A       | N/A       | N/A       | 5         |
| LORA CS             | N/A            | N/A       | N/A       | N/A       | N/A       | N/A       | 18        |
| LORA RST            | N/A            | N/A       | N/A       | N/A       | N/A       | N/A       | 23        |
| LORA DIO0           | N/A            | N/A       | N/A       | N/A       | N/A       | 2N/A      | 26        |
| SPRAM               | N/A            | N/A       | N/A       | supported | N/A       | N/A       | supported |
| Support EPaper Size | Full Size      | Full Size | Full Size | Full Size | Full Size | Full Size | Full Size |


[中文描述点这里](doc/zh-cn.md)


## Note1: 

**Max98357**

| Name | T5 V2.8 |
| ---- | ------- |
| BCK  | 26      |
| WS   | 25      |
| DOUT | 19      |

**Mic**

| Name | T5 V2.8 |
| ---- | ------- |
| BCK  | 26      |
| WS   | 25      |
| DIN  | 19      |



## Note
- There are currently three versions of 2.13 e-paper, all of which will use the `GxGDE0213B72B` model later, and the `GxGDE0213B1` and `GxGDE0213B72` models have been stopped. The default setting is "GxGDE0213B72B". If the old version screen has changed, change the corresponding title in `board_def.h`.


    ```
    // #include <GxGDE0213B1/GxGDE0213B1.h>       // 2.13" b/w
    // #include <GxGDE0213B72/GxGDE0213B72.h>     // 2.13" b/w
    #include <GxGDE0213B72B/GxGDE0213B72B.h>      // 2.13" b/w
    ```

- 2019/5/11 The T5_V2.4 version is the same as the T5_V1.2 version pin pin. Add `IO19` to the power amplifier power control. Control IO19 to high level to turn on the power amplifier power supply, low level is off.



#### Update to PlatformIO, if you use Arduino, you need to do these
- If you use Dowload ZIP to download and compile with Arduino IDE, please change src / main.cpp to a folder with the same name as your directory, otherwise you won't find the header files, such as using the downloaded folder named `TTGO-EPaper-Series-master`, then you need to change the name of main.cpp in src to TTGO-EPaper-Series.ino, and change the src directory to TTGO-EPaper-Series, and change the lib Move or copy the folders in the directory to your Arduino library directory.The default Arduino directory is `C:\Users\your username\Documents\Arduino\libraries`, and then put the data directory into` TTGO-EPaper-Series.ino` in the same directory for uploading resources


## First

- For the first time, change the macro definition in `board_def.h` according to the corresponding layout and screen, and change the version to be used to 1.
```
#define TTGO_T5_1_2 0
#define TTGO_T5_2_0 0
#define TTGO_T5_2_1 0
#define TTGO_T5_2_2 0
#define TTGO_T5_2_3 0
#define TTGO_T5_2_4 0
#define TTGO_T5_2_8 0   
```

- Check the screen size and color used. The default configuration screen list can be viewed in `board_def.h`. The default configuration is based on the size of the TTGO store. Except for the T5 V1.2 version, the T5 V1.2 needs to be configured according to the actual situation. The corresponding header file, 1.54 inches will not be fully displayed in this program

## Install the following dependency library files:
- [Button2](https://github.com/lewisxhe/Button2)<fork branch>
- [GxEPD](https://github.com/lewisxhe/GxEPD)<fork branch>
- [Adafruit-GFX-Library](https://github.com/adafruit/Adafruit-GFX-Library)
- [AsyncTCP](https://github.com/me-no-dev/AsyncTCP)
- [ESPAsyncWebServer](https://github.com/me-no-dev/ESPAsyncWebServer)
- [ArduinoJson](https://github.com/bblanchon/ArduinoJson/releases)
- [ESP8266Audio](https://github.com/earlephilhower/ESP8266Audio)
    ~~**CAUTION**: The Arduino Library Manager installs the ArduinoJson version 6 by default.~~
    ~~In here using version 5 is recommended because version 6 is still in beta stage. Please select 5.13.2 version to install on the releas page.~~

## Upload webserver resource
- Use Arduino ESP32 Sketch data Upload files,if you not install,[download ESP32FS-vX.zip](https://github.com/me-no-dev/arduino-esp32fs-plugin/releases),Extract to <C:\Users\Your User Name\Documents\Arduino\tools>,Open Ardunio IDE,  Tools -> ESP32 Sketch data Upload -> Upload

- With PlatformIO also you can upload files, with the next command:
```bash
pio run --target uploadfs
```

## Configure Badge Website
- **Configure the badge by entering http://ttgo.local or ip address in your browser.**
![](images/3.png)

- **The display will be refreshed after submission**
- **Page1**
![](images/1.png)
- **Page2**
![](images/2.png)


## CAUTION:
- Currently only supports 100*100 size BMP format as image file for uploading


