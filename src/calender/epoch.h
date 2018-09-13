//
// Created by Garrett Battaglia on 9/13/18.
//

#ifndef SMARTCAL_CALDAV_EPOCH_H
#define SMARTCAL_CALDAV_EPOCH_H

#include <cstdint>
#include <time.h>

struct tm* SecondsSinceEpochToDateTime(struct tm* pTm, uint_fast64_t SecondsSinceEpoch);


#endif //SMARTCAL_CALDAV_EPOCH_H
