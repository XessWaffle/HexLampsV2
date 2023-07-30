#ifndef COLOR_H
#define COLOR_H


#include "Constants.h"
#include "Animation.h"

typedef struct ColorAnimationParameters
{
    animation_parameters_s init_params;
} color_animation_parameters_s;

void color(struct CRGB leds[], animation_state_e state, animation_parameters_s init_params);

#endif