# Coding Standard

---

# Document Information

| Item | Value |
|------|-------|
| Project | Project Falcon |
| Document | Coding Standard |
| Document ID | PF-CDR-004 |
| Revision | 1.0 |
| Status | Draft |
| Author | Paul Cervellero |
| Last Updated | July 2026 |

---

# Purpose

This document defines the coding standards used throughout Project Falcon.

The objective is to produce firmware that is readable, maintainable, consistent, and easy to review.

---

# General Principles

Project Falcon firmware shall prioritize:

- Readability over cleverness
- Simplicity over complexity
- Reliability over optimization
- Consistency over personal preference

---

# File Organization

Each module consists of:

example_module.c

example_module.h

No source file should contain unrelated functionality.

---

# Naming Conventions

## Variables

Use:

snake_case

Example

```c
flight_state
battery_voltage
packet_counter
```

---

## Functions

Use descriptive snake_case names.

Example

```c
initialize_uart()
read_gps_data()
build_telemetry_packet()
calculate_crc16()
```

---

## Constants

Use uppercase with underscores.

Example

```c
MAX_PACKET_SIZE
UART_TIMEOUT_MS
DEFAULT_BAUD_RATE
```

---

## Enumerations

Example

```c
typedef enum
{
    STATE_IDLE,
    STATE_READY,
    STATE_ASCENT,
    STATE_DESCENT
} flight_state_t;
```

---

## Structures

Example

```c
typedef struct
{
    float altitude;
    float velocity;
    float pressure;
} telemetry_packet_t;
```

---

# Comments

Every source file begins with:

```c
/******************************************************************************
 *
 * File:
 *
 * Description:
 *
 * Author:
 *
 ******************************************************************************/
```

Functions should describe:

- Purpose
- Inputs
- Outputs

Comments explain why—not what.

---

# Error Handling

Every function should return meaningful status information whenever practical.

Example:

```c
typedef enum
{
    STATUS_OK,
    STATUS_ERROR,
    STATUS_TIMEOUT
} status_t;
```

---

# Header Files

Header files contain:

- Public function declarations
- Public data structures
- Enumerations
- Constants

Never place executable code inside header files.

---

# Global Variables

Avoid global variables whenever practical.

If a global variable is required:

- Keep it private using static
- Document its purpose

---

# Magic Numbers

Magic numbers are prohibited.

Use named constants.

Example

```c
#define UART_BAUD_RATE 115200
```

instead of

```c
uart_init(115200);
```

---

# Formatting

- Four spaces for indentation
- Opening braces on a new line
- One declaration per line
- Maximum practical function length: approximately 50 lines
- Maximum practical line length: 100 characters

---

# Engineering Philosophy

Every line of code should satisfy one question:

"Will another engineer understand this six months from now?"

If the answer is no, rewrite it.