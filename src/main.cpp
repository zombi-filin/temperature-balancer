#include <Arduino.h>
#include <Wire.h>
#include "DS3231.h"

#define LED_PIN       16
#define BLINK_DELAY   500

void setup() {
	// Инициализация I2C
	Wire.begin(PIN_WIRE_SDA, PIN_WIRE_SCL);

	// Настройка порта монитора
	Serial.begin(74880);
  
	//
	pinMode(LED_PIN, OUTPUT);
}

void loop() {
	digitalWrite(LED_PIN, HIGH);
	delay(BLINK_DELAY);
	digitalWrite(LED_PIN,LOW);
	delay(BLINK_DELAY);

	Serial.println("Loop");
}