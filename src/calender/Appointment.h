//
// Created by Garrett Battaglia on 8/31/18.
//

#ifndef SMARTCAL_CALDAV_APPOINTMENT_H
#define SMARTCAL_CALDAV_APPOINTMENT_H


#include <string>
#include <ostream>
#include "Date.h"
#include "Time.h"
#include "iCalDefs.h"

class Appointment {
	private:
		Date _icalStampDate;
		Time _icalStampTime;
		Date _startDate;
		Time _startTime;
		Date _endDate;
		Time _endTime;
		std::string _name;
	public:
		Appointment() {

		}

		Appointment(uint_fast64_t startEpoch, uint_fast64_t endEpoch, std::string name) {
			_startDate = epochTime2Date(startEpoch);
			_endDate = epochTime2Date(endEpoch);
			_startTime = epochTime2Time(startEpoch);
			_endTime = epochTime2Time(endEpoch);
			_name = name;
		}

		friend std::ostream &operator<<(std::ostream &os, const Appointment &appointment) {
			//TODO real time stamp
			os << "BEGIN:VEVENT" << ICAL_LINE_SEP << "DTSTAMP: " << appointment._icalStampDate << "T"
			   << appointment._icalStampTime << ICAL_LINE_SEP << "DTSTART:" << appointment._startDate << "T"
			   << appointment._startTime << "DTEND" << appointment._endDate << "T" << appointment._endTime
			   << "END:VEVENT";
			return os;
		}

};


#endif //SMARTCAL_CALDAV_APPOINTMENT_H
