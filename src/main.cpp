#include <Arduino.h>
#include <Wire.h>
#include <Ticker.h>
#include "DS3231.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ST7735.h"
#include <SPI.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include "ESP8266WiFi.h"
#include "ESP8266WebServer.h"

#define LED_PIN					16
#define BLINK_DELAY_MS			500

#define DEFAULT_TEXT_COLOR		ST7735_WHITE
#define DEFAULT_TEXT_BG_COLOR	ST7735_BLACK

#define TFT_CS					D8
#define TFT_RST					D4
#define TFT_DC					D3
#define TFT_SDA					D7
#define TFT_SCK					D5

#define ONE_WIRE_BUS			10

DS3231_datetime_t datetime;

Ticker ticker;

uint16_t blink_ticks;
uint16_t time_echo;

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

ESP8266WebServer server(80);

float temp_C = 0;
int device_count = 0;

const char* ssid = "Balancer-WiFi";

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
		if (device_count > 0)
		{
			sensors.requestTemperatures();
			temp_C = sensors.getTempCByIndex(0);
		}
		
		tft.setTextColor(DEFAULT_TEXT_COLOR, DEFAULT_TEXT_BG_COLOR);
		tft.setTextSize(1);
		tft.setCursor(20, 5);

		tft.printf("%02i.%02i.%4i  %02i:%02i:%02i", datetime.day_month, datetime.month, datetime.year, datetime.hour, datetime.minute, datetime.second);

		tft.setTextSize(5);
		tft.setCursor(25, 28);
		tft.printf("%.1f", temp_C);
	}

	// blink
	digitalWrite(LED_PIN, (blink_ticks >= BLINK_DELAY_MS));
	inc100ms_tick(&blink_ticks, BLINK_DELAY_MS * 2);
}

void setup()
{
	// Настройка порта монитора
	Serial.begin(74880);

	// Инициализация I2C
	Serial.println("Init wire");
	Wire.begin(PIN_WIRE_SDA, PIN_WIRE_SCL);

	Serial.println("Init sensor");
	sensors.begin();
	device_count = sensors.getDeviceCount();

	

	
	Serial.println("Init TFT");
	tft.initR(INITR_BLACKTAB);
	tft.setRotation(3);
	tft.fillScreen(DEFAULT_TEXT_BG_COLOR);


	//
	pinMode(LED_PIN, OUTPUT);

	//
	ticker.attach_ms(100, tick_100ms);
}

void loop()
{

}