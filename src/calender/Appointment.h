#include <utility>

//
// Created by Garrett Battaglia on 8/31/18.
//


#ifndef SMARTCAL_CALDAV_APPOINTMENT_H
#define SMARTCAL_CALDAV_APPOINTMENT_H


#include <string>
#include <ostream>
#include <iostream>
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
		std::string _uuid;
	public:
		Appointment() = default;

		/**
		 * create an appointment off an epoch time
		 * @param createEpoch the epoch time that the appointment was created, needed by ICAL
		 * @param startEpoch the epoch time that the appointment starts
		 * @param endEpoch the epoch time that the appointment ends
		 * @param name the name of the appointment
		 * @param uuid the globaly unique ID needed by ICAL
		 */
		Appointment(int_fast64_t createEpoch, int_fast64_t startEpoch, int_fast64_t endEpoch, std::string name,
		            std::string uuid) {
			_icalStampDate = epochTime2Date(createEpoch);
			_icalStampTime = epochTime2Time(createEpoch);
			_startDate = epochTime2Date(startEpoch);
			_endDate = epochTime2Date(endEpoch);
			_startTime = epochTime2Time(startEpoch);
			_endTime = epochTime2Time(endEpoch);
			_name = std::move(name);
			_uuid = std::move(uuid);
		}

		/**
		 * create an appointemnt based off unix tm structure
		 * @param createEpoch create tm structure
		 * @param startEpoch start tm structure
		 * @param endEpoch end tm structure
		 * @param name the name of the appointment
		 * @param uuid the globaly unique ID needed by ICAL
		 */
		Appointment(tm *createEpoch, tm *startEpoch, tm *endEpoch, std::string name, std::string uuid) {
			_icalStampDate = Date(createEpoch);
			_icalStampTime = Time(createEpoch);
			_startDate = Date(startEpoch);
			_endDate = Date(endEpoch);
			_startTime = Time(startEpoch);
			_endTime = Time(endEpoch);
			_name = std::move(name);
			_uuid = std::move(uuid);
		}

		/**
 		* output the event in ICAL format, standard stream out op
 		* @param os
 		* @param appointment
 		* @return
 		*/
		friend std::ostream &operator<<(std::ostream &os, const Appointment &appointment) {
			os << "BEGIN:VEVENT" << ICAL_LINE_SEP << "DTSTAMP: " << appointment._icalStampDate << "T"
			   << appointment._icalStampTime << ICAL_LINE_SEP << "DTSTART:" << appointment._startDate << "T"
			   << appointment._startTime << ICAL_LINE_SEP << "DTEND:" << appointment._endDate << "T"
			   << appointment._endTime << ICAL_LINE_SEP << "SUMMARY:" << appointment._name << ICAL_LINE_SEP << "UID:"
			   << appointment._uuid << ICAL_LINE_SEP << "END:VEVENT" << ICAL_LINE_SEP;
			return os;
		}

};


#endif //SMARTCAL_CALDAV_APPOINTMENT_H
