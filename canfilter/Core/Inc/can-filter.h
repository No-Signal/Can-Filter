#if !defined(can_filter_h)
#define can_filter_h

#include "main.h"
#include "can.h"

void can_filter_allow_list(uint8_t can_bus, CAN_FRAME *frame);

void can_filter_extended_ids_only(uint8_t can_bus, CAN_FRAME *frame);

#endif
