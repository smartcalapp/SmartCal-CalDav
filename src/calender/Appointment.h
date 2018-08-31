//
// Created by Garrett Battaglia on 8/31/18.
//

#ifndef SMARTCAL_CALDAV_APPOINTMENT_H
#define SMARTCAL_CALDAV_APPOINTMENT_H


#include "Date.h"
#include "Time.h"

class Appointment
{
	private:
		Date _startDate;
		Time _startTime;
		Date _endDate;
		Time _endTime;
};


#endif //SMARTCAL_CALDAV_APPOINTMENT_H
