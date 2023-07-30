#include "Utilities.h"

#include "time.h"

#include <ESP8266WiFi.h>
#include <Arduino.h>
#include <TZ.h>

utilities_result_e connect_wifi()
{
    WiFi.begin(WIFI_SSID, WIFI_PSK);

    if(WiFi.status() == WL_CONNECTED)
        return UTIL_SUCCESS;
    else
        return UTIL_IN_PROGRESS;
}

utilities_result_e disconnect_wifi()
{
    WiFi.disconnect(true);
    WiFi.mode(WIFI_OFF);
    return UTIL_SUCCESS;
}

utilities_result_e initialize_local_time(uint16_t gmt_offset, uint16_t daylight_offset)
{
    if(WiFi.status() != WL_CONNECTED)
        return UTIL_FAIL;
    Serial.println("Initializing Time");
    configTime(TZ_America_Tijuana, "pool.ntp.org");

    return UTIL_SUCCESS;
}