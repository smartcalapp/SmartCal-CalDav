//
// Created by Garrett Battaglia on 9/13/18.
//

#include "epoch.h"
#include <string.h>
#include <iostream>

/**
 * covert epoch time to tm structure
 * @param pTm tm struct to fill in
 * @param SecondsSinceEpoch epoch time stamp
 * @return pTm filled in based on timestamp
 */
//WARN: TAKEN FROM http://qr.ae/TUNleL
struct tm* SecondsSinceEpochToDateTime(tm* pTm, uint_fast64_t SecondsSinceEpoch)
{
	uint_fast64_t sec;
	uint_fast32_t quadricentennials, centennials, quadrennials, annuals/*1-ennial?*/;
	uint_fast32_t year, leap;
	uint_fast32_t yday, hour, min;
	uint_fast32_t month, mday, wday;
	static const uint_fast32_t daysSinceJan1st[2][13]=
					{
									{0,31,59,90,120,151,181,212,243,273,304,334,365}, // 365 days, non-leap
									{0,31,60,91,121,152,182,213,244,274,305,335,366}  // 366 days, leap
					};
/*
  400 years:

  1st hundred, starting immediately after a leap year that's a multiple of 400:
  n n n l  \
  n n n l   } 24 times
  ...      /
  n n n l /
  n n n n

  2nd hundred:
  n n n l  \
  n n n l   } 24 times
  ...      /
  n n n l /
  n n n n

  3rd hundred:
  n n n l  \
  n n n l   } 24 times
  ...      /
  n n n l /
  n n n n

  4th hundred:
  n n n l  \
  n n n l   } 24 times
  ...      /
  n n n l /
  n n n L <- 97'th leap year every 400 years
*/

	// Re-bias from 1970 to 1601:
	// 1970 - 1601 = 369 = 3*100 + 17*4 + 1 years (incl. 89 leap days) =
	// (3*100*(365+24/100) + 17*4*(365+1/4) + 1*365)*24*3600 seconds
	sec = SecondsSinceEpoch + 11644473600LL;

	wday = (uint_fast32_t)((sec / 86400 + 1) % 7); // day of week

	// Remove multiples of 400 years (incl. 97 leap days)
	quadricentennials = (uint_fast32_t)(sec / 12622780800ULL); // 400*365.2425*24*3600
	sec %= 12622780800ULL;

	// Remove multiples of 100 years (incl. 24 leap days), can't be more than 3
	// (because multiples of 4*100=400 years (incl. leap days) have been removed)
	centennials = (uint_fast32_t)(sec / 3155673600ULL); // 100*(365+24/100)*24*3600
	if (centennials > 3)
	{
		centennials = 3;
	}
	sec -= centennials * 3155673600ULL;

	// Remove multiples of 4 years (incl. 1 leap day), can't be more than 24
	// (because multiples of 25*4=100 years (incl. leap days) have been removed)
	quadrennials = (uint_fast32_t)(sec / 126230400); // 4*(365+1/4)*24*3600
	if (quadrennials > 24)
	{
		quadrennials = 24;
	}
	sec -= quadrennials * 126230400ULL;

	// Remove multiples of years (incl. 0 leap days), can't be more than 3
	// (because multiples of 4 years (incl. leap days) have been removed)
	annuals = (uint_fast32_t)(sec / 31536000); // 365*24*3600
	if (annuals > 3)
	{
		annuals = 3;
	}
	sec -= annuals * 31536000ULL;

	// Calculate the year and find out if it's leap
	year = 1601 + quadricentennials * 400 + centennials * 100 + quadrennials * 4 + annuals;
	leap = !(year % 4) && (year % 100 || !(year % 400));

	// Calculate the day of the year and the time
	yday = sec / 86400;
	sec %= 86400;
	hour = sec / 3600;
	sec %= 3600;
	min = sec / 60;
	sec %= 60;

	// Calculate the month
	for (mday = month = 1; month < 13; month++)
	{
		if (yday < daysSinceJan1st[leap][month])
		{
			mday += yday - daysSinceJan1st[leap][month - 1];
			break;
		}
	}

	// Fill in C's "struct tm"
	memset(pTm, 0, sizeof(*pTm));
	pTm->tm_sec = sec;          // [0,59]
	pTm->tm_min = min;          // [0,59]
	pTm->tm_hour = hour;        // [0,23]
	pTm->tm_mday = mday;        // [1,31]  (day of month)
	pTm->tm_mon = month - 1;    // [0,11]  (month)
	pTm->tm_year = year - 1900; // 70+     (year since 1900)
	pTm->tm_wday = wday;        // [0,6]   (day since Sunday AKA day of week)
	pTm->tm_yday = yday;        // [0,365] (day since January 1st AKA day of year)
	pTm->tm_isdst = -1;         // daylight saving time flag

	return pTm;
}