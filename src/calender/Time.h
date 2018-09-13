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

		/**
		 * create time based on hour, min, sec
		 * @param hour
		 * @param min
		 * @param sec
		 */
		Time(uint_fast16_t hour, uint_fast16_t min, uint_fast16_t sec) {
			if (isValidTime(hour, min, sec)) {
				_hour = hour;
				_min = min;
				_sec = sec;
			} else {
				throw  std::domain_error("invalid time");
			}
		}

		/**
		 * create time based on unix tm
		 * @param time
		 */
		Time(tm* time) {
			_hour = time->tm_hour;
			_min = time ->tm_min;
			_sec = time->tm_sec;
		}

		/**
		 * get hour
		 * @return hour
		 */
		uint_fast16_t gethour() const {
			return _hour;
		}

		/**
		 * set hour
		 * @param hour
		 */
		void sethour(uint_fast16_t hour) {
			if (isValidTime(hour, _min, _sec)) {
				Time::_hour = hour;
			} else {
				throw  std::domain_error("seting hour would make time invalid");
			}
		}

		/**
		 * get min
		 * @return min
		 */
		uint_fast16_t getmin() const {
			return _min;
		}

		/**
		 * set min
		 * @param min
		 */
		void setmin(uint_fast16_t min) {
			if (isValidTime(_hour, min, _sec)) {
				Time::_min = min;
			} else {
				throw  std::domain_error("seting min would make time invalid");
			}
		}

		/**
		 * get second
		 * @return second
		 */
		uint_fast16_t getsec() const {
			return _sec;
		}

		/**
		 * set second
		 * @param sec
		 */
		void setsec(uint_fast16_t sec) {
			if (isValidTime(_hour, _min, sec)) {
				Time::_sec = sec;
			} else {
				throw  std::domain_error("seting sec would make time invalid");
			}
		}

		/**
		 * output time in ICAL format
		 * @param os
		 * @param time
		 * @return
		 */
		friend std::ostream &operator<<(std::ostream &os, const Time &time) {
			os << std::setfill('0') << std::setw(2) << time._hour << std::setw(2) << time._min << std::setw(2)
			   << time._sec << "Z";
			return os;
		}
};

Time epochTime2Time(int_fast64_t epoch);


#endif //SMARTCAL_CALDAV_TIME_H
