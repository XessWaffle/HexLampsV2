#ifndef ANIMATION_H
#define ANIMATION_H

#include <FastLED.h>

typedef enum AnimationState
{
    ANIMATION_ENTER, ANIMATION_EXIT, ANIMATION_CONTINUE
} animation_state_e;

typedef struct AnimationParameters
{
    struct CRGB color;
    uint8_t fps;
    uint8_t brightness;
} animation_parameters_s;


#endif
