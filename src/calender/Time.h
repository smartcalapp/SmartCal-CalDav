//
// Created by Garrett Battaglia on 8/31/18.
//

#ifndef SMARTCAL_CALDAV_TIME_H
#define SMARTCAL_CALDAV_TIME_H


#include <cstdint>
#include <ostream>
#include <iomanip>

bool isValidTime(uint_fast16_t hour, uint_fast16_t min, uint_fast16_t sec);


class Time {
	private:
		uint_fast16_t _hour;
		uint_fast16_t _min;
		uint_fast16_t _sec;
	public:
		Time() = default;

		Time(uint_fast16_t hour, uint_fast16_t min, uint_fast16_t sec) {
			if (isValidTime(hour, min, sec)) {
				_hour = hour;
				_min = min;
				_sec = sec;
			} else {
				throw  std::domain_error("invalid time");
			}
		}

		uint_fast16_t gethour() const {
			return _hour;
		}

		void sethour(uint_fast16_t hour) {
			if (isValidTime(hour, _min, _sec)) {
				Time::_hour = hour;
			} else {
				throw  std::domain_error("seting hour would make time invalid");
			}
		}

		uint_fast16_t getmin() const {
			return _min;
		}

		void setmin(uint_fast16_t min) {
			if (isValidTime(_hour, min, _sec)) {
				Time::_min = min;
			} else {
				throw  std::domain_error("seting min would make time invalid");
			}
		}

		uint_fast16_t getsec() const {
			return _sec;
		}

		void setsec(uint_fast16_t sec) {
			if (isValidTime(_hour, _min, sec)) {
				Time::_sec = sec;
			} else {
				throw  std::domain_error("seting sec would make time invalid");
			}
		}

		friend std::ostream &operator<<(std::ostream &os, const Time &time) {
			os << std::setfill('0') << std::setw(2) << time._hour << std::setw(2) << time._min << std::setw(2)
			   << time._sec << "Z";
			return os;
		}
};

Time epochTime2Time(int_fast64_t epoch);


#endif //SMARTCAL_CALDAV_TIME_H
