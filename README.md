# temperature-balancer
Температурный балансир


## Периферия

### TFT LCD 1.8 дюйма

| ST7735 (SPI) | NodeMCU |
|---|---|
| VCC | 3V3 ( +3.3 ) |
| GND | GND |
| CS | D8 ( GPIO15 )|
| RESET | D4 ( GPIO2 ) |
| A0 | D3 ( GPIO0 )|
| SDA | D7 ( GPIO13 )|
| SCK | D5 ( GPIO14 ) |
| LED | 3V3 ( +3.3 ) |


| SD | NodeMCU |
|---|---|
| SD_CS | RX ( GPIO3)  |
| SD_MOSI | D7 ( GPIO13 ) |
| SD_MISO | D6 ( GPIO12 )|
| SD_SCK | D5 ( GPIO14 ) |

### Часы реального времени DS3231

| DS3231 (I2C) | NodeMCU |
|---|---|
| SCL | D1 ( GPIO5 ) |
| SDA | D2 ( GPIO4 ) |
| VCC | 3V3 ( +3.3 ) |
| GND | GND |

### Термодатчик DS18B20

| DS18B20 | NodeMCU | |
|---|---|---|
| VCC | GND ||
| DATA | SD3 ( GPIO10 ) | DATA --- 4k7 -- 3V3  |
| GND | GND ||