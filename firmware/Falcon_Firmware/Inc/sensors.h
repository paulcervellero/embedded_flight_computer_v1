/******************************************************************************
 * Project Falcon
 * File: sensors.h
 * Description: Public interface for simulated and future real sensors.
 ******************************************************************************/

#ifndef SENSORS_H
#define SENSORS_H

#include <stdint.h>

#include "falcon_types.h"

void sensors_init(void);
void sensors_update(uint32_t timestamp_ms);
const sensor_data_t *sensors_get_data(void);

#endif
