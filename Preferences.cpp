#include "Preferences.h"

#include "time.h"

#include <Arduino.h>

bool night()
{
    static bool trigger = false;

    struct tm timeinfo;
    getLocalTime(&timeinfo);
    
    Serial.print("Night: ");
    Serial.println(timeinfo.tm_hour);

    bool result = !trigger && (timeinfo.tm_hour >= NIGHT_HOUR || timeinfo.tm_hour <= SLEEP_HOUR);
    trigger = timeinfo.tm_hour >= NIGHT_HOUR || timeinfo.tm_hour <= SLEEP_HOUR;
    return result;
}

bool sleep()
{
    static bool trigger = false;

    struct tm timeinfo;
    getLocalTime(&timeinfo);
    
    Serial.print("Sleep: ");
    Serial.println(timeinfo.tm_hour);

    bool result = !trigger && (timeinfo.tm_hour >= SLEEP_HOUR && timeinfo.tm_hour <= MORNING_HOUR);
    trigger = timeinfo.tm_hour >= SLEEP_HOUR && timeinfo.tm_hour <= MORNING_HOUR;
    return result;
}