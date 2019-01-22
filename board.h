
#define TTGO_T5_1_2 0
#define TTGO_T5_2_1 0
#define TTGO_T5_2_2 1
#define TTGO_T5_2_3 0

#if TTGO_T5_1_2
// The program does not currently support
#define ELINK_BUSY 4
#define ELINK_RESET 16
#define ELINK_DC 17
#define ELINK_SS 5

#define SPI_MOSI 23
#define SPI_MISO -1 //elink no use
#define SPI_CLK 18

#define SDCARD_SS 13
#define SDCARD_MOSI 15
#define SDCARD_MISO 2
#define SDCARD_CLK  14

#define BUTTON_1 37
#define BUTTON_2 38
#define BUTTON_3 39

#define SPEAKER_OUT 25

#elif TTGO_T5_2_1

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