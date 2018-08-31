//
// Created by Garrett Battaglia on 8/31/18.
//

#ifndef SMARTCAL_CALDAV_TIME_H
#define SMARTCAL_CALDAV_TIME_H


#include <cstdint>

class Time
{
	private:
		uint_fast8_t _hour;
		uint_fast8_t _min;
		uint_fast8_t _sec;
	public:
		Time(){

		}

		Time(uint_fast8_t hour, uint_fast8_t min, uint_fast8_t sec){
			_hour = hour;
			_min = min;
			_sec = sec;
		}

		uint_fast8_t gethour() const
		{
			return _hour;
		}

		void sethour(uint_fast8_t _hour)
		{
			Time::_hour = _hour;
		}

		uint_fast8_t getmin() const
		{
			return _min;
		}

		void setmin(uint_fast8_t _min)
		{
			Time::_min = _min;
		}

		uint_fast8_t getsec() const
		{
			return _sec;
		}

		void setsec(uint_fast8_t _sec)
		{
			Time::_sec = _sec;
		}
};


#endif //SMARTCAL_CALDAV_TIME_H
