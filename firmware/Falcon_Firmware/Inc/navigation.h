/******************************************************************************
 * Project Falcon
 * File: navigation.h
 * Description: Public interface for navigation calculations.
 ******************************************************************************/

#ifndef NAVIGATION_H
#define NAVIGATION_H

#include <stdint.h>

#include "falcon_types.h"

void navigation_init(void);
void navigation_update(const sensor_data_t *sensor_data, uint32_t timestamp_ms);
const navigation_data_t *navigation_get_data(void);

#endif
