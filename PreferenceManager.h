#ifndef PREFERENCE_MANAGER_H
#define PREFERENCE_MANAGER_H

#include "Lamp.h"

typedef struct Preference
{
    bool (*condition)();
    lamp_task_packet_s *packet;
    struct Preference *next, *prev;
} preference_s;


void iterate_preferences();
void add_preference(bool (*condition)(), lamp_task_packet_s *packet);

#endif