//
// Created by Garrett Battaglia on 8/31/18.
//

#include "Time.h"

#define EPOCH_SEC_PER_DAY 86400
#define MINS_PER_HR 60
#define SECS_PER_MIN 60
#define SECS_PER_HR (MINS_PER_HR*SECS_PER_MIN)

/**
 * check if time is valid
 * @param hour
 * @param min
 * @param sec
 * @return true if time is valid
 */
bool isValidTime(uint_fast16_t hour, uint_fast16_t min, uint_fast16_t sec) {
	return (hour > 0 && hour < 24) && (min > 0 && min < 60) && (sec > 0 && sec < 60);
}


//todo fix
/**
 * conver epoch timestamp to time object, dosen't currently work
 * @param epoch timestamp to covert
 * @return time object based off timestamp
 */
Time epochTime2Time(int_fast64_t epoch) {
	auto secsOfDay = static_cast<uint_fast16_t>(epoch % EPOCH_SEC_PER_DAY);
	auto hours = static_cast<uint_fast16_t>(secsOfDay / SECS_PER_HR);
	secsOfDay %= SECS_PER_HR;
	auto mins = static_cast<uint_fast16_t>(secsOfDay / SECS_PER_MIN);
	secsOfDay %= SECS_PER_MIN;
	uint_fast16_t secs = secsOfDay;
	return Time(hours, mins, secs);
}