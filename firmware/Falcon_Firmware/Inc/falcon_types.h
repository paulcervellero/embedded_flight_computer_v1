/******************************************************************************
 * Project Falcon
 * File: falcon_types.h
 * Description: Shared data types used by Falcon software modules.
 ******************************************************************************/

#ifndef FALCON_TYPES_H
#define FALCON_TYPES_H

#include <stdbool.h>
#include <stdint.h>

#include "config.h"

typedef enum
{
    FLIGHT_STATE_IDLE = 0,
    FLIGHT_STATE_INITIALIZATION = 1,
    FLIGHT_STATE_READY = 2,
    FLIGHT_STATE_LAUNCH = 3,
    FLIGHT_STATE_ASCENT = 4,
    FLIGHT_STATE_APOGEE = 5,
    FLIGHT_STATE_DESCENT = 6,
    FLIGHT_STATE_LANDING = 7
} flight_state_t;

typedef struct
{
    float acceleration_x_g;
    float acceleration_y_g;
    float acceleration_z_g;
    float gyro_x_dps;
    float gyro_y_dps;
    float gyro_z_dps;
    float pressure_pa;
    float temperature_c;
    float altitude_m;
    float battery_voltage_v;
    bool gps_fix;
    float latitude_deg;
    float longitude_deg;
} sensor_data_t;

typedef struct
{
    float vertical_velocity_mps;
} navigation_data_t;

typedef enum
{
    HEALTH_FAULT_NONE = 0U,
    HEALTH_FAULT_LOW_BATTERY = (1U << 0),
    HEALTH_FAULT_PRESSURE_RANGE = (1U << 1),
    HEALTH_FAULT_ALTITUDE_RANGE = (1U << 2)
} health_fault_t;

typedef struct
{
    uint32_t fault_mask;
    bool healthy;
} health_status_t;

typedef struct
{
    uint8_t bytes[FALCON_TELEMETRY_PACKET_SIZE];
} telemetry_frame_t;

#endif
