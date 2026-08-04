/******************************************************************************
 * Project Falcon
 * File: telemetry.h
 * Description: Public interface for telemetry packet generation.
 ******************************************************************************/

#ifndef TELEMETRY_H
#define TELEMETRY_H

#include <stdint.h>

#include "falcon_types.h"

void telemetry_init(void);
void telemetry_update(uint32_t timestamp_ms,
                      flight_state_t flight_state,
                      const sensor_data_t *sensor_data,
                      const navigation_data_t *navigation_data);
const telemetry_frame_t *telemetry_get_latest_frame(void);
uint16_t telemetry_calculate_crc16(const uint8_t *data, uint32_t length);

#endif
