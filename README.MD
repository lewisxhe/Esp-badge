TTGO Badge & TTGO EPaper Series
========================

![](images/4.png)

## BOARD PINS
| Name                | T5 V1.2   | T5 V2.0   | T5 V2.1   | T5 V2.2   | T5 V2.3   | T5 xxxx   |
| ------------------- | --------- | --------- | --------- | --------- | --------- | --------- |
| EPaper BUSY         | 4         | 4         | 4         | 4         | 4         | 4         |
| EPaper RST          | 16        | 16        | 16        | 12        | 16        | 12        |
| EPaper DC           | 17        | 17        | 17        | 19        | 17        | 13        |
| EPaper CS           | 5         | 5         | 5         | 5         | 5         | 2         |
| EPaper MOSI         | 23        | 23        | 23        | 23        | 23        | 15        |
| EPaper MISO         | N/A       | N/A       | N/A       | N/A       | N/A       | N/A       |
| EPaper SCLK         | 18        | 18        | 18        | 18        | 18        | 14        |
| SDCard CS           | 13        | 13        | 13        | 13        | 13        | N/A       |
| SDCard MOSI         | 15        | 15        | 15        | 23        | 15        | N/A       |
| SDCard MISO         | 2         | 2         | 2         | 2         | 2         | N/A       |
| SDCard SCLK         | 14        | 14        | 14        | 18        | 14        | N/A       |
| Button 1            | 37        | 39        | 37        | 37        | 39        | 37        |
| Button 2            | 38        | N/A       | 38        | 38        | N/A       | 38        |
| Button 3            | 39        | N/A       | 39        | 39        | N/A       | 39        |
| DAC OUT             | 25        | N/A       | 25        | 25        | N/A       | N/A       |
| DS3231 SDA          | N/A       | N/A       | N/A       | N/A       | N/A       | 21        |
| DS3231 SCL          | N/A       | N/A       | N/A       | N/A       | N/A       | 22        |
| LORA MOSI           | N/A       | N/A       | N/A       | N/A       | N/A       | 27        |
| LORA MISO           | N/A       | N/A       | N/A       | N/A       | N/A       | 19        |
| LORA SCLK           | N/A       | N/A       | N/A       | N/A       | N/A       | 5         |
| LORA CS             | N/A       | N/A       | N/A       | N/A       | N/A       | 18        |
| LORA RST            | N/A       | N/A       | N/A       | N/A       | N/A       | 23        |
| LORA DIO0           | N/A       | N/A       | N/A       | N/A       | N/A       | 26        |
| SPRAM               | N/A       | N/A       | N/A       | supported | N/A       | supported |
| Support EPaper Size | Full Size | Full Size | Full Size | Full Size | Full Size | Full Size |

## Install the following dependency library files:
- [Button2](https://github.com/lewisxhe/Button2)
- [GxEPD](https://github.com/ZinggJM/GxEPD)
- [Adafruit-GFX-Library](https://github.com/adafruit/Adafruit-GFX-Library)
- [AsyncTCP](https://github.com/me-no-dev/AsyncTCP)
- [ESPAsyncWebServer](https://github.com/me-no-dev/ESPAsyncWebServer)
- [ArduinoJson 5.13.2](https://github.com/bblanchon/ArduinoJson/releases)

    **CAUTION**: The Arduino Library Manager installs the ArduinoJson version 6 by default.
    In here using version 5 is recommended because version 6 is still in beta stage. Please select 5.13.2 version to install on the releas page.

## Upload webserver resource
- Use Arduino ESP32 Sketch data Upload files,if you not install,[download ESP32FS-vX.zip](https://github.com/me-no-dev/arduino-esp32fs-plugin/releases),Extract to <C:\Users\Your User Name\Documents\Arduino\tools>,Open Ardunio IDE,  Tools -> ESP32 Sketch data Upload -> Upload

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


