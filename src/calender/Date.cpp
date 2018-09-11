//
// Created by Garrett Battaglia on 8/31/18.
//

#include <iostream>
#include "Date.h"

#define EPOCH_SEC_PER_DAY 86400



bool isLeapYear(uint_fast16_t year) {
	if (year % 4 != 0) {
		return false;
	} else if (year % 100 != 0) {
		return true;
	} else {
		return year % 400 == 400;
	}
}

uint_fast16_t daysInMonth(uint_fast16_t month, uint_fast16_t year) {
	if (month == 2 && isLeapYear(year)) {
		return 29;
	}
	if (month == 2 && !isLeapYear(year)) {
		return 28;
	}
	if (month <= 7 && month % 2 == 1) {
		return 31;
	}
	if (month <= 7 && month % 2 == 0) {
		return 30;
	}
	if (month > 7 && month % 2 == 1) {
		return 30;
	}
	if (month > 7 && month % 2 == 0) {
		return 31;
	}
	return static_cast<uint_fast8_t>(-1);
}

Date epochTime2Date(int_fast64_t epoch) {
	uint_fast64_t daysSinceEpoch = abs(epoch / EPOCH_SEC_PER_DAY);
	uint_fast16_t year = 1970;
	uint_fast16_t month = 0;
	for (; daysSinceEpoch > (isLeapYear(year) ? 365 : 366); daysSinceEpoch -= isLeapYear(year) ? 365 : 366) {
		year++;
	}
	for (; daysSinceEpoch > daysInMonth(month, year); daysSinceEpoch -= daysInMonth(month, year)) {
		month++;
	}
	return Date(year, daysSinceEpoch, month);
}

bool isValidDate(uint_fast16_t year, uint_fast16_t day, uint_fast16_t month) {
	if (day < 1 || month < 1 || month > 12 || year < 1) {
		return false;
	}
	if (month == 2 && isLeapYear(year)) {
		return day <= 29;
	}
	if (month == 2 && !isLeapYear(year)) {
		return day <= 28;
	}
	if (month <= 7 && month % 2 == 1) {
		return day <= 31;
	}
	if (month <= 7 && month % 2 == 0) {
		return day <= 30;
	}
	if (month > 7 && month % 2 == 1) {
		return day <= 30;
	}
	if (month > 7 && month % 2 == 0) {
		return day <= 31;
	}
	return false;
}