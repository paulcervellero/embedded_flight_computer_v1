/******************************************************************************
 * Project Falcon
 * File: telemetry.c
 * Description: Serializes Falcon telemetry into a fixed 30-byte packet.
 ******************************************************************************/

#include "telemetry.h"

#include <string.h>

static telemetry_frame_t latest_frame;
static uint8_t packet_id;

static void write_u16_le(uint8_t *destination, uint16_t value)
{
    destination[0] = (uint8_t)(value & 0xFFU);
    destination[1] = (uint8_t)((value >> 8) & 0xFFU);
}

static void write_u32_le(uint8_t *destination, uint32_t value)
{
    destination[0] = (uint8_t)(value & 0xFFU);
    destination[1] = (uint8_t)((value >> 8) & 0xFFU);
    destination[2] = (uint8_t)((value >> 16) & 0xFFU);
    destination[3] = (uint8_t)((value >> 24) & 0xFFU);
}

static void write_float_le(uint8_t *destination, float value)
{
    uint32_t raw_value;

    memcpy(&raw_value, &value, sizeof(raw_value));
    write_u32_le(destination, raw_value);
}

void telemetry_init(void)
{
    uint32_t index;

    for (index = 0U; index < FALCON_TELEMETRY_PACKET_SIZE; index++)
    {
        latest_frame.bytes[index] = 0U;
    }

    packet_id = 0U;
}

void telemetry_update(uint32_t timestamp_ms,
                      flight_state_t flight_state,
                      const sensor_data_t *sensor_data,
                      const navigation_data_t *navigation_data)
{
    float altitude_m = 0.0f;
    float velocity_mps = 0.0f;
    float temperature_c = 0.0f;
    float pressure_pa = 0.0f;
    float battery_voltage_v = 0.0f;
    uint16_t crc;

    if (sensor_data != 0)
    {
        altitude_m = sensor_data->altitude_m;
        temperature_c = sensor_data->temperature_c;
        pressure_pa = sensor_data->pressure_pa;
        battery_voltage_v = sensor_data->battery_voltage_v;
    }

    if (navigation_data != 0)
    {
        velocity_mps = navigation_data->vertical_velocity_mps;
    }

    write_u16_le(&latest_frame.bytes[0], FALCON_TELEMETRY_SYNC_WORD);
    latest_frame.bytes[2] = packet_id;
    latest_frame.bytes[3] = (uint8_t)flight_state;
    write_u32_le(&latest_frame.bytes[4], timestamp_ms);
    write_float_le(&latest_frame.bytes[8], altitude_m);
    write_float_le(&latest_frame.bytes[12], velocity_mps);
    write_float_le(&latest_frame.bytes[16], temperature_c);
    write_float_le(&latest_frame.bytes[20], pressure_pa);
    write_float_le(&latest_frame.bytes[24], battery_voltage_v);

    crc = telemetry_calculate_crc16(latest_frame.bytes, 28U);
    write_u16_le(&latest_frame.bytes[28], crc);

    packet_id++;
}

const telemetry_frame_t *telemetry_get_latest_frame(void)
{
    return &latest_frame;
}

uint16_t telemetry_calculate_crc16(const uint8_t *data, uint32_t length)
{
    uint16_t crc = 0xFFFFU;
    uint32_t index;

    if (data == 0)
    {
        return 0U;
    }

    for (index = 0U; index < length; index++)
    {
        uint8_t bit;

        crc ^= (uint16_t)data[index] << 8;

        for (bit = 0U; bit < 8U; bit++)
        {
            if ((crc & 0x8000U) != 0U)
            {
                crc = (uint16_t)((crc << 1) ^ 0x1021U);
            }
            else
            {
                crc = (uint16_t)(crc << 1);
            }
        }
    }

    return crc;
}
