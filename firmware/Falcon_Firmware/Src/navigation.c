/******************************************************************************
 * Project Falcon
 * File: navigation.c
 * Description: Calculates vertical velocity from simulated altitude data.
 ******************************************************************************/

#include "navigation.h"

static navigation_data_t navigation_data;
static float previous_altitude_m;
static uint32_t previous_timestamp_ms;
static bool has_previous_sample;

void navigation_init(void)
{
    navigation_data.vertical_velocity_mps = 0.0f;
    previous_altitude_m = 0.0f;
    previous_timestamp_ms = 0U;
    has_previous_sample = false;
}

void navigation_update(const sensor_data_t *sensor_data, uint32_t timestamp_ms)
{
    if ((sensor_data == 0) || !has_previous_sample)
    {
        if (sensor_data != 0)
        {
            previous_altitude_m = sensor_data->altitude_m;
            previous_timestamp_ms = timestamp_ms;
            has_previous_sample = true;
        }

        navigation_data.vertical_velocity_mps = 0.0f;
        return;
    }

    const uint32_t delta_time_ms = timestamp_ms - previous_timestamp_ms;

    if (delta_time_ms > 0U)
    {
        const float delta_time_s = (float)delta_time_ms / 1000.0f;
        navigation_data.vertical_velocity_mps =
            (sensor_data->altitude_m - previous_altitude_m) / delta_time_s;
    }

    previous_altitude_m = sensor_data->altitude_m;
    previous_timestamp_ms = timestamp_ms;
}

const navigation_data_t *navigation_get_data(void)
{
    return &navigation_data;
}
