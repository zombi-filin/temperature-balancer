#ifndef __DS3231_H__
#define __DS3231_H__

#include <stdint.h>
#include <Arduino.h>
#include <Wire.h>

#define DS3231_I2C_ADDRESS  0x68
typedef struct 
{
    uint16_t year;       // Год
    uint8_t month;      // Месяц
    uint8_t day_month;  // День 1-31
    uint8_t day_week;   // День недели 1=Воскресенье, 7=Суббота
    uint8_t hour;       // Часы
    uint8_t minute;     // Минуты
    uint8_t second;     // Секунды
}DS3231_datetime_t;


void DS3231_get_time(TwoWire *wire, DS3231_datetime_t* datetime);
void DS3231_set_time(TwoWire *wire,DS3231_datetime_t *datetime);

#endif // __DS3231_H__