#include "Lamp.h"

#include "Fire.h"
#include "Color.h"

#include "PreferenceManager.h"
#include "Preferences.h"
#include "Utilities.h"

extern lamp_state_s glbl_lamp_state;

void lamp_task_cb(lamp_task_e task_result)
{

}

bool test_preference(){

  Serial.println("Test1");
  return random(10) > 5;
}

bool test_preference2(){
  Serial.println("Test2");
  return random(10) < 5;
}

void setup() {
  // put your setup code here, to run once
  Serial.begin(115200);
  initialize();
  
  connect_wifi();
  while(initialize_local_time(8 * 60 * 60, 0) == UTIL_FAIL) delay(100);

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
  packet->req_params.params.brightness = 20;
  packet->req_params.params.fps = 30;
  packet->req_params.params.color = CRGB(255, 0, 0);

  add_preference(sleep, packet);

  /*packet = (lamp_task_packet_s*) malloc(sizeof(lamp_task_packet_s));
  packet->cb = lamp_task_cb;
  packet->req_task = LAMP_ON_REQ;
  packet->next_req = NULL;
  packet->req_params.animation_cb = fire;
  packet->req_params.params.brightness = 240;
  packet->req_params.params.fps = 60;
  packet->req_params.params.color = CRGB(255, 255, 255);

  //add_preference(test_preference, packet);

  packet = (lamp_task_packet_s*) malloc(sizeof(lamp_task_packet_s));
  packet->cb = lamp_task_cb;
  packet->req_task = LAMP_OFF_REQ;
  packet->next_req = NULL;
  packet->req_params.animation_cb = NULL;
  packet->req_params.params.brightness = 50;
  packet->req_params.params.fps = 60;
  packet->req_params.params.color = CRGB(0,0,0);

  //add_preference(test_preference2, packet);*/


}

void loop() {
  // put your main code here, to run repeatedly:
  static uint32_t sys_time = 0;

  iterate();
  if(millis() - sys_time > TIME_UPDATE || sys_time == 0)
  {
    iterate_preferences();
    sys_time = millis();
  }
}