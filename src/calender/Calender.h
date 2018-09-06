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
				Appointment** _events;
				int lastAssinged = 0;
				int numApts;
		public:
				Calender(){

				}
				Calender(int numberOfApts){
					_events = new Appointment*[numberOfApts];
					numApts= numberOfApts;
				}
				void add(uint_fast64_t startEpoch, uint_fast64_t endEpoch, std::string name){
					_events[lastAssinged] = new Appointment(startEpoch, endEpoch, name);
					lastAssinged++;
				}

				friend std::ostream &operator<<(std::ostream &os, const Calender &calender) {
					os << "BEGIN:VCALENDAR" << ICAL_LINE_SEP << "VERSION:2.0" << ICAL_LINE_SEP << "PRODID:" << PROD_ID << " " << VERSION_ID << ICAL_LINE_SEP;
					for (int i = 0; i < calender.numApts; i++){
						os <<  *(calender._events[i]) ;
					}
					os << "END:VCALENDAR";
					return os;
				}
};


#endif //SMARTCAL_CALDAV_CALENDER_H
