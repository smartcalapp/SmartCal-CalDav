//
// Created by Garrett Battaglia on 8/31/18.
//

#ifndef SMARTCAL_CALDAV_SOCKET_H
#define SMARTCAL_CALDAV_SOCKET_H

#include <cstdint>

/**
 * open master socket based on config
 */
void openMasterSocket();

/**
 * open master socket
 * @param port port to open socket on
 */
void openMasterSocket(uint_fast16_t port);

#endif //SMARTCAL_CALDAV_SOCKET_H
