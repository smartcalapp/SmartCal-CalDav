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
		/**
		 *
		 * @param numberOfApts number appointments to alloc
		 */
		Calender(int numberOfApts) {
			_events = new Appointment *[numberOfApts];
			numApts = numberOfApts;
		}
		/**
		 * add an appointment based on unix epoch
		 * @param createEpoch the epoch time that the appointment was created, needed by ICAL
		 * @param startEpoch the epoch time that the appointment starts
		 * @param endEpoch the epoch time that the appointment ends
		 * @param name the name of the appointment
		 * @param uuid the globaly unique ID needed by ICAL
		 */
		void add(int_fast64_t createEpoch, int_fast64_t startEpoch, int_fast64_t endEpoch, std::string name,
		         std::string uuid) {
			_events[lastAssinged] = new Appointment(createEpoch, startEpoch, endEpoch, std::move(name), uuid);
			lastAssinged++;
		}
		/**
		 * add apointemnt to the calender based on unix tm struct
		 * @param createEpoch create tm structure
		 * @param startEpoch start tm structure
		 * @param endEpoch end tm structure
		 * @param name the name of the appointment
		 * @param uuid the globaly unique ID needed by ICAL
		 */
		void add(tm *createEpoch, tm *startEpoch, tm *endEpoch, std::string name, std::string uuid) {
			_events[lastAssinged] = new Appointment(createEpoch, startEpoch, endEpoch, std::move(name), uuid);
			lastAssinged++;
		}

		/**
		 * output stream operator, outputs in ICAL format
		 * @param os
		 * @param calender
		 * @return
		 */
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
