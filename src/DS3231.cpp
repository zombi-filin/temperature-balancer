#include "DS3231.h"


// Convert normal decimal numbers to binary coded decimal
uint8_t decToBcd(uint8_t val)
{
    return( (val/10*16) + (val%10) );
}

void DS3231_get_time(TwoWire *wire, DS3231_datetime_t *datetime)
{
    uint8_t read_data;
    uint8_t h_part;
    uint8_t l_part;

    wire->beginTransmission(DS3231_I2C_ADDRESS);
    wire->write(0x00);
    wire->endTransmission();

    wire->requestFrom(DS3231_I2C_ADDRESS, 7);
    
    read_data = wire->read();
    l_part = read_data & 0x0F;
    h_part = (read_data & 0x70) >> 4;
    datetime->second = (h_part * 10) + l_part;

    read_data = wire->read();
    l_part = read_data & 0x0F;
    h_part = (read_data & 0x70) >> 4;
    datetime->minute = (h_part * 10) + l_part;

    read_data = wire->read();
    l_part = read_data & 0x0F;
    uint8_t _12h_mode = (read_data & 0x40) >> 6;
    if (_12h_mode) {
		h_part = (read_data & 0x10) >> 4;// 0b00010000
	}
	else {
		h_part = (read_data & 0x30) >> 4;//0b00110000
	}
    datetime->hour = (h_part * 10) + l_part;
 
    datetime->day_week = wire->read() & 0x07;

    read_data = wire->read();
    l_part = read_data & 0x0F;
    h_part = (read_data & 0x30) >> 4;
    datetime->day_month = (h_part * 10) + l_part;

    read_data = wire->read();
    l_part = read_data & 0x0F;
    h_part = (read_data & 0x10) >> 4;
    datetime->month = (h_part * 10) + l_part;

    read_data = wire->read();
    l_part = read_data & 0x0F;
    h_part = (read_data & 0xF0) >> 4;
    datetime->year = 2000 + (h_part * 10) + l_part;
}

void DS3231_set_time(TwoWire *wire, DS3231_datetime_t *datetime)
{
    wire->beginTransmission(DS3231_I2C_ADDRESS);
    wire->write(0x00);
    wire->write(decToBcd(datetime->second));
    wire->write(decToBcd(datetime->minute));
    wire->write(decToBcd(datetime->hour));
    wire->write(decToBcd(datetime->day_week));
    wire->write(decToBcd(datetime->day_month));
    wire->write(decToBcd(datetime->month));
    wire->write(decToBcd(datetime->year));
    wire->endTransmission();
}
