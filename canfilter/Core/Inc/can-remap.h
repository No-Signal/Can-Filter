#if !defined(can_remap_h)
#define can_remap_h

#include "main.h"
#include "can.h"

#ifdef BATTERY_REMAP
void can_handler_to_battery(uint8_t can_bus, CAN_FRAME *frame);
void can_handler_to_battery_emulator(uint8_t can_bus, CAN_FRAME *frame);
#endif

#endif
