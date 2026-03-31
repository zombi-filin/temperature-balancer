#ifndef __WEB_CONTENT_H__
#define __WEB_CONTENT_H__

#include <Arduino.h>
#include "DS3231.h"

String HTML_main_page(DS3231_datetime_t* datetime, float current_temp);


#endif