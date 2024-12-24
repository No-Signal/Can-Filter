# CAN-Filter

This software is designed to work with the [Battery-Emulator](https://github.com/dalathegreat/Battery-Emulator) project to allow using Inverters that need to see only certain CAN messages on the same CAN-bus as a battery by filtering out all other messages.

## How to use?

Read the [CAN-filter-hardware](https://github.com/dalathegreat/Battery-Emulator/wiki/CAN-filter-hardware) wiki entry for how to use this software.

CAN1 must be connected to the Battery-Emulator
CAN2 must be connected to the Inverter

## Making changes to the software

To specify which inverter you are using uncomment the relevant #define in the USER_SETTINGS.h file.

**Example Configuration**
```
/* Select Mode */
#define INVERTER_ALLOWLIST
//#define BATTERY_REMAP

/* Select Inverter used */
//#define SMA
#define SOLAX
```

The software is developed using STM32CubeIDE.

## Multiple batteries on a single CAN-bus (untested)

> [!CAUTION]
> **This approach is untested and may cause collisions with other CAN frames which could cause a dangerous situation, use this at your own risk.**
> This **untested** configuration is to allow multiple batteries to be connected to a single CAN-bus by modifying the CAN frame IDs as an alternate approach to having multiple CAN channels. 

The connected battery will receive messages on the expected IDs while the Battery-Emulator will receive the IDs adjusted by BATTERY_REMAP_ADJUST (default 10), this requires code changes to Battery-Emulator.

**Example Configuration**
```
/* Select Mode */
//#define INVERTER_ALLOWLIST
#define BATTERY_REMAP

/* Select Inverter used */
//#define SMA
//#define SOLAX

/* Select Battery used */
#define BATTERY_REMAP_ADJUST 10
#define NISSAN_LEAF
```

## Based On

This project is based on the [Nissan-LEAF-Battery-Upgrade](https://github.com/dalathegreat/Nissan-LEAF-Battery-Upgrade) project.

Special thanks to [malcolmputer](https://github.com/malcolmputer) for the initial idea of CAN filtering and the POC from which this is based.