/******************************************************************************
 * Project Falcon
 * File: app.c
 * Description: Initializes Falcon modules and runs one application cycle.
 ******************************************************************************/

#include "app.h"

#include "flight_mode.h"
#include "health.h"
#include "logger.h"
#include "navigation.h"
#include "scheduler.h"
#include "sensors.h"
#include "telemetry.h"

void app_init(void)
{
    sensors_init();
    navigation_init();
    health_init();
    flight_mode_init();
    telemetry_init();
    logger_init();
    scheduler_init();
}

void app_run(void)
{
    scheduler_run();
}
