#include "PreferenceManager.h"
#include "Lamp.h"

preference_s *glbl_pref_buffer = NULL, *glbl_ring_ptr = NULL;

void iterate_preferences()
{
    if(glbl_ring_ptr != NULL )
    { 
        do{
          if(glbl_ring_ptr->condition())
          {
              lamp_task_packet_s *cpy = (lamp_task_packet_s*) malloc(sizeof(lamp_task_packet_s));
              memcpy(cpy, glbl_ring_ptr->packet, sizeof(lamp_task_packet_s));
              add_task_packet(cpy);
          }
          glbl_ring_ptr = glbl_ring_ptr->next;
        } while(glbl_ring_ptr != glbl_pref_buffer);
    }
}

void add_preference(bool (*condition)(), lamp_task_packet_s *packet)
{
    if(glbl_pref_buffer == NULL)
    {
        glbl_pref_buffer = (preference_s*) malloc(sizeof(preference_s));
        glbl_pref_buffer->packet = packet;
        glbl_pref_buffer->condition = condition;

        glbl_pref_buffer->next = glbl_pref_buffer;
        glbl_pref_buffer->prev = glbl_pref_buffer;
        glbl_ring_ptr = glbl_pref_buffer;
    } 
    else 
    {
        preference_s *new_preference = (preference_s*) malloc(sizeof(preference_s));
        new_preference->packet = packet;
        new_preference->condition = condition;

        preference_s *glbl_prev = glbl_pref_buffer->prev;
        glbl_prev->next = new_preference;
        new_preference->prev = glbl_prev;
        glbl_pref_buffer->prev = new_preference;
        new_preference->next = glbl_pref_buffer;
    }
}