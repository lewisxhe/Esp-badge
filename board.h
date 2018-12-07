

#define TTGO_T5_2_1 0
#define TTGO_T5_2_2 1
#define TTGO_T5_2_3 0

#if TTGO_T5_2_1

#define ELINK_BUSY 4
#define ELINK_RESET 16
#define ELINK_DC 17
#define ELINK_SS 5

#define SPI_MOSI 23
#define SPI_MISO 19
#define SPI_CLK 18

#define SDCARD_SS 13
#define BUTTON_1 38
#define BUTTON_2 37
#define BUTTON_3 39

#elif TTGO_T5_2_2

#define ELINK_BUSY 4
#define ELINK_RESET 12
#define ELINK_DC 19
#define ELINK_SS 5

#define SPI_MOSI 23
#define SPI_MISO 2
#define SPI_CLK 18

#define SDCARD_SS 13
#define BUTTON_1 38
#define BUTTON_2 37
#define BUTTON_3 39

#elif TTGO_T5_2_3

#define ELINK_BUSY 4
#define ELINK_RESET 12
#define ELINK_DC 13
#define ELINK_SS 2

#define SPI_MOSI 15
#define SPI_MISO 2
#define SPI_CLK 14

#define SDCARD_SS 13

#define BUTTON_1 38
#define BUTTON_2 37
#define BUTTON_3 39

#else
#error "Please select board type"
#endif

// // #define OLD_BOARD

// #ifdef OLD_BOARD
// #define ELINK_BUSY 4
// #define ELINK_RESET 12//16
// #define ELINK_DC 19//17
// #define ELINK_SS 5

// #define SPI_MOSI 23
// #define SPI_MISO 2//19
// #define SPI_CLK 18

// #define SDCARD_SS 13
// #define BUTTON_1 38
// #define BUTTON_2 37
// #define BUTTON_3 39

// #else

// #define ELINK_BUSY 4
// #define ELINK_RESET 12
// #define ELINK_DC 13
// #define ELINK_SS 2

// #define SPI_MOSI 15
// #define SPI_MISO 2
// #define SPI_CLK 14

// #define SDCARD_SS 13

// #define BUTTON_1 38
// #define BUTTON_2 37
// #define BUTTON_3 39

//NEW  BOARD
// #define ELINK_BUSY 4
// #define ELINK_RESET 12
// #define ELINK_DC 19
// #define ELINK_SS 5

// #define SPI_MOSI 23
// #define SPI_MISO 2
// #define SPI_CLK 18

// #define SDCARD_SS 13

// #define BUTTON_1 38
// #define BUTTON_2 37
// #define BUTTON_3 39
// #endif
// SPIClass& spi, int8_t cs, int8_t dc, int8_t rst = -1, int8_t bl = -1
// GxGDEH029A1(GxIO& io, int8_t rst = 9, int8_t busy = 7);

// SPIClass(uint8_t spi_bus=HSPI);
// void begin(int8_t sck=-1, int8_t miso=-1, int8_t mosi=-1, int8_t ss=-1);

/*  0 默认初始化IO
Set _cs :5
Set _dc :17
Set _rst :16
SPIClass::Begin:VSPI ,SCK:-1 MISO:-1 MOSI:-1 SS:-1
SPI.cpp INIT :_sck:-1 _miso:-1 _mosi:-1 _ss:-1
SPI.cpp INIT :_sck:18 _miso:19 _mosi:23 _ss:5
*/

/*  1 指定初始化IO
SPIClass::Begin:VSPI ,SCK:18 MISO:19 MOSI:23 SS:5
SPI.cpp INIT :_sck:18 _miso:19 _mosi:23 _ss:5
SPI.cpp INIT :_sck:18 _miso:19 _mosi:23 _ss:5
GxIO_SPI::init
Set _cs :5
Set _dc :17
Set _rst :16
SPIClass::Begin:VSPI ,SCK:-1 MISO:-1 MOSI:-1 SS:-1
already init return func
*/

/* 2 更改MISO  IO
SPIClass::Begin:VSPI ,SCK:18 MISO:2 MOSI:23 SS:5
SPI.cpp INIT :_sck:18 _miso:2 _mosi:23 _ss:5
SPI.cpp INIT :_sck:18 _miso:2 _mosi:23 _ss:5
GxIO_SPI::init
Set _cs :5
Set _dc :17
Set _rst :16
SPIClass::Begin:VSPI ,SCK:-1 MISO:-1 MOSI:-1 SS:-1
already init return func
*/

/*  3 更改DC IO
SPIClass::Begin:VSPI ,SCK:18 MISO:2 MOSI:23 SS:5
SPI.cpp INIT :_sck:18 _miso:2 _mosi:23 _ss:5
SPI.cpp INIT :_sck:18 _miso:2 _mosi:23 _ss:5
GxIO_SPI::init
Set _cs :5
Set _dc :19
Set _rst :16
SPIClass::Begin:VSPI ,SCK:-1 MISO:-1 MOSI:-1 SS:-1
already init return func
*/

/*  4.更改RST IO
SPIClass::Begin:VSPI ,SCK:18 MISO:2 MOSI:23 SS:5
SPI.cpp INIT :_sck:18 _miso:2 _mosi:23 _ss:5
SPI.cpp INIT :_sck:18 _miso:2 _mosi:23 _ss:5
GxIO_SPI::init
Set _cs :5
Set _dc :19
Set _rst :12
SPIClass::Begin:VSPI ,SCK:-1 MISO:-1 MOSI:-1 SS:-1
already init return func
*/