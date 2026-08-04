/******************************************************************************
 * Project Falcon
 * File: config.h
 * Description: Central software configuration constants.
 ******************************************************************************/

#ifndef CONFIG_H
#define CONFIG_H

#include <stdint.h>

#define FALCON_SCHEDULER_PERIOD_MS        (100U)
#define FALCON_TELEMETRY_SYNC_WORD        (0xAA55U)
#define FALCON_TELEMETRY_PACKET_SIZE      (30U)
#define FALCON_LOG_CAPACITY               (64U)
#define FALCON_LOW_BATTERY_VOLTAGE_V      (7.0f)
#define FALCON_MAX_ALTITUDE_M             (10000.0f)
#define FALCON_MIN_PRESSURE_PA            (30000.0f)
#define FALCON_MAX_PRESSURE_PA            (110000.0f)

#endif
