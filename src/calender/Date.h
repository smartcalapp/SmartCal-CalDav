//
// Created by Garrett Battaglia on 8/31/18.
//

#ifndef SMARTCAL_CALDAV_DATE_H
#define SMARTCAL_CALDAV_DATE_H


#include <cstdint>
#include <ostream>
#include <iomanip>

bool isValidDate(uint_fast16_t year, uint_fast16_t day, uint_fast16_t month);

class Date {
	private:
		uint_fast16_t _year;
		uint_fast16_t _day;
		uint_fast16_t _month;
	public:
		Date() = default;

		/**
		 * create date based on day, month, year
		 * @param year
		 * @param day
		 * @param month
		 */
		Date(uint_fast16_t year, uint_fast16_t day, uint_fast16_t month) {
			if (isValidDate(year, day, month)) {
				_year = year ;
				_day = day;
				_month = month;
			} else {
				throw  std::domain_error("invaild date");
			}
		}
		/**
		 * create date based of unix tm
		 * @param time
		 */
		Date(tm* time){
			_year = time->tm_year + 1900;
			_month = time->tm_mon + 1;
			_day = time->tm_mday;
		}

		/**
		 * output date in ICAL format
		 * @param os
		 * @param date
		 * @return
		 */
		friend std::ostream &operator<<(std::ostream &os, const Date &date) {
			os << std::setfill('0') << std::setw(2) << date._year << std::setw(2) << date._month << std::setw(2)
			   << date._day;
			return os;
		}
		/**
		 * get year
		 * @return year
		 */
		uint_fast16_t getyear() const {
			return _year;
		}
		/**
		 * set year
		 * @param year
		 */
		void setyear(uint_fast16_t year) {
			if (isValidDate(year, _day, _month)) {
				Date::_year = year;
			} else {
				throw std::domain_error("seting year would make date invalid");
			}
		}

		/**
		 * get day
		 * @return day
		 */
		uint_fast16_t getday() const {
			return _day;
		}
		/**
		 * set day
		 * @param day
		 */
		void setday(uint_fast16_t day) {
			if (isValidDate(_year, day, _month)) {
				Date::_day = day;
			} else {
				throw  std::domain_error("seting day would make date invalid");
			}
		}
		/**
		 * get month
		 * @return month
		 */
		uint_fast16_t getmonth() const {
			return _month;
		}
		/**
		 * set month
		 * @param month
		 */
		void setmonth(uint_fast16_t month) {
			if (isValidDate(_year, _day, month)) {
				Date::_month = month;
			} else {
				throw  std::domain_error("seting month would make date invalid");
			}
		}
};

Date epochTime2Date(int_fast64_t epoch);

#endif //SMARTCAL_CALDAV_DATE_H