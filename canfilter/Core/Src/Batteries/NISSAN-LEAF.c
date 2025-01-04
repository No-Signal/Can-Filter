#include "Batteries.h"
#ifdef NISSAN_LEAF

#define BATTERY_SELECTED 1

uint32_t allowed_to_battery[] = {
    0x1F2 + BATTERY_REMAP_ADJUST,
    0x50B + BATTERY_REMAP_ADJUST,
    0x50C + BATTERY_REMAP_ADJUST,
    0x1D4 + BATTERY_REMAP_ADJUST,
    0x79B + BATTERY_REMAP_ADJUST
};

uint32_t allowed_to_battery_emulator[] = {
    0x1DB,
    0x1DC,
    0x55B,
    0x5BC,
    0x5C0,
    0x59E,
    0x1ED,
    0x1C2,
    0x7BB
};

size_t num_allowed_to_battery = sizeof(allowed_to_battery) / sizeof(allowed_to_battery[0]);
size_t num_allowed_to_battery_emulator = sizeof(allowed_to_battery_emulator) / sizeof(allowed_to_battery_emulator[0]);
#endif
