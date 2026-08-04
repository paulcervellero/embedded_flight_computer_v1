/******************************************************************************
 * Project Falcon
 * File: flight_mode.c
 * Description: Implements the Falcon flight-state transition logic.
 ******************************************************************************/

#include "flight_mode.h"

static flight_state_t current_state;

void flight_mode_init(void)
{
    current_state = FLIGHT_STATE_INITIALIZATION;
}

void flight_mode_update(uint32_t timestamp_ms,
                        const sensor_data_t *sensor_data,
                        const navigation_data_t *navigation_data,
                        const health_status_t *health_status)
{
    if ((sensor_data == 0) || (navigation_data == 0) || (health_status == 0))
    {
        current_state = FLIGHT_STATE_IDLE;
        return;
    }

    switch (current_state)
    {
        case FLIGHT_STATE_INITIALIZATION:
            if ((timestamp_ms >= 1000U) && health_status->healthy)
            {
                current_state = FLIGHT_STATE_READY;
            }
            break;

        case FLIGHT_STATE_READY:
            if (sensor_data->altitude_m > 5.0f)
            {
                current_state = FLIGHT_STATE_LAUNCH;
            }
            break;

        case FLIGHT_STATE_LAUNCH:
            if (navigation_data->vertical_velocity_mps > 5.0f)
            {
                current_state = FLIGHT_STATE_ASCENT;
            }
            break;

        case FLIGHT_STATE_ASCENT:
            if ((sensor_data->altitude_m > 100.0f) &&
                (navigation_data->vertical_velocity_mps <= 0.5f))
            {
                current_state = FLIGHT_STATE_APOGEE;
            }
            break;

        case FLIGHT_STATE_APOGEE:
            if (navigation_data->vertical_velocity_mps < -0.5f)
            {
                current_state = FLIGHT_STATE_DESCENT;
            }
            break;

        case FLIGHT_STATE_DESCENT:
            if ((sensor_data->altitude_m < 2.0f) &&
                (navigation_data->vertical_velocity_mps <= 0.5f))
            {
                current_state = FLIGHT_STATE_LANDING;
            }
            break;

        case FLIGHT_STATE_IDLE:
        case FLIGHT_STATE_LANDING:
        default:
            break;
    }
}

flight_state_t flight_mode_get_state(void)
{
    return current_state;
}
