//
// Created by Garrett Battaglia on 8/31/18.
//

#include "Time.h"

bool isValidTime(uint_fast8_t hour, uint_fast8_t min, uint_fast8_t sec)
{
	return (hour > 0 && hour < 24) && (min > 0 && min < 60) && (sec > 0 && sec < 60);
}