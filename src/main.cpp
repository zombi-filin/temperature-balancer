#include <Arduino.h>
#include <Wire.h>
#include <Ticker.h>
#include "DS3231.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ST7735.h"
#include <SPI.h>

#define LED_PIN			16
#define BLINK_DELAY_MS	500

#define TFT_CS			D8
#define TFT_RST			D4
#define TFT_DC			D3
#define TFT_SDA			D7
#define TFT_SCK			D5

DS3231_datetime_t datetime;

Ticker ticker;

uint16_t blink_ticks;
uint16_t time_echo;

//Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_SDA, TFT_SCK, TFT_RST);
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

bool inc100ms_tick(uint16_t *ticks, uint16_t limit)
{
	(*ticks) += 100;

	if ((uint16_t)(*ticks) >= limit)
	{
		(*ticks) = 0;
		return true;
	}
	return false;
}

void tick_100ms()
{
	DS3231_get_time(&Wire, &datetime);
	
	if (inc100ms_tick(&time_echo, 1000))
	{
		tft.setTextColor(ST7735_WHITE);
		tft.setTextSize(1);
		tft.setCursor(20, 25);
		tft.printf("%i:%i:%i",datetime.hour, datetime.minute, datetime.second);
	}

	// blink
	digitalWrite(LED_PIN, (blink_ticks >= BLINK_DELAY_MS));
	inc100ms_tick(&blink_ticks, BLINK_DELAY_MS * 2);
}

void setup()
{
	// Инициализация I2C
	Wire.begin(PIN_WIRE_SDA, PIN_WIRE_SCL);

	// Настройка порта монитора
	Serial.begin(74880);
	
	
	tft.initR(INITR_BLACKTAB);
	tft.setRotation(3);
	tft.fillScreen(ST7735_BLACK);


	//
	pinMode(LED_PIN, OUTPUT);

	//
	ticker.attach_ms(100, tick_100ms);
}

void loop()
{

}