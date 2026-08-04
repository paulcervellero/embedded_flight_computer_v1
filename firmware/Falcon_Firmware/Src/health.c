/******************************************************************************
 * Project Falcon
 * File: health.c
 * Description: Monitors simulated values and records active fault bits.
 ******************************************************************************/

#include "health.h"

static health_status_t health_status;

void health_init(void)
{
    health_status.fault_mask = HEALTH_FAULT_NONE;
    health_status.healthy = true;
}

void health_update(const sensor_data_t *sensor_data)
{
    uint32_t fault_mask = HEALTH_FAULT_NONE;

    if (sensor_data == 0)
    {
        health_status.fault_mask = HEALTH_FAULT_PRESSURE_RANGE;
        health_status.healthy = false;
        return;
    }

    if (sensor_data->battery_voltage_v < FALCON_LOW_BATTERY_VOLTAGE_V)
    {
        fault_mask |= HEALTH_FAULT_LOW_BATTERY;
    }

    if ((sensor_data->pressure_pa < FALCON_MIN_PRESSURE_PA) ||
        (sensor_data->pressure_pa > FALCON_MAX_PRESSURE_PA))
    {
        fault_mask |= HEALTH_FAULT_PRESSURE_RANGE;
    }

    if ((sensor_data->altitude_m < 0.0f) ||
        (sensor_data->altitude_m > FALCON_MAX_ALTITUDE_M))
    {
        fault_mask |= HEALTH_FAULT_ALTITUDE_RANGE;
    }

    health_status.fault_mask = fault_mask;
    health_status.healthy = (fault_mask == HEALTH_FAULT_NONE);
}

const health_status_t *health_get_status(void)
{
    return &health_status;
}
