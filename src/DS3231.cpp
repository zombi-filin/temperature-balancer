#include "DS3231.h"


// Convert normal decimal numbers to binary coded decimal
uint8_t decToBcd(uint8_t val)
{
    return( (val/10*16) + (val%10) );
}
// Convert binary coded decimal to normal decimal numbers
uint8_t bcdToDec(uint8_t val)
{
    return ((((val >> 4) & 0x0F) * 10) + (val & 0x0F)) ;
}

void DS3231_get_time(TwoWire *wire, DS3231_datetime_t *datetime)
{
    wire->beginTransmission(DS3231_I2C_ADDRESS);
    wire->write(0x00);
    wire->endTransmission();
    wire->requestFrom(DS3231_I2C_ADDRESS, 7);
    datetime->second = bcdToDec(wire->read() & 0x7f);
    datetime->minute = bcdToDec(wire->read());
    datetime->hour = bcdToDec(wire->read() & 0x3f);
    datetime->day_week = bcdToDec(wire->read());
    datetime->day_month = bcdToDec(wire->read());
    datetime->month = bcdToDec(wire->read());
    datetime->year = bcdToDec(wire->read());
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
