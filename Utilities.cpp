#include "Utilities.h"

#include <ESP8266WiFi.h>

generic_task_e connect_wifi()
{
    WiFi.begin(WIFI_SSID, WIFI_PSK);

    if(WiFi.status() == WL_CONNECTED)
        return TASK_SUCCESS; 
    else
        return TASK_IN_PROGRESS;
}

generic_task_e disconnect_wifi()
{
    WiFi.disconnect(true);
    WiFi.mode(WIFI_OFF);
    return TASK_SUCCESS;
}

bool is_wifi_connected(){
    return WiFi.status() == WL_CONNECTED;
}

