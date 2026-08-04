/******************************************************************************
 * Project Falcon
 * File: logger.h
 * Description: Public interface for the in-memory telemetry logger.
 ******************************************************************************/

#ifndef LOGGER_H
#define LOGGER_H

#include <stdbool.h>
#include <stdint.h>

#include "falcon_types.h"

void logger_init(void);
void logger_write(const telemetry_frame_t *frame);
uint32_t logger_get_count(void);
bool logger_get_frame(uint32_t index, telemetry_frame_t *frame);

#endif
