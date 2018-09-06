//
// Created by Garrett Battaglia on 8/31/18.
//

#ifndef SMARTCAL_CALDAV_CALENDER_H
#define SMARTCAL_CALDAV_CALENDER_H

#include <string>
#include "Appointment.h"

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
};


#endif //SMARTCAL_CALDAV_CALENDER_H
