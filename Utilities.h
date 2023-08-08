#ifndef WIFI_MANAGER_H
#define WIFI_MANAGER_H

#include "Constants.h"

generic_task_e connect_wifi();
generic_task_e disconnect_wifi();
bool is_wifi_connected();

#endif