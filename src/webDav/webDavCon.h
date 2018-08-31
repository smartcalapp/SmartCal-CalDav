//
// Created by Garrett Battaglia on 8/31/18.
//

#ifndef SMARTCAL_CALDAV_WEBDAV_H
#define SMARTCAL_CALDAV_WEBDAV_H


class WebDavCon {
	private:
		int _file;
		void sqlCon;
		WebDavCon(){

		}
	public:
		WebDavCon(int file){
			_file = file;
			//open SQL con
		}

};


#endif //SMARTCAL_CALDAV_WEBDAV_H
