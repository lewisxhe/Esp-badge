// include library, include base class, make path known
#include <GxEPD.h>
#include <GxIO/GxIO_SPI/GxIO_SPI.cpp>
#include <GxIO/GxIO.cpp>
// select the display class to use, only one
//#include <GxGDEP015OC1/GxGDEP015OC1.cpp>    // 1.54" b/w
//#include <GxGDEW0154Z04/GxGDEW0154Z04.cpp>  // 1.54" b/w/r 200x200
//#include <GxGDEW0154Z17/GxGDEW0154Z17.cpp>  // 1.54" b/w/r 152x152
//#include <GxGDE0213B1/GxGDE0213B1.cpp>      // 2.13" b/w
//#include <GxGDEW0213Z16/GxGDEW0213Z16.cpp>  // 2.13" b/w/r
#include <GxGDEH029A1/GxGDEH029A1.cpp> // 2.9" b/w
//#include <GxGDEW029Z10/GxGDEW029Z10.cpp>    // 2.9" b/w/r
//#include <GxGDEW027C44/GxGDEW027C44.cpp>    // 2.7" b/w/r
// #include <GxGDEW027W3/GxGDEW027W3.cpp> // 2.7" b/w
//#include <GxGDEW042T2/GxGDEW042T2.cpp>      // 4.2" b/w
//#include <GxGDEW042Z15/GxGDEW042Z15.cpp>    // 4.2" b/w/r
//#include <GxGDEW0583T7/GxGDEW0583T7.cpp>    // 5.83" b/w
//#include <GxGDEW075T8/GxGDEW075T8.cpp>      // 7.5" b/w
// #include <GxGDEW075Z09/GxGDEW075Z09.cpp>    // 7.5" b/w/r

#include <Fonts/FreeMono9pt7b.h>
#include <Fonts/FreeMonoBoldOblique9pt7b.h>
#include <Fonts/FreeMonoBold9pt7b.h>
#include <Fonts/FreeMonoOblique9pt7b.h>
#include <Fonts/FreeSans9pt7b.h>
#include <Fonts/FreeSansBold9pt7b.h>
#include <Fonts/FreeSansBoldOblique9pt7b.h>
#include <Fonts/FreeSansOblique9pt7b.h>
#include <Fonts/FreeSerif9pt7b.h>
#include <Fonts/FreeSerifBold9pt7b.h>
#include <Fonts/FreeSerifBoldItalic9pt7b.h>
#include <Fonts/FreeSerifItalic9pt7b.h>

//#define DEFALUT_FONT  FreeMono9pt7b
// #define DEFALUT_FONT  FreeMonoBoldOblique9pt7b
// #define DEFALUT_FONT FreeMonoBold9pt7b
// #define DEFALUT_FONT FreeMonoOblique9pt7b
#define DEFALUT_FONT FreeSans9pt7b
// #define DEFALUT_FONT FreeSansBold9pt7b
// #define DEFALUT_FONT FreeSansBoldOblique9pt7b
// #define DEFALUT_FONT FreeSansOblique9pt7b
// #define DEFALUT_FONT FreeSerif9pt7b
// #define DEFALUT_FONT FreeSerifBold9pt7b
// #define DEFALUT_FONT FreeSerifBoldItalic9pt7b
// #define DEFALUT_FONT FreeSerifItalic9pt7b

const GFXfont *fonts[] = {
    &FreeMono9pt7b,
    &FreeMonoBoldOblique9pt7b,
    &FreeMonoBold9pt7b,
    &FreeMonoOblique9pt7b,
    &FreeSans9pt7b,
    &FreeSansBold9pt7b,
    &FreeSansBoldOblique9pt7b,
    &FreeSansOblique9pt7b,
    &FreeSerif9pt7b,
    &FreeSerifBold9pt7b,
    &FreeSerifBoldItalic9pt7b,
    &FreeSerifItalic9pt7b};

#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <ESPmDNS.h>

#include <OneButton.h>

// ----------->>>> SD
// #define USE_SD
// #define USE_AP_MODE
// #define __DEBUG

#ifdef USE_SD
/*
 * SD Card | ESP32
 *    D2       -
 *    D3       SS
 *    CMD      MOSI
 *    VSS      GND
 *    VDD      3.3V
 *    CLK      SCK
 *    VSS      GND
 *    D0       MISO
 *    D1       -
 */
#include "SD.h"
#include "SPI.h"
#define FILESYSTEM SD
#else
#include <SPIFFS.h>
#define FILESYSTEM SPIFFS
#endif
#include <FS.h>

#include <ArduinoJson.h>

#include "esp_wifi.h"
#include "Esp.h"

/*100 * 100 bmp fromat*/
//https://www.onlineconverter.com/jpg-to-bmp
#define BADGE_CONFIG_FILE_NAME "/badge.data"
#define DEFALUT_AVATAR_BMP "/avatar.bmp"
#define DEFALUT_QR_CODE_BMP "/qr.bmp"
#define WIFI_SSID "xinyuan"
#define WIFI_PASSWORD "12345678"

typedef struct
{
  char name[32];
  char link[64];
  char tel[64];
  char company[64];
  char email[64];
  char address[128];
} Badge_Info_t;

typedef enum
{
  RIGHT_ALIGNMENT = 0,
  LEFT_ALIGNMENT,
  CENTER_ALIGNMENT,
} Text_alignment;

AsyncWebServer server(80);

#include "board.h"
GxIO_Class io(SPI, ELINK_SS, ELINK_DC, ELINK_RESET);
GxEPD_Class display(io, ELINK_RESET, ELINK_BUSY);

OneButton button1(GPIO_NUM_38, true);
OneButton button2(GPIO_NUM_37, true);
OneButton button3(GPIO_NUM_39, true);

StaticJsonBuffer<512> jsonBuffer;
Badge_Info_t info;
static const uint16_t input_buffer_pixels = 20;       // may affect performance
static const uint16_t max_palette_pixels = 256;       // for depth <= 8
uint8_t mono_palette_buffer[max_palette_pixels / 8];  // palette buffer for depth <= 8 b/w
uint8_t color_palette_buffer[max_palette_pixels / 8]; // palette buffer for depth <= 8 c/w
uint8_t input_buffer[3 * input_buffer_pixels];        // up to depth 24
const char *path[2] = {DEFALUT_AVATAR_BMP, DEFALUT_QR_CODE_BMP};

#ifdef __DEBUG

// Prints the content of a file to the Serial
void printFile(const char *filename)
{
  // Open file for reading
  File file = FILESYSTEM.open(filename);
  if (!file)
  {
    Serial.println(F("Failed to read file"));
    return;
  }
  // Extract each characters by one by one
  while (file.available())
  {
    Serial.print((char)file.read());
  }
  Serial.println();
  // Close the file (File's destructor doesn't close the file)
  file.close();
}

void listDir(fs::FS &fs, const char *dirname, uint8_t levels)
{
  Serial.printf("Listing directory: %s\r\n", dirname);

  File root = fs.open(dirname);
  if (!root)
  {
    Serial.println("- failed to open directory");
    return;
  }
  if (!root.isDirectory())
  {
    Serial.println(" - not a directory");
    return;
  }

  File file = root.openNextFile();
  while (file)
  {
    if (file.isDirectory())
    {
      Serial.print("  DIR : ");
      Serial.println(file.name());
      if (levels)
      {
        listDir(fs, file.name(), levels - 1);
      }
    }
    else
    {
      Serial.print("  FILE: ");
      Serial.print(file.name());
      Serial.print("\tSIZE: ");
      Serial.println(file.size());
    }
    file = root.openNextFile();
  }
}
#endif

void displayText(const String &str, int16_t y, uint8_t alignment)
{
  int16_t x = 0;
  int16_t x1, y1;
  uint16_t w, h;
  display.setCursor(x, y);
  display.getTextBounds(str, x, y, &x1, &y1, &w, &h);

  switch (alignment)
  {
  case RIGHT_ALIGNMENT:
    display.setCursor(display.width() - w - x1, y);
    break;
  case LEFT_ALIGNMENT:
    display.setCursor(0, y);
    break;
  case CENTER_ALIGNMENT:
    display.setCursor(display.width() / 2 - ((w + x1) / 2), y);
    break;
  default:
    break;
  }
  display.println(str);
}

void saveBadgeInfo(Badge_Info_t *info)
{
  // Open file for writing
  File file = FILESYSTEM.open(BADGE_CONFIG_FILE_NAME, FILE_WRITE);
  if (!file)
  {
    Serial.println(F("Failed to create file"));
    return;
  }
  // Parse the root object
  JsonObject &root = jsonBuffer.createObject();

  // Set the values
  root["company"] = info->company;
  root["name"] = info->name;
  root["address"] = info->address;
  root["email"] = info->email;
  root["link"] = info->link;
  root["tel"] = info->tel;

  // Serialize JSON to file
  if (root.printTo(file) == 0)
  {
    Serial.println(F("Failed to write to file"));
  }

  // Close the file (File's destructor doesn't close the file)
  file.close();
}

void loadDefaultInfo(void)
{
  strlcpy(info.company, "Xin Yuan Electronic", sizeof(info.company));
  strlcpy(info.name, "Lilygo", sizeof(info.name));
  strlcpy(info.address, "ShenZhen", sizeof(info.address));
  strlcpy(info.email, "lily@lilygo.cc", sizeof(info.email));
  strlcpy(info.link, "http://www.lilygo.cn", sizeof(info.link));
  strlcpy(info.tel, "0755-83380665", sizeof(info.tel));
  saveBadgeInfo(&info);
}

bool loadBadgeInfo(Badge_Info_t *info)
{
  if (!FILESYSTEM.exists(BADGE_CONFIG_FILE_NAME))
  {
    Serial.println("load configure fail");
    return false;
  }

  File file = FILESYSTEM.open(BADGE_CONFIG_FILE_NAME);
  if (!file)
  {
    Serial.println("Open Fial -->");
    return false;
  }
  JsonObject &root = jsonBuffer.parseObject(file);
  if (!root.success())
  {
    Serial.println(F("Failed to read file, using default configuration"));
    file.close();
    return false;
  }
  Serial.println("parse success\n");

  root.printTo(Serial);

  if (!root.get<const char *>("company") || !root.get<const char *>("name") || !root.get<const char *>("address") || !root.get<const char *>("email") || !root.get<const char *>("link") || !root.get<const char *>("tel"))
  {
    file.close();
    return false;
  }
  strlcpy(info->company, root["company"], sizeof(info->company));
  strlcpy(info->name, root["name"], sizeof(info->name));
  strlcpy(info->address, root["address"], sizeof(info->address));
  strlcpy(info->email, root["email"], sizeof(info->email));
  strlcpy(info->link, root["link"], sizeof(info->link));
  strlcpy(info->tel, root["tel"], sizeof(info->tel));
  file.close();
  return true;
}

void WebServerStart(void)
{

#ifdef USE_AP_MODE
  uint8_t mac[6];
  char apName[18] = {0};
  IPAddress apIP = IPAddress(192, 168, 1, 1);

  WiFi.mode(WIFI_AP);

  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));

  esp_wifi_get_mac(WIFI_IF_STA, mac);

  sprintf(apName, "TTGO-Badge-%02X:%02X", mac[4], mac[5]);

  if (!WiFi.softAP(apName, "12345678", 1, 0, 1))
  {
    Serial.println("AP Config failed.");
    return;
  }
  else
  {
    Serial.println("AP Config Success.");
    Serial.print("AP MAC: ");
    Serial.println(WiFi.softAPmacAddress());
  }
#else
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  while (WiFi.waitForConnectResult() != WL_CONNECTED)
  {
    Serial.print(".");
    esp_restart();
  }
  Serial.println(F("WiFi connected"));
  Serial.println("");
  Serial.println(WiFi.localIP());
#endif

  if (MDNS.begin("ttgo"))
  {
    Serial.println("MDNS responder started");
  }

  server.serveStatic("/", FILESYSTEM, "/").setDefaultFile("index.html");

  /*test png bmp*/
  server.on("/av", HTTP_GET, [](AsyncWebServerRequest *request) {
    Serial.println("BMP");
    request->send(FILESYSTEM, DEFALUT_AVATAR_BMP, "image/bmp");
  });

  server.on("/qr", HTTP_GET, [](AsyncWebServerRequest *request) {
    Serial.println("png");
    request->send(FILESYSTEM, DEFALUT_QR_CODE_BMP, "image/bmp");
  });
  /*test png bmp*/

  // server.on("js/upload.js", HTTP_GET, [](AsyncWebServerRequest *request) {
  //   request->send(FILESYSTEM, "js/upload.js", "application/javascript");
  // });

  server.on("css/main.css", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(FILESYSTEM, "css/main.css", "text/css");
  });
  server.on("js/jquery.min.js", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(FILESYSTEM, "js/jquery.min.js", "application/javascript");
  });
  server.on("js/tbdValidate.js", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(FILESYSTEM, "js/tbdValidate.js", "application/javascript");
  });
  server.on("/data", HTTP_POST, [](AsyncWebServerRequest *request) {
    request->send(200, "text/plain", "");

    for (int i = 0; i < request->params(); i++)
    {
      String name = request->getParam(i)->name();
      String params = request->getParam(i)->value();
      Serial.println(name + " : " + params);
      if (name == "company")
      {
        strlcpy(info.company, params.c_str(), sizeof(info.company));
      }
      else if (name == "name")
      {
        strlcpy(info.name, params.c_str(), sizeof(info.name));
      }
      else if (name == "address")
      {
        strlcpy(info.address, params.c_str(), sizeof(info.address));
      }
      else if (name == "email")
      {
        strlcpy(info.email, params.c_str(), sizeof(info.email));
      }
      else if (name == "link")
      {
        strlcpy(info.link, params.c_str(), sizeof(info.link));
      }
      else if (name == "tel")
      {
        strlcpy(info.tel, params.c_str(), sizeof(info.tel));
      }
    }
    saveBadgeInfo(&info);
  });

  server.onFileUpload([](AsyncWebServerRequest *request, const String &filename, size_t index, uint8_t *data, size_t len, bool final) {
    static File file;
    static int pathIndex = 0;
    if (!index)
    {
      Serial.printf("UploadStart: %s\n", filename.c_str());
      file = FILESYSTEM.open(path[pathIndex], FILE_WRITE);
      if (!file)
      {
        Serial.println("Open FAIL");
        request->send(500, "text/plain", "hander error");
        return;
      }
    }
    if (file.write(data, len) != len)
    {
      Serial.println("Write fail");
      request->send(500, "text/plain", "hander error");
      file.close();
      return;
    }

    if (final)
    {
      Serial.printf("UploadEnd: %s (%u)\n", filename.c_str(), index + len);
      file.close();
      request->send(200, "text/plain", "");
      if (++pathIndex >= 2)
      {
        pathIndex = 0;
        showMianPage();
      }
    }
  });

  server.onNotFound([](AsyncWebServerRequest *request) {
    request->send(404, "text/plain", "Not found");
  });

  MDNS.addService("http", "tcp", 80);

  server.begin();
}

void showMianPage(void)
{
  displayInit();
  display.fillScreen(GxEPD_WHITE);
  drawBitmap(DEFALUT_AVATAR_BMP, 10, 10, true);
  displayText(String(info.name), 30, RIGHT_ALIGNMENT);
  displayText(String(info.company), 50, RIGHT_ALIGNMENT);
  displayText(String(info.email), 70, RIGHT_ALIGNMENT);
  displayText(String(info.link), 90, RIGHT_ALIGNMENT);
  display.update();
}

void showQrPage(void)
{
  displayInit();
  display.fillScreen(GxEPD_WHITE);
  drawBitmap(DEFALUT_QR_CODE_BMP, 10, 10, true);
  displayText(String(info.tel), 50, RIGHT_ALIGNMENT);
  displayText(String(info.email), 70, RIGHT_ALIGNMENT);
  displayText(String(info.address), 90, RIGHT_ALIGNMENT);
  display.update();
}

void click1()
{
  Serial.println("Button 1 click.");
#ifdef __DEBUG
  listDir(FILESYSTEM, "/", 2);
#else
  esp_sleep_enable_ext0_wakeup(GPIO_NUM_38, LOW);
  Serial.println("Going to sleep now");
  delay(2000);
  esp_deep_sleep_start();
  Serial.println("This will never be printed");
#endif
}

void click2()
{
  static int i = 0;
  Serial.println("Button 2 click.");
  Serial.printf("Show Num: %d font\n", i);
  i = ((i + 1) >= sizeof(fonts) / sizeof(fonts[0])) ? 0 : i + 1;
  display.setFont(fonts[i]);
  showMianPage();
}

void click3()
{
  static bool index = 1;
  Serial.println("Button 3 click.");
  if (!index)
  {
    showMianPage();
    index = true;
  }
  else
  {
    showQrPage();
    index = false;
  }
}

uint16_t read16(File &f)
{
  // BMP data is stored little-endian, same as Arduino.
  uint16_t result;
  ((uint8_t *)&result)[0] = f.read(); // LSB
  ((uint8_t *)&result)[1] = f.read(); // MSB
  return result;
}

uint32_t read32(File &f)
{
  // BMP data is stored little-endian, same as Arduino.
  uint32_t result;
  ((uint8_t *)&result)[0] = f.read(); // LSB
  ((uint8_t *)&result)[1] = f.read();
  ((uint8_t *)&result)[2] = f.read();
  ((uint8_t *)&result)[3] = f.read(); // MSB
  return result;
}

void drawBitmap(const char *filename, int16_t x, int16_t y, bool with_color)
{
  File file;
  bool valid = false; // valid format to be handled
  bool flip = true;   // bitmap is stored bottom-to-top
  uint32_t startTime = millis();
  if ((x >= display.width()) || (y >= display.height()))
    return;
  Serial.println();
  Serial.print("Loading image '");
  Serial.print(filename);
  Serial.println('\'');

  file = FILESYSTEM.open(filename, FILE_READ);
  if (!file)
  {
    Serial.print("File not found");
    return;
  }

  // Parse BMP header
  if (read16(file) == 0x4D42) // BMP signature
  {
    uint32_t fileSize = read32(file);
    uint32_t creatorBytes = read32(file);
    uint32_t imageOffset = read32(file); // Start of image data
    uint32_t headerSize = read32(file);
    uint32_t width = read32(file);
    uint32_t height = read32(file);
    uint16_t planes = read16(file);
    uint16_t depth = read16(file); // bits per pixel
    uint32_t format = read32(file);
    if ((planes == 1) && ((format == 0) || (format == 3))) // uncompressed is handled, 565 also
    {
      Serial.print("File size: ");
      Serial.println(fileSize);
      Serial.print("Image Offset: ");
      Serial.println(imageOffset);
      Serial.print("Header size: ");
      Serial.println(headerSize);
      Serial.print("Bit Depth: ");
      Serial.println(depth);
      Serial.print("Image size: ");
      Serial.print(width);
      Serial.print('x');
      Serial.println(height);
      // BMP rows are padded (if needed) to 4-byte boundary
      uint32_t rowSize = (width * depth / 8 + 3) & ~3;
      if (depth < 8)
        rowSize = ((width * depth + 8 - depth) / 8 + 3) & ~3;
      if (height < 0)
      {
        height = -height;
        flip = false;
      }
      uint16_t w = width;
      uint16_t h = height;
      if ((x + w - 1) >= display.width())
        w = display.width() - x;
      if ((y + h - 1) >= display.height())
        h = display.height() - y;
      valid = true;
      uint8_t bitmask = 0xFF;
      uint8_t bitshift = 8 - depth;
      uint16_t red, green, blue;
      bool whitish, colored;
      if (depth == 1)
        with_color = false;
      if (depth <= 8)
      {
        if (depth < 8)
          bitmask >>= depth;
        file.seek(54); //palette is always @ 54
        for (uint16_t pn = 0; pn < (1 << depth); pn++)
        {
          blue = file.read();
          green = file.read();
          red = file.read();
          file.read();
          whitish = with_color ? ((red > 0x80) && (green > 0x80) && (blue > 0x80)) : ((red + green + blue) > 3 * 0x80); // whitish
          colored = (red > 0xF0) || ((green > 0xF0) && (blue > 0xF0));                                                  // reddish or yellowish?
          if (0 == pn % 8)
            mono_palette_buffer[pn / 8] = 0;
          mono_palette_buffer[pn / 8] |= whitish << pn % 8;
          if (0 == pn % 8)
            color_palette_buffer[pn / 8] = 0;
          color_palette_buffer[pn / 8] |= colored << pn % 8;
        }
      }
      display.fillScreen(GxEPD_WHITE);
      uint32_t rowPosition = flip ? imageOffset + (height - h) * rowSize : imageOffset;
      for (uint16_t row = 0; row < h; row++, rowPosition += rowSize) // for each line
      {
        uint32_t in_remain = rowSize;
        uint32_t in_idx = 0;
        uint32_t in_bytes = 0;
        uint8_t in_byte = 0; // for depth <= 8
        uint8_t in_bits = 0; // for depth <= 8
        uint16_t color = GxEPD_WHITE;
        file.seek(rowPosition);
        for (uint16_t col = 0; col < w; col++) // for each pixel
        {
          // Time to read more pixel data?
          if (in_idx >= in_bytes) // ok, exact match for 24bit also (size IS multiple of 3)
          {
            in_bytes = file.read(input_buffer, in_remain > sizeof(input_buffer) ? sizeof(input_buffer) : in_remain);
            in_remain -= in_bytes;
            in_idx = 0;
          }
          switch (depth)
          {
          case 24:
            blue = input_buffer[in_idx++];
            green = input_buffer[in_idx++];
            red = input_buffer[in_idx++];
            whitish = with_color ? ((red > 0x80) && (green > 0x80) && (blue > 0x80)) : ((red + green + blue) > 3 * 0x80); // whitish
            colored = (red > 0xF0) || ((green > 0xF0) && (blue > 0xF0));                                                  // reddish or yellowish?
            break;
          case 16:
          {
            uint8_t lsb = input_buffer[in_idx++];
            uint8_t msb = input_buffer[in_idx++];
            if (format == 0) // 555
            {
              blue = (lsb & 0x1F) << 3;
              green = ((msb & 0x03) << 6) | ((lsb & 0xE0) >> 2);
              red = (msb & 0x7C) << 1;
            }
            else // 565
            {
              blue = (lsb & 0x1F) << 3;
              green = ((msb & 0x07) << 5) | ((lsb & 0xE0) >> 3);
              red = (msb & 0xF8);
            }
            whitish = with_color ? ((red > 0x80) && (green > 0x80) && (blue > 0x80)) : ((red + green + blue) > 3 * 0x80); // whitish
            colored = (red > 0xF0) || ((green > 0xF0) && (blue > 0xF0));                                                  // reddish or yellowish?
          }
          break;
          case 1:
          case 4:
          case 8:
          {
            if (0 == in_bits)
            {
              in_byte = input_buffer[in_idx++];
              in_bits = 8;
            }
            uint16_t pn = (in_byte >> bitshift) & bitmask;
            whitish = mono_palette_buffer[pn / 8] & (0x1 << pn % 8);
            colored = color_palette_buffer[pn / 8] & (0x1 << pn % 8);
            in_byte <<= depth;
            in_bits -= depth;
          }
          break;
          }
          if (whitish)
          {
            color = GxEPD_WHITE;
          }
          else if (colored && with_color)
          {
            color = GxEPD_RED;
          }
          else
          {
            color = GxEPD_BLACK;
          }
          uint16_t yrow = y + (flip ? h - row - 1 : row);
          display.drawPixel(x + col, yrow, color);
        } // end pixel
      }   // end line
      Serial.print("loaded in ");
      Serial.print(millis() - startTime);
      Serial.println(" ms");
    }
  }
  file.close();
  if (!valid)
  {
    Serial.println("bitmap format not handled.");
  }
}

void displayInit(void)
{
  static bool isInit = false;
  if (isInit)
  {
    return;
  }
  isInit = true;
  display.init();
  display.setRotation(1);
  display.eraseDisplay();
  display.setTextColor(GxEPD_BLACK);
  display.setFont(&DEFALUT_FONT);
  display.setTextSize(0);
}

void setup()
{
  Serial.begin(115200);
  delay(500);

  Serial.println("free heap:" + String(ESP.getHeapSize()));

  SPI.begin(SPI_CLK, SPI_MISO, SPI_MOSI, -1);

#ifdef USE_SD
  if (!FILESYSTEM.begin(SDCARD_SS))
#else
  if (!FILESYSTEM.begin())
#endif
  {
    Serial.println("FILESYSTEM is not database");
    Serial.println("Please use Arduino ESP32 Sketch data Upload files");
    while (1)
    {
      delay(1000);
    }
  }

#ifdef USE_SD
  uint64_t cardSize = FILESYSTEM.cardSize() / (1024 * 1024);
  Serial.printf("SD Card Size: %lluMB\n", cardSize);
#endif

  if (!loadBadgeInfo(&info))
  {
    loadDefaultInfo();
  }

  if (esp_sleep_get_wakeup_cause() == ESP_SLEEP_WAKEUP_UNDEFINED)
  {
    showMianPage();
  }

  WebServerStart();

  button1.attachClick(click1);
  button2.attachClick(click2);
  button3.attachClick(click3);
}

void loop()
{
  button1.tick();
  button2.tick();
  button3.tick();
}
