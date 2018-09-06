//
// Created by Garrett Battaglia on 8/31/18.
//

#ifndef SMARTCAL_CALDAV_APPOINTMENT_H
#define SMARTCAL_CALDAV_APPOINTMENT_H


#include <string>
#include "Date.h"
#include "Time.h"

class Appointment {
		private:
				Date _startDate;
				Time _startTime;
				Date _endDate;
				Time _endTime;
				std::string _name;
		public:
				Appointment(){

				}
				Appointment(uint_fast64_t startEpoch, uint_fast64_t endEpoch, std::string name){
					_startDate = epochTime2Date(startEpoch);
					_endDate = epochTime2Date(endEpoch);
					_startTime = epochTime2Time(startEpoch);
					_endTime = epochTime2Time(endEpoch);
					_name = name;
				}

};


#endif //SMARTCAL_CALDAV_APPOINTMENT_H
