TTGO Badge 
========================


### Install the following dependency library files:
- [OneButton](https://github.com/mathertel/OneButton)
- [GxEPD](https://github.com/ZinggJM/GxEPD)
- [Adafruit-GFX-Library](https://github.com/adafruit/Adafruit-GFX-Library)
- [AsyncTCP](https://github.com/me-no-dev/AsyncTCP)
- [ESPAsyncWebServer](https://github.com/me-no-dev/ESPAsyncWebServer)
- [ArduinoJson 5.13.2](https://github.com/bblanchon/ArduinoJson/releases)

    **CAUTION**: The Arduino Library Manager installs the ArduinoJson version 6 by default.
    In here using version 5 is recommended because version 6 is still in beta stage. Please select 5.13.2 version to install on the releas page.

### Upload webserver resource
- Use Arduino ESP32 Sketch data Upload files,if you not install,[download ESP32FS-vX.zip](https://github.com/me-no-dev/arduino-esp32fs-plugin/releases),Extract to <C:\Users\Your User Name\Documents\Arduino\tools>,Open Ardunio IDE,  Tools -> ESP32 Sketch data Upload -> Upload

### Configure Badge Website

- **Configure the badge by entering http://ttgo.local in your browser.**
![](images/3.png)

- **The display will be refreshed after submission**
- **Page1**
![](images/1.png)
- **Page2**
![](images/2.png)


## CAUTION:
- Currently only supports 100*100 size BMP format as image file for uploading
