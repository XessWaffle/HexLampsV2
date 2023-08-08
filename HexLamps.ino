#include "Lamp.h"

#include "Fire.h"
#include "Color.h"

#include "PreferenceManager.h"
#include "TimeManager.h"
#include "Preferences.h"
#include "Utilities.h"

extern lamp_state_s glbl_lamp_state;

void lamp_task_cb(lamp_task_e task_result)
{

}


void setup() {
  // put your setup code here, to run once

#if defined(DEBUG) || defined(DEBUG_PREFERENCES) 
  Serial.begin(115200);
#endif

  initialize();
  connect_wifi();
  while(sync_time() == TASK_FAIL) delay(100);

  lamp_task_packet_s *packet = (lamp_task_packet_s*) malloc(sizeof(lamp_task_packet_s));
  packet->cb = lamp_task_cb;
  packet->req_task = LAMP_ON_REQ;
  packet->next_req = NULL;
  packet->req_params.animation_cb = fire;
  packet->req_params.params.brightness = 240;
  packet->req_params.params.fps = 60;

  add_preference(night, packet);

  packet = (lamp_task_packet_s*) malloc(sizeof(lamp_task_packet_s));
  packet->cb = lamp_task_cb;
  packet->req_task = LAMP_SWITCH_ANIMATION_REQ;
  packet->next_req = NULL;
  packet->req_params.animation_cb = color;
  packet->req_params.params.brightness = 10;
  packet->req_params.params.fps = 30;
  packet->req_params.params.color = CRGB(200, 20, 0);

  add_preference(sleep, packet);

  packet = (lamp_task_packet_s*) malloc(sizeof(lamp_task_packet_s));
  packet->cb = lamp_task_cb;
  packet->req_task = LAMP_OFF_REQ;
  packet->next_req = NULL;
  packet->req_params.animation_cb = fire;
  packet->req_params.params.brightness = 0;
  packet->req_params.params.fps = 60;
  packet->req_params.params.color = CRGB(255, 255, 255);

  add_preference(day, packet);

}

void loop() {
  // put your main code here, to run repeatedly:

  iterate();
  iterate_time();
  iterate_preferences();

}
