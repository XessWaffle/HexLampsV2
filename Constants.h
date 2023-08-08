#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <stdint.h>

typedef enum {TASK_SUCCESS, TASK_FAIL, TASK_IN_PROGRESS} generic_task_e;

const uint8_t DATA_PIN = 5;
const uint8_t NUM_LEDS = 150;

const uint8_t NIGHT_LAMP_MATRIX_WIDTH = 6;
const uint8_t NIGHT_LAMP_MATRIX_HEIGHT = 25;

const char WIFI_SSID[] = "SDSquad";
const char WIFI_PSK[] = "lpvertcomm";

const uint8_t NIGHT_HOUR = 21;
const uint8_t SLEEP_HOUR = 0;
const uint8_t MORNING_HOUR = 7;

const uint32_t SYNC_TIME_DELAY = 1000 * 60 * 30;
const uint32_t UPDATE_TIME_DELAY = 1000;

#endif