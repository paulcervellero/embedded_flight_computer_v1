/******************************************************************************
 * Project Falcon
 * File: scheduler.c
 * Description: Runs Falcon modules in a deterministic order using virtual time.
 ******************************************************************************/

#include "scheduler.h"

#include "flight_mode.h"
#include "health.h"
#include "logger.h"
#include "navigation.h"
#include "sensors.h"
#include "telemetry.h"

static uint32_t scheduler_time_ms;

void scheduler_init(void)
{
    scheduler_time_ms = 0U;
}

void scheduler_run(void)
{
    const sensor_data_t *sensor_data;
    const navigation_data_t *navigation_data;
    const health_status_t *health_status;
    const telemetry_frame_t *telemetry_frame;

    sensors_update(scheduler_time_ms);
    sensor_data = sensors_get_data();

    navigation_update(sensor_data, scheduler_time_ms);
    navigation_data = navigation_get_data();

    health_update(sensor_data);
    health_status = health_get_status();

    flight_mode_update(scheduler_time_ms,
                       sensor_data,
                       navigation_data,
                       health_status);

    telemetry_update(scheduler_time_ms,
                     flight_mode_get_state(),
                     sensor_data,
                     navigation_data);

    telemetry_frame = telemetry_get_latest_frame();
    logger_write(telemetry_frame);

    scheduler_time_ms += FALCON_SCHEDULER_PERIOD_MS;
}

uint32_t scheduler_get_time_ms(void)
{
    return scheduler_time_ms;
}
