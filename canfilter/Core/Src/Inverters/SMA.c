#include "Inverters.h"
#ifdef SMA

#define INVERTER_SELECTED 1

uint32_t allowed_frames[] = {
	       0x358, // allow max/min voltage current
	       0x360,
	       0x3E0,
	       0x3D8, // allow SOC/SOH
	       0x420,
	       0x458,
	       0x518,
	       0x4D8, // allow voltage current temp status
	       0x158, // warning and errors
	       0x558,
	       0x598,
	       0x5D8,
	       0x618,
	       0x560, // pairing message
	       0x561, // pairing message
	       0x562, // pairing message
	       0x563, // pairing message
	       0x564, // pairing message
	       0x565, // pairing message
	       0x566, // pairing message
	       0x567, // pairing message
	       0x5E0, // pairing message
	       0x5E1, // pairing message
	       0x5E2, // pairing message
	       0x5E3, // pairing message
	       0x5E4, // pairing message
	       0x5E5, // pairing message
	       0x5E6, // pairing message
	       0x5E7  // pairing message
	   };
size_t num_allowed_frames = sizeof(allowed_frames) / sizeof(allowed_frames[0]);
#endif
