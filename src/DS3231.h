#ifndef __DS3231_H__
#define __DS3231_H__

#include <Wire.h>

#define DS3231_I2C_ADDRESS  0x68

struct DS3231_datetime_t
{
    uint16_t year;      // Год
    uint8_t month;      // Месяц
    uint8_t day_month;  // День 1-31
    uint8_t day_week;   // День недели 1=Воскресенье, 7=Суббота
    uint8_t hour;       // Часы
    uint8_t minute;     // Минуты
    uint8_t second;     // Секунды
};


#endif // __DS3231_H__