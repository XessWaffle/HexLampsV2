#ifndef TIME_MANAGER_H
#define TIME_MANAGER_H

#include "Constants.h"

void iterate_time();

generic_task_e sync_time();

uint8_t get_hour();
uint8_t get_minute();
uint8_t get_second();


#endif