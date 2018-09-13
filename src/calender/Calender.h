#include <utility>

//
// Created by Garrett Battaglia on 8/31/18.
//

#ifndef SMARTCAL_CALDAV_CALENDER_H
#define SMARTCAL_CALDAV_CALENDER_H

#include <string>
#include <ostream>
#include "Appointment.h"
#include "iCalDefs.h"

class Calender {
	private:
		Appointment **_events;
		int lastAssinged = 0;
		int numApts;
	public:
		Calender() = default;

		Calender(int numberOfApts) {
			_events = new Appointment *[numberOfApts];
			numApts = numberOfApts;
		}

		void add(int_fast64_t createEpoch, int_fast64_t startEpoch, int_fast64_t endEpoch, std::string name,
		         std::string uuid) {
			_events[lastAssinged] = new Appointment(createEpoch, startEpoch, endEpoch, std::move(name), uuid);
			lastAssinged++;
		}

		void add(tm *createEpoch, tm *startEpoch, tm *endEpoch, std::string name, std::string uuid) {
			_events[lastAssinged] = new Appointment(createEpoch, startEpoch, endEpoch, std::move(name), uuid);
			lastAssinged++;
		}

		friend std::ostream &operator<<(std::ostream &os, const Calender &calender) {
			os << "BEGIN:VCALENDAR" << ICAL_LINE_SEP << "VERSION:2.0" << ICAL_LINE_SEP << "PRODID:" << PROD_ID << " "
			   << VERSION_ID << ICAL_LINE_SEP;
			for (int i = 0; i < calender.numApts; i++) {
				os << *(calender._events[i]);
			}
			os << "END:VCALENDAR";
			return os;
		}
};


#endif //SMARTCAL_CALDAV_CALENDER_H
