/******************************************************************************
 * Project Falcon
 * File: flight_mode.h
 * Description: Public interface for the Falcon flight-state machine.
 ******************************************************************************/

#ifndef FLIGHT_MODE_H
#define FLIGHT_MODE_H

#include <stdint.h>

#include "falcon_types.h"

void flight_mode_init(void);
void flight_mode_update(uint32_t timestamp_ms,
                        const sensor_data_t *sensor_data,
                        const navigation_data_t *navigation_data,
                        const health_status_t *health_status);
flight_state_t flight_mode_get_state(void);

#endif
