#include "Color.h"

void color(struct CRGB leds[], animation_state_e state, animation_parameters_s init_params)
{
    static color_animation_parameters_s params;

    if(state == ANIMATION_ENTER)
    {
        params.init_params = init_params;
        Serial.println("Playing Animation Color");
        
    }
    else if (state == ANIMATION_CONTINUE)
    {
        for(int i = 0; i < NUM_LEDS; i++)
            leds[i] = params.init_params.color;
    }
    else if (state == ANIMATION_EXIT)
    {
        memset(&params, 0, sizeof(color_animation_parameters_s));
    }
    
}