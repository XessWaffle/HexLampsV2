#include "Fire.h"

void fire(struct CRGB leds[], animation_state_e state, animation_parameters_s init_params)
{
    // Array of temperature readings at each simulation cell
    static uint8_t heat[NUM_LEDS];
    static fire_animation_parameters_s params;

    if(state == ANIMATION_ENTER)
    {
        params.init_params = init_params;
        params.gReverseDirection = false;
        random16_add_entropy(random());
        Serial.println("Playing Animation Fire");
        
    }
    else if (state == ANIMATION_CONTINUE)
    {
       // Step 1.  Cool down every cell a little
        for( int i = 0; i < NUM_LEDS; i++)
            heat[i] = qsub8( heat[i],  random8(0, ((COOLING * 10) / NUM_LEDS) + 2));
    
        // Step 2.  Heat from each cell drifts 'up' and diffuses a little
        for( int k= NUM_LEDS - 1; k >= 2; k--)
            heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2] ) / 3;
        
        // Step 3.  Randomly ignite new 'sparks' of heat near the bottom
        if( random8() < SPARKING ) {
            int y = random8(7);
            heat[y] = qadd8( heat[y], random8(160,255) );
        }

        // Step 4.  Map from heat cells to LED colors
        for( int j = 0; j < NUM_LEDS; j++)
        {
            // Scale the heat value from 0-255 down to 0-240
            // for best results with color palettes.
            uint8_t colorindex = scale8( heat[j], 240);
            struct CRGB color = ColorFromPalette( HeatColors_p, colorindex);
            int pixelnumber;
            if( params.gReverseDirection ) {
                pixelnumber = (NUM_LEDS-1) - j;
            } else {
                pixelnumber = j;
            }
            leds[pixelnumber] = color;
        }
    }
    else if (state == ANIMATION_EXIT)
    {
        memset(&params, 0, sizeof(fire_animation_parameters_s));
        random16_set_seed(millis());
    }   
}