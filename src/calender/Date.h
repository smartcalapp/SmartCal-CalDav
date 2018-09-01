//
// Created by Garrett Battaglia on 8/31/18.
//

#ifndef SMARTCAL_CALDAV_DATE_H
#define SMARTCAL_CALDAV_DATE_H


#include <cstdint>

bool isValidDate(uint_fast16_t year, uint_fast8_t day, uint_fast8_t month);

class Date
{
	private:
		uint_fast16_t _year;
		uint_fast8_t _day;
		uint_fast8_t _month;
	public:
		Date()
		{

		}

		Date(uint_fast16_t year, uint_fast8_t day, uint_fast8_t month)
		{
			if (isValidDate(year, day, month)) {
				_year = year;
				_day = day;
				_month = month;
			} else {
				//TODO exept
			}
		}

		uint_fast16_t getyear() const
		{
			return _year;
		}

		void setyear(uint_fast16_t year)
		{
			if (isValidDate(year, _day, _month)) {
				Date::_year = year;
			} else {
				//TODO exept
			}
		}

		uint_fast8_t getday() const
		{
			return _day;
		}

		void setday(uint_fast8_t day)
		{
			if (isValidDate(_year, day, _month)) {
				Date::_day = day;
			} else {
				//TODO exept
			}
		}

		uint_fast8_t getmonth() const
		{
			return _month;
		}

		void setmonth(uint_fast8_t month)
		{
			if (isValidDate(_year, _day, month)) {
				Date::_month = month;
			} else {
				//TODO exept
			}
		}
};

Date epochTime2Date(uint_fast64_t epoch);

#endif //SMARTCAL_CALDAV_DATE_H