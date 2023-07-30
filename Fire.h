#ifndef FIRE_H
#define FIRE_H

#include "Constants.h"
#include "Animation.h"

#define COOLING  55
// SPARKING: What chance (out of 255) is there that a new spark will be lit?
// Higher chance = more roaring fire.  Lower chance = more flickery fire.
// Default 120, suggested range 50-200.
#define SPARKING 120

typedef struct FireAnimationParameters
{
    animation_parameters_s init_params;
    bool gReverseDirection;
} fire_animation_parameters_s;

void fire(struct CRGB leds[], animation_state_e state, animation_parameters_s init_params);

#endif