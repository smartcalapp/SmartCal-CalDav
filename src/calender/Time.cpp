//
// Created by Garrett Battaglia on 8/31/18.
//

#include "Time.h"

#define EPOCH_SEC_PER_DAY 86400
#define MINS_PER_HR 60
#define SECS_PER_MIN 60
#define SECS_PER_HR (MINS_PER_HR*SECS_PER_MIN)


bool isValidTime(uint_fast16_t hour, uint_fast16_t min, uint_fast16_t sec) {
	return (hour > 0 && hour < 24) && (min > 0 && min < 60) && (sec > 0 && sec < 60);
}

Time epochTime2Time(int_fast64_t epoch) {
	uint_fast16_t secsOfDay = epoch % EPOCH_SEC_PER_DAY;
	uint_fast16_t hours = secsOfDay / SECS_PER_HR;
	secsOfDay %= SECS_PER_HR;
	uint_fast16_t mins = secsOfDay / SECS_PER_MIN;
	secsOfDay %= SECS_PER_MIN;
	uint_fast16_t secs = secsOfDay;
	return Time(hours, mins, secs);
}