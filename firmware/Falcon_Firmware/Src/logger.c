/******************************************************************************
 * Project Falcon
 * File: logger.c
 * Description: Stores telemetry frames in a fixed-size RAM ring buffer.
 ******************************************************************************/

#include "logger.h"

static telemetry_frame_t log_buffer[FALCON_LOG_CAPACITY];
static uint32_t write_index;
static uint32_t frame_count;

void logger_init(void)
{
    write_index = 0U;
    frame_count = 0U;
}

void logger_write(const telemetry_frame_t *frame)
{
    uint32_t byte_index;

    if (frame == 0)
    {
        return;
    }

    for (byte_index = 0U; byte_index < FALCON_TELEMETRY_PACKET_SIZE; byte_index++)
    {
        log_buffer[write_index].bytes[byte_index] = frame->bytes[byte_index];
    }

    write_index = (write_index + 1U) % FALCON_LOG_CAPACITY;

    if (frame_count < FALCON_LOG_CAPACITY)
    {
        frame_count++;
    }
}

uint32_t logger_get_count(void)
{
    return frame_count;
}

bool logger_get_frame(uint32_t index, telemetry_frame_t *frame)
{
    uint32_t byte_index;
    uint32_t start_index;
    uint32_t buffer_index;

    if ((frame == 0) || (index >= frame_count))
    {
        return false;
    }

    start_index = (write_index + FALCON_LOG_CAPACITY - frame_count) %
                  FALCON_LOG_CAPACITY;
    buffer_index = (start_index + index) % FALCON_LOG_CAPACITY;

    for (byte_index = 0U; byte_index < FALCON_TELEMETRY_PACKET_SIZE; byte_index++)
    {
        frame->bytes[byte_index] = log_buffer[buffer_index].bytes[byte_index];
    }

    return true;
}
