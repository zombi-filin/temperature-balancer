#ifndef __WEB_CONTENT_H__
#define __WEB_CONTENT_H__

#include <Arduino.h>
#include "consts.h"
#include "DS3231.h"

String HTML_main_page(uint8_t temp_min, uint8_t temp_max);


#endif