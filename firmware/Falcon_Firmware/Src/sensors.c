/******************************************************************************
 * Project Falcon
 * File: sensors.c
 * Description: Generates deterministic simulated sensor data.
 ******************************************************************************/

#include "sensors.h"

static sensor_data_t sensor_data;

static float calculate_simulated_altitude(uint32_t timestamp_ms)
{
    const float time_s = (float)timestamp_ms / 1000.0f;

    if (time_s < 5.0f)
    {
        return 0.0f;
    }

    if (time_s < 25.0f)
    {
        return (time_s - 5.0f) * 25.0f;
    }

    if (time_s < 28.0f)
    {
        return 500.0f;
    }

    if (time_s < 58.0f)
    {
        return 500.0f - ((time_s - 28.0f) * (500.0f / 30.0f));
    }

    return 0.0f;
}

void sensors_init(void)
{
    sensor_data.acceleration_x_g = 0.0f;
    sensor_data.acceleration_y_g = 0.0f;
    sensor_data.acceleration_z_g = 1.0f;
    sensor_data.gyro_x_dps = 0.0f;
    sensor_data.gyro_y_dps = 0.0f;
    sensor_data.gyro_z_dps = 0.0f;
    sensor_data.pressure_pa = 101325.0f;
    sensor_data.temperature_c = 22.0f;
    sensor_data.altitude_m = 0.0f;
    sensor_data.battery_voltage_v = 8.4f;
    sensor_data.gps_fix = false;
    sensor_data.latitude_deg = 34.000000f;
    sensor_data.longitude_deg = -81.000000f;
}

void sensors_update(uint32_t timestamp_ms)
{
    const float time_s = (float)timestamp_ms / 1000.0f;
    const float altitude_m = calculate_simulated_altitude(timestamp_ms);

    sensor_data.altitude_m = altitude_m;
    sensor_data.pressure_pa = 101325.0f - (altitude_m * 12.0f);
    sensor_data.temperature_c = 22.0f - (altitude_m * 0.0065f);
    sensor_data.battery_voltage_v = 8.4f - (time_s * 0.002f);
    sensor_data.gps_fix = (timestamp_ms >= 3000U);
    sensor_data.latitude_deg = 34.000000f + (time_s * 0.000015f);
    sensor_data.longitude_deg = -81.000000f - (time_s * 0.000012f);

    if ((timestamp_ms >= 5000U) && (timestamp_ms < 25000U))
    {
        sensor_data.acceleration_z_g = 1.25f;
    }
    else if ((timestamp_ms >= 28000U) && (timestamp_ms < 58000U))
    {
        sensor_data.acceleration_z_g = 0.85f;
    }
    else
    {
        sensor_data.acceleration_z_g = 1.0f;
    }
}

const sensor_data_t *sensors_get_data(void)
{
    return &sensor_data;
}
