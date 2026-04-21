#include "main.h"

#define LED_PIN					16
#define BLINK_DELAY_MS			500

#define DEFAULT_TEXT_COLOR		ST7735_WHITE
#define COLD_TEXT_COLOR			ST7735_BLUE
#define HOT_TEXT_COLOR			ST7735_RED
#define DEFAULT_TEXT_BG_COLOR	ST7735_BLACK

#define TFT_CS					D8
#define TFT_RST					D4
#define TFT_DC					D3
#define TFT_SDA					D7
#define TFT_SCK					D5

#define ONE_WIRE_BUS			10
#define DS18B20MODEL			0x28

DS3231_datetime_t datetime;

bool blink_state = false;
step_e step;

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

ESP8266WebServer web_server(80);

float temp_C = 0;
uint8_t temp_min = DEF_MIN_TEMP;
uint8_t temp_max = DEF_MAX_TEMP;

String wifi_ssid = "Balancer-WiFi";
String wifi_password = "81726354";

/* Настройки IP адреса */
IPAddress local_ip(192, 168, 88, 1);
IPAddress subnet(255, 255, 255 ,0);

uint16_t delay_millis = 0;
unsigned long time_millis = 0;

void blink_toggle()
{
	digitalWrite(LED_PIN, blink_state);
	blink_state = !blink_state;
}

void screen_display()
{
	tft.setTextColor(DEFAULT_TEXT_COLOR, DEFAULT_TEXT_BG_COLOR);
	tft.setTextSize(1);
	tft.setCursor(20, 5);
	tft.printf("%02i.%02i.%4i  %02i:%02i:%02i", datetime.day_month, datetime.month, datetime.year, datetime.hour, datetime.minute, datetime.second);

	tft.setCursor(10,113);
	tft.printf("%d.%d.%d.%d   %s", local_ip[0], local_ip[1], local_ip[2], local_ip[3], wifi_password);

	uint16_t circle_color = DEFAULT_TEXT_BG_COLOR;

	tft.setTextSize(6);

	if (temp_C > temp_max)
	{
		tft.setTextColor(HOT_TEXT_COLOR, DEFAULT_TEXT_BG_COLOR);
		circle_color = COLD_TEXT_COLOR;
	}
	else if (temp_C < temp_min)
	{
		tft.setTextColor(COLD_TEXT_COLOR, DEFAULT_TEXT_BG_COLOR);			
		circle_color = HOT_TEXT_COLOR;
	}
	else
	{
		tft.setTextColor(DEFAULT_TEXT_COLOR, DEFAULT_TEXT_BG_COLOR);
	}

	tft.fillCircle(80, 90, 12, circle_color);

	tft.setCursor(10, 21);
	tft.printf("%.1f", temp_C);

	tft.setTextSize(4);

	tft.setCursor(10, 75);
	tft.setTextColor(COLD_TEXT_COLOR,DEFAULT_TEXT_BG_COLOR);
	tft.printf("%d", temp_min);

	tft.setCursor(105, 75);
	tft.setTextColor(HOT_TEXT_COLOR,DEFAULT_TEXT_BG_COLOR);
	tft.printf("%d", temp_max);
}

void handle_NotFound()
{
	web_server.send(200, "text/plain", "Not found");
}

void redirect_root()
{
	web_server.sendHeader("Location", "/",true);
	web_server.send(302, "text/plane","");
}

void handle_root()
{
	web_server.send(200, "text/html", HTML_main_page(temp_min, temp_max));
}

void handle_save()
{
	redirect_root();
}

void handle_sync()
{
	redirect_root();
}

void setup()
{
	// Настройка порта монитора
	Serial.begin(74880);

	// Чтение значений из EEPROM
	temp_min = EEPROM.read(MIN_TEMP_ADDR);
	if ((temp_min < MINIMUM_TEMP) || (temp_min > MAXIMUM_TEMP))
	{
		temp_min = DEF_MIN_TEMP;
	}

	temp_max = EEPROM.read(MAX_TEMP_ADDR);
	if ((temp_max < MINIMUM_TEMP) || (temp_max > MAXIMUM_TEMP))
	{
		temp_max = DEF_MAX_TEMP;
	}

	// Инициализация I2C
	Wire.begin(PIN_WIRE_SDA, PIN_WIRE_SCL);
	DS3231_get_time(&Wire, &datetime);
	Serial.println("Init wire");

	// Инициализация TFT
	tft.initR(INITR_BLACKTAB);
	tft.setRotation(3);
	tft.fillScreen(DEFAULT_TEXT_BG_COLOR);
	Serial.println("Init TFT");

	// Инициализация термодатчика
	sensors.begin();
	sensors.setResolution(9);	
	Serial.println("Init temp sensor");

	// Инициализация WiFi
	WiFi.mode(WIFI_AP);
	WiFi.softAPConfig(local_ip, local_ip, subnet);
	WiFi.softAP(wifi_ssid, wifi_password);
	Serial.println("Init Wi-Fi");

	// Инициализация web сервера
	web_server.on("/", handle_root);
	web_server.on("/save", handle_save);
	web_server.on("/sync", handle_sync);
	web_server.onNotFound(handle_NotFound);
	web_server.begin();
	Serial.println("Init web server");
	delay(100);

	//
	pinMode(LED_PIN, OUTPUT);

	//
	time_millis = millis();
	step = READ_TIME;
}

void loop()
{
	web_server.handleClient();
	
	uint16_t delta = millis() - time_millis;
	
	if (delta >= 1000)
	{
		step = READ_TIME;
		screen_display();
		time_millis += 1000;
	}
	else if ((step == READ_TIME) && (delta >= 10))
	{
		DS3231_get_time(&Wire, &datetime);
		step = REQUEST_TEMP;
		blink_toggle();
	}
	else if ((step == REQUEST_TEMP) && (delta >= 50))
	{
		sensors.requestTemperatures();
		step = GET_TEMP;
	}
	else if ((step == GET_TEMP) && (delta >= 200))
	{
		temp_C = sensors.getTempCByIndex(0);
		step = IDLE;
		blink_toggle();
	}
}