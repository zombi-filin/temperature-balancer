#ifndef __MAIN_H__
#define __MAIN_H__

#include <Arduino.h>
#include <EEPROM.h>

#include <Ticker.h>
#include <SPI.h>
#include "Adafruit_GFX.h"
#include "Adafruit_ST7735.h"
#include <Wire.h>
#include "DS3231.h"
#include <OneWire.h>
#include <DallasTemperature.h>
#include "ESP8266WiFi.h"
#include "ESP8266WebServer.h"
#include "web_content.h"
#include "consts.h"

enum step_e {
	IDLE = 0,
	READ_TIME,
	REQUEST_TEMP,
	GET_TEMP
};

#endif