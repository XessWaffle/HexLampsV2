#ifndef WIFI_MANAGER_H
#define WIFI_MANAGER_H

#include "Constants.h"

typedef enum {UTIL_SUCCESS, UTIL_FAIL, UTIL_IN_PROGRESS} utilities_result_e;

utilities_result_e connect_wifi();
utilities_result_e disconnect_wifi();

utilities_result_e initialize_local_time(uint16_t gmt_offset, uint16_t daylight_offset);


#endif