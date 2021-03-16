
#pragma once

#if defined(LILYGO_T5_V213)

#define EPD_MOSI                (23)
#define EPD_MISO                (-1)
#define EPD_SCLK                (18)
#define EPD_CS                  (5)

#define EPD_BUSY                (4)
#define EPD_RSET                (16)
#define EPD_DC                  (17)

#define SDCARD_CS               (13)
#define SDCARD_MOSI             (15)
#define SDCARD_MISO             (2)
#define SDCARD_SCLK             (14)

#define BUTTON_1                (39)
#define BUTTONS                 {39}

#define BUTTON_COUNT            (1)

#define LED_PIN                 (19)
#define LED_ON                  (LOW)

#define ADC_PIN                 (35)

#define _HAS_ADC_DETECTED_
#define _HAS_LED_
#define _HAS_SDCARD_

#elif defined(LILYGO_T5_V22)

#define EPD_MOSI                (23)
#define EPD_MISO                (2)
#define EPD_SCLK                (18)
#define EPD_CS                  (5)

#define EPD_BUSY                (4)
#define EPD_RSET                (12)
#define EPD_DC                  (19)

#define SDCARD_CS               (13)

#define BUTTON_1                (37)
#define BUTTON_2                (38)
#define BUTTON_3                (39)

#define BUTTONS                 {37,38,39}
#define BUTTON_COUNT            (3)

#define LED_PIN                 (26)
#define LED_ON                  (HIGH)

#define ADC_PIN                 (35)

#define SPERKER_PIN             (25)

#define LEDC_CHANNEL_0          (0)
#define _HAS_ADC_DETECTED_
#define _HAS_LED_
#define _HAS_SPEAKER_
#define _BUILTIN_DAC_
#define _USE_SHARED_SPI_BUS_
#define _HAS_SDCARD_

#elif defined(LILYGO_T5_V24)

#define EPD_MOSI                (23)
#define EPD_MISO                (-1) //elink no use
#define EPD_SCLK                (18)

#define EPD_BUSY                (4)
#define EPD_RSET                (16)
#define EPD_DC                  (17)
#define EPD_CS                  (5)

#define SDCARD_CS               (13)
#define SDCARD_MOSI             (15)
#define SDCARD_MISO             (2)
#define SDCARD_SCLK             (14)

#define BUTTON_1                (37)
#define BUTTON_2                (38)
#define BUTTON_3                (39)

#define SPK_POWER_EN                (19)

#define BUTTONS                 {37,38,39}
#define BUTTON_COUNT            (3)

#define LED_PIN                 (26)
#define LED_ON                  (LOW)

#define ADC_PIN                 (35)

#define SPERKER_PIN             (25)

#define LEDC_CHANNEL_0          (0)
#define _HAS_ADC_DETECTED_
#define _HAS_LED_
#define _HAS_SPEAKER_
#define _BUILTIN_DAC_
#define _HAS_SDCARD_
#define _HAS_PWR_CTRL_
#elif defined(LILYGO_T5_V28)

#define EPD_MOSI                (23)
#define EPD_MISO                (-1)
#define EPD_SCLK                (18)
#define EPD_CS                  (5)

#define EPD_BUSY                (4)
#define EPD_RSET                (16)
#define EPD_DC                  (17)

#define SDCARD_CS               (13)
#define SDCARD_MOSI             (15)
#define SDCARD_MISO             (2)
#define SDCARD_SCLK             (14)

#define BUTTON_1                (37)
#define BUTTON_2                (38)
#define BUTTON_3                (39)

#define IIS_WS                  (25)
#define IIS_BCK                 (26)
#define IIS_DOUT                (19)

#define ICS43434_WS             (33)
#define ICS43434_BCK            (32)
#define ICS43434_DIN            (27)

#define I2C_SDA                 (21)
#define I2C_SCL                 (22)

#define BUTTONS                 {37,38,39}
#define BUTTON_COUNT            (3)

#define LED_PIN                 (22)
#define LED_ON                  (HIGH)

#define ADC_PIN                 (35)

#define _HAS_ADC_DETECTED_
#define _HAS_LED_
// #define _HAS_SPEAKER_
#define _HAS_SDCARD_

#else
#error "Please select model !!!"
#endif