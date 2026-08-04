/******************************************************************************
 * Project Falcon
 * File: health.h
 * Description: Public interface for system-health monitoring.
 ******************************************************************************/

#ifndef HEALTH_H
#define HEALTH_H

#include "falcon_types.h"

void health_init(void);
void health_update(const sensor_data_t *sensor_data);
const health_status_t *health_get_status(void);

#endif
