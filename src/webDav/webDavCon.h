//
// Created by Garrett Battaglia on 8/31/18.
//

#ifndef SMARTCAL_CALDAV_WEBDAV_H
#define SMARTCAL_CALDAV_WEBDAV_H

//TODO abs path
#include "../calender/Calender.h"

class WebDavCon {
	private:
		int _file;
		void* sqlCon;
		Calender cal;
		WebDavCon(){

		}
	public:
		WebDavCon(int file){
			_file = file;
			//open SQL con
			//build calender
		}

};


#endif //SMARTCAL_CALDAV_WEBDAV_H
