#include "TimeManager.h"

#include <TZ.h>
#include <Arduino.h>

#include "Utilities.h"
#include "time.h"

struct tm glbl_time_info;

void iterate_time()
{
    static time_t sync = 0;
    static uint32_t sync_delay = 0;
    static uint32_t update_delay = 0;

    if(millis() - sync_delay > SYNC_TIME_DELAY || sync_delay == 0)
    {
        sync_time();
        sync_delay = millis();
    }

    if(millis() - update_delay > UPDATE_TIME_DELAY || update_delay == 0)
    {
        time(&sync);

        struct tm *calculated_info = localtime(&sync); 
        memcpy(&glbl_time_info, calculated_info, sizeof(struct tm));
#ifdef DEBUG
        char buffer[80];
        strftime(buffer, 80, "%Y/%m/%d %r", calculated_info);
        Serial.println(buffer);
#endif
        update_delay = millis();

    }
}

generic_task_e sync_time()
{
    static bool tz_configured = false;
    if(is_wifi_connected()){
        if(!tz_configured)
        {
          configTime(TZ_America_Tijuana, "pool.ntp.org");
          tz_configured = true;
        }
        
        getLocalTime(&glbl_time_info);

        return TASK_SUCCESS;
    }
    return TASK_FAIL;
}

uint8_t get_hour()
{
    return glbl_time_info.tm_hour;
}
uint8_t get_minute()
{
    return glbl_time_info.tm_min;
}
uint8_t get_second()
{
    return glbl_time_info.tm_sec;
}
