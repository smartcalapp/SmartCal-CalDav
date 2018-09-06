cmake_minimum_required(VERSION 3.12)
project(SmartCal_CalDav)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(SmartCal_CalDav src/main.cpp src/net/socket.cpp src/webDav/webDavCon.cpp src/webDav/webDavCon.h
        src/calender/Calender.cpp src/calender/Calender.h src/calender/Appointment.cpp src/calender/Appointment.h
        src/calender/Date.cpp src/calender/Date.h src/calender/Time.cpp src/calender/Time.h src/config/config.cpp src/config/config.h src/calender/iCalDefs.h)

#include libqp
find_path(POSTGRESS_SQL_INCLUDE_DIR libpq-fe.h)
include_directories(${POSTGRESS_SQL_INCLUDE_DIR})
target_link_libraries(SmartCal_CalDav -lpq)