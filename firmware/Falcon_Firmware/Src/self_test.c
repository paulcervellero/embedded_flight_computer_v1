/******************************************************************************
 * Project Falcon
 * File: self_test.c
 * Description: Software-only startup checks for the Falcon core.
 ******************************************************************************/

#include "self_test.h"

#include "flight_mode.h"
#include "health.h"
#include "logger.h"
#include "telemetry.h"

static bool self_test_crc16(void)
{
    static const uint8_t test_data[] = {
        '1', '2', '3', '4', '5', '6', '7', '8', '9'
    };

    return (telemetry_calculate_crc16(test_data, 9U) == 0x29B1U);
}

static bool self_test_health_init(void)
{
    const health_status_t *status;

    health_init();
    status = health_get_status();

    return (status != 0) &&
           status->healthy &&
           (status->fault_mask == HEALTH_FAULT_NONE);
}

static bool self_test_flight_mode_init(void)
{
    flight_mode_init();
    return (flight_mode_get_state() == FLIGHT_STATE_INITIALIZATION);
}

static bool self_test_logger_wraparound(void)
{
    telemetry_frame_t input_frame = {0};
    telemetry_frame_t output_frame = {0};
    uint32_t index;

    logger_init();

    for (index = 0U; index < (FALCON_LOG_CAPACITY + 2U); index++)
    {
        input_frame.bytes[0] = (uint8_t)index;
        input_frame.bytes[1] = (uint8_t)(0xA5U ^ (uint8_t)index);
        logger_write(&input_frame);
    }

    if (logger_get_count() != FALCON_LOG_CAPACITY)
    {
        return false;
    }

    if (!logger_get_frame(0U, &output_frame))
    {
        return false;
    }

    return (output_frame.bytes[0] == 2U);
}

bool self_test_run(void)
{
    bool ok = true;

    ok = ok && self_test_crc16();
    ok = ok && self_test_health_init();
    ok = ok && self_test_flight_mode_init();
    ok = ok && self_test_logger_wraparound();

    return ok;
}
