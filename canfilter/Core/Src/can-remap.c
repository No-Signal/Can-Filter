#include "can.h"

#include "can-remap.h"
#include "Batteries.h"

#ifdef BATTERY_REMAP
void can_handler_to_battery_emulator(uint8_t can_bus, CAN_FRAME *frame)
{
   uint8_t allowed = 0;

   for (size_t i = 0; i < num_allowed_to_battery_emulator; i++)
   {
      if (frame->ID == allowed_to_battery_emulator[i])
      {
         allowed = 1;
         break;
      }
   }

   if (allowed)
   {
      frame->ID = frame->ID + BATTERY_REMAP_ADJUST;
      PushCan(can_bus, CAN_TX, frame);
   }
}

void can_handler_to_battery(uint8_t can_bus, CAN_FRAME *frame)
{
   uint8_t allowed = 0;

   for (size_t i = 0; i < num_allowed_to_battery; i++)
   {
      if (frame->ID == allowed_to_battery[i])
      {
        allowed = 1;
        break;
      }
   }

   if (allowed)
   {
        frame->ID = frame->ID - BATTERY_REMAP_ADJUST;
        PushCan(can_bus, CAN_TX, frame);
   }
}
#endif
