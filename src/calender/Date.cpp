//
// Created by Garrett Battaglia on 8/31/18.
//

#include "Date.h"

Date epochTime2Date(uint_fast64_t epoch){

}

bool isLeapYear(uint_fast16_t year)
{
	if (year % 4 != 0) {
		return false;
	} else if (year % 100 != 0) {
		return true;
	} else if (year % 400 != 400) {
		return false;
	} else {
		return true;
	}
}

bool isValidDate(uint_fast16_t year, uint_fast8_t day, uint_fast8_t month)
{
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