//
// Created by Garrett Battaglia on 8/31/18.
//

#ifndef SMARTCAL_CALDAV_TIME_H
#define SMARTCAL_CALDAV_TIME_H


#include <cstdint>

bool isValidTime(uint_fast8_t hour, uint_fast8_t min, uint_fast8_t sec);


class Time {
		private:
				uint_fast8_t _hour;
				uint_fast8_t _min;
				uint_fast8_t _sec;
		public:
				Time() {

				}

				Time(uint_fast8_t hour, uint_fast8_t min, uint_fast8_t sec) {
					if (isValidTime(hour, min, sec)) {
						_hour = hour;
						_min = min;
						_sec = sec;
					} else {
						//todo exception
					}
				}

				uint_fast8_t gethour() const {
					return _hour;
				}

				void sethour(uint_fast8_t hour) {
					if (isValidTime(hour, _min, _sec)) {
						Time::_hour = hour;
					} else {
						//todo exception
					}
				}

				uint_fast8_t getmin() const {
					return _min;
				}

				void setmin(uint_fast8_t min) {
					if (isValidTime(_hour, min, _sec)) {
						Time::_min = min;
					} else {
						//todo exception
					}
				}

				uint_fast8_t getsec() const {
					return _sec;
				}

				void setsec(uint_fast8_t sec) {
					if (isValidTime(_hour, _min, sec)) {
						Time::_sec = sec;
					} else {
						//TODO exception
					}
				}

};

Time epochTime2Time(int_fast64_t epoch);


#endif //SMARTCAL_CALDAV_TIME_H
