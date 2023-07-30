#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <stdint.h>

const uint8_t DATA_PIN = 5;
const uint8_t NUM_LEDS = 150;

const uint8_t NIGHT_LAMP_MATRIX_WIDTH = 6;
const uint8_t NIGHT_LAMP_MATRIX_HEIGHT = 25;

const char WIFI_SSID[] = "SDSquad";
const char WIFI_PSK[] = "lpvertcomm";

const uint8_t NIGHT_HOUR = 22;
const uint8_t SLEEP_HOUR = 1;
const uint8_t MORNING_HOUR = 9;

const uint32_t TIME_UPDATE = 1000 * 60 * 30;

#endif