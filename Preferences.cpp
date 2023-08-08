#include "Preferences.h"

#include <Arduino.h>

#include "TimeManager.h"
#include "Constants.h"

bool night()
{
    static bool trigger = false;
#ifdef DEBUG_PREFERENCES
    Serial.print("Night: ");
    Serial.println(get_hour());
#endif

    bool result = !trigger && (get_hour() >= NIGHT_HOUR);
    trigger = get_hour() >= NIGHT_HOUR;
    return result;
}

bool sleep()
{
    static bool trigger = false;
#ifdef DEBUG_PREFERENCES
    Serial.print("Sleep: ");
    Serial.println(get_hour());
#endif

    bool result = !trigger && (get_hour() >= SLEEP_HOUR && get_hour() <= MORNING_HOUR);
    trigger = get_hour() >= SLEEP_HOUR && get_hour() <= MORNING_HOUR;
    return result;
}

bool day()
{
    static bool trigger = false;
#ifdef DEBUG_PREFERENCES
    Serial.print("Day: ");
    Serial.println(get_hour());
#endif

    bool result = !trigger && (get_hour() >= MORNING_HOUR && get_hour() < NIGHT_HOUR);
    trigger = get_hour() >= MORNING_HOUR && get_hour() < NIGHT_HOUR;
    return result;
}