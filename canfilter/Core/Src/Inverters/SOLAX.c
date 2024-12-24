#include "Inverters.h"
#ifdef SOLAX

#define INVERTER_SELECTED 1

uint32_t allowed_frames[] = {
		0x1801,
		0x1872,// BMS_Limits
		0x1873,// BMS_PackData
		0x1874,// BMS_CellData
		0x1875,// BMS_Status
		0x1876,// BMS_PackTemps
		0x1877,
		0x1878,// BMS_PackStats
		0x1879,
		0x187E, // Needed for Ultra
		0x187D, // Needed for Ultra
		0x187C, // Needed for Ultra
		0x187B, // Needed for Ultra
		0x187A, // Needed for Ultra
		0x1881,// E.g.: 0 6 S B M S F A
		0x1882,// E.g.: 0 2 3 A B 0 5 2
		0x100A001
	   };
size_t num_allowed_frames = sizeof(allowed_frames) / sizeof(allowed_frames[0]);
#endif
