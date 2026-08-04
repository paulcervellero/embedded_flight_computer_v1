/******************************************************************************
 * Project Falcon
 * File: scheduler.h
 * Description: Public interface for the virtual-time cooperative scheduler.
 ******************************************************************************/

#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <stdint.h>

void scheduler_init(void);
void scheduler_run(void);
uint32_t scheduler_get_time_ms(void);

#endif
