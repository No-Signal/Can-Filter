#include "can.h"

#include "can-filter.h"
#include "Inverters.h"

void can_filter_allow_list(uint8_t can_bus, CAN_FRAME *frame)
{
   uint8_t allowed = 0;

   for (size_t i = 0; i < num_allowed_frames; i++)
   {
      if (frame->ID == allowed_frames[i])
      {
         allowed = 1;
         break;
      }
   }

   if (allowed)
   {
      PushCan(can_bus, CAN_TX, frame);
   }
}

void can_filter_extended_ids_only(uint8_t can_bus, CAN_FRAME *frame)
{
	if(frame->ide){
		PushCan(can_bus, CAN_TX, frame);
	}
}
