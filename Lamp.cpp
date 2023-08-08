#include "Lamp.h"
#include <Arduino.h>

lamp_state_s glbl_lamp_state;

void initialize()
{
    FastLED.addLeds<WS2812B, DATA_PIN, GRB>(glbl_lamp_state.leds, NUM_LEDS);
    glbl_lamp_state.initialized = true;
    glbl_lamp_state.on = true;
    glbl_lamp_state.task_queue_process = NULL;
}

void iterate()
{
    if(!glbl_lamp_state.initialized) return;

    if(glbl_lamp_state.task_queue_process != NULL)
    {
        switch(glbl_lamp_state.task_queue_process->req_task) 
        {
            case LAMP_ON_REQ:
#ifdef DEBUG
                Serial.println("LAMP_ON_REQ");
#endif
                glbl_lamp_state.task_queue_process->cb(lamp_on());
                break;
            case LAMP_OFF_REQ:
#ifdef DEBUG
                Serial.println("LAMP_OFF_REQ");
#endif
                glbl_lamp_state.task_queue_process->cb(lamp_off());
                break;
            case LAMP_SWITCH_ANIMATION_REQ:
#ifdef DEBUG
                Serial.println("LAMP_SWITCH_ANIMATION_REQ");
#endif
                if(glbl_lamp_state.current_prm_state.animation_cb != NULL)
                    glbl_lamp_state.current_prm_state.animation_cb(glbl_lamp_state.leds, ANIMATION_EXIT, glbl_lamp_state.current_prm_state.params);
                glbl_lamp_state.task_queue_process->cb(lamp_switch_animation());
                glbl_lamp_state.current_prm_state.animation_cb(glbl_lamp_state.leds, ANIMATION_ENTER, glbl_lamp_state.current_prm_state.params);
                break;
            default:
                glbl_lamp_state.task_queue_process->cb(LAMP_TASK_FAIL);
                break;
        }
        lamp_task_packet_s *processed = glbl_lamp_state.task_queue_process;
        glbl_lamp_state.task_queue_process = glbl_lamp_state.task_queue_process->next_req;
        free(processed);

        if(glbl_lamp_state.task_queue_process == NULL) glbl_lamp_state.task_queue_end = NULL;
    }

    if(glbl_lamp_state.current_prm_state.animation_cb != NULL && glbl_lamp_state.on)
    {
        glbl_lamp_state.current_prm_state.animation_cb(glbl_lamp_state.leds, ANIMATION_CONTINUE, glbl_lamp_state.current_prm_state.params);
        FastLED.show();
        FastLED.delay(1000 / glbl_lamp_state.current_prm_state.params.fps);
        FastLED.setBrightness(glbl_lamp_state.current_prm_state.params.brightness);
    }
}

lamp_task_e lamp_on()
{
    lamp_parameters_s *params = &(glbl_lamp_state.task_queue_process->req_params);
    if(params->animation_cb != NULL)
    {
        memcpy(&glbl_lamp_state.current_prm_state, params, sizeof(lamp_parameters_s));
        glbl_lamp_state.current_prm_state.animation_cb(glbl_lamp_state.leds, ANIMATION_ENTER, glbl_lamp_state.current_prm_state.params);
    }
    if(glbl_lamp_state.on) return LAMP_ON_FAIL;
    glbl_lamp_state.on = true;
    return LAMP_ON_DONE;
}

lamp_task_e lamp_off()
{
    lamp_parameters_s *params = &(glbl_lamp_state.task_queue_process->req_params);
    if(!glbl_lamp_state.on) return LAMP_OFF_FAIL;
    glbl_lamp_state.on = false;
    
    for(int i = 0; i < NUM_LEDS; i++){
      glbl_lamp_state.leds[i] = CRGB::Black;
    }

    FastLED.show();

    return LAMP_OFF_DONE;
}

lamp_task_e lamp_switch_animation()
{
    /* Verify integrity of animation parameters */
    lamp_parameters_s *params = &(glbl_lamp_state.task_queue_process->req_params);
    if(params->animation_cb == NULL) return LAMP_SWITCH_ANIMATION_FAIL;
    memcpy(&glbl_lamp_state.current_prm_state, params, sizeof(lamp_parameters_s));
    return LAMP_SWITCH_ANIMATION_DONE;
}

void add_task_packet(lamp_task_packet_s *packet)
{
#ifdef DEBUG
    Serial.println("Added packet");
#endif
    if(glbl_lamp_state.task_queue_process == NULL)
        glbl_lamp_state.task_queue_process = packet;
    else
        glbl_lamp_state.task_queue_end->next_req = packet;

    glbl_lamp_state.task_queue_end = packet;
}   