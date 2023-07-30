#ifndef LAMPS_H
#define LAMPS_H

#include "Constants.h"
#include "Animation.h"

typedef enum LampTask
{
    LAMP_ON_REQ, LAMP_OFF_REQ, LAMP_SWITCH_ANIMATION_REQ, 
    LAMP_ON_DONE, LAMP_OFF_DONE, LAMP_SWITCH_ANIMATION_DONE,
    LAMP_ON_FAIL, LAMP_OFF_FAIL, LAMP_SWITCH_ANIMATION_FAIL,
    LAMP_TASK_FAIL
} lamp_task_e;

typedef struct LampParameters
{
    void (*animation_cb)(struct CRGB*, animation_state_e, animation_parameters_s);
    animation_parameters_s params;
} lamp_parameters_s;

typedef struct LampTaskPacket
{
    lamp_task_e req_task;
    lamp_parameters_s req_params;

    void (*cb)(lamp_task_e);

    struct LampTaskPacket *next_req;
} lamp_task_packet_s;

typedef struct LampState
{
    bool on, initialized;
    
    lamp_task_packet_s *task_queue_process, *task_queue_end;
    lamp_parameters_s current_prm_state;
    
    struct CRGB leds[NUM_LEDS];

} lamp_state_s;


void initialize();

void iterate();

lamp_task_e lamp_on();
lamp_task_e lamp_off();
lamp_task_e lamp_switch_animation();

void add_task_packet(lamp_task_packet_s *packet);



#endif