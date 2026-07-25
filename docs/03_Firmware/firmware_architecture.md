# Firmware Architecture

---

# Document Information

| Item | Value |
|------|-------|
| Project | Project Falcon |
| Document | Firmware Architecture |
| Document ID | PF-CDR-003 |
| Revision | 1.0 |
| Status | Draft |
| Author | Paul Cervellero |
| Last Updated | July 2026 |

---

# Purpose

This document defines the software architecture used throughout Project Falcon.

The objective is to ensure that firmware remains modular, maintainable, testable, and scalable as the project grows.

Each subsystem has one clearly defined responsibility.

---

# Architectural Philosophy

Project Falcon follows a layered embedded software architecture.

Each software layer interacts only with adjacent layers.

This minimizes coupling and simplifies debugging, testing, and future expansion.

---

# System Architecture

```
                    +---------------------------+
                    |      Application          |
                    +---------------------------+
                                |
                    +---------------------------+
                    |    Flight State Machine   |
                    +---------------------------+
                    |                           |
          +-------------------+     +-------------------+
          |    Telemetry      |     |     Logging       |
          +-------------------+     +-------------------+
                    |                           |
          +-------------------+     +-------------------+
          | Communication     |     | Sensor Drivers    |
          +-------------------+     +-------------------+
                    |                           |
              +--------------------------------------+
              |           STM32 HAL Drivers          |
              +--------------------------------------+
                             |
              +--------------------------------------+
              |        STM32F401RE Hardware          |
              +--------------------------------------+
```

---

# Layer Responsibilities

## Application Layer

Responsibilities

- System startup
- Main loop
- High-level control
- Module coordination

The Application Layer contains no hardware-specific code.

---

## Flight State Machine

Responsibilities

- Idle
- Initialization
- Ready
- Launch
- Ascent
- Apogee
- Descent
- Landing

This module determines overall system behavior.

---

## Telemetry Module

Responsibilities

- Build telemetry packets
- Add timestamps
- Calculate CRC
- Send telemetry

The telemetry module never reads sensors directly.

---

## Logging Module

Responsibilities

- SD card logging
- File management
- Logging errors

---

## Communication Module

Responsibilities

- UART
- SPI
- I²C

This module moves data.

It never interprets sensor values.

---

## Sensor Drivers

Responsibilities

- IMU
- BMP280
- GPS

Drivers return measurements.

Drivers never make decisions.

---

## HAL Layer

Responsibilities

Provide hardware abstraction between STM32 peripherals and Project Falcon software.

---

# Directory Layout

```
firmware/

├── Application/
│
├── StateMachine/
│
├── Telemetry/
│
├── Sensors/
│
├── Communication/
│
├── Logging/
│
├── Core/
│
├── Drivers/
│
└── Tests/
```

---

# Engineering Rules

## Rule 1

One module performs one responsibility.

---

## Rule 2

Modules communicate only through defined interfaces.

---

## Rule 3

No circular dependencies.

---

## Rule 4

Hardware-specific code remains isolated inside drivers.

---

## Rule 5

Every module must be independently testable whenever practical.

---

# Future Expansion

The architecture supports future integration of:

- Radio telemetry
- CAN bus
- Additional sensors
- RTOS
- Autonomous navigation
- FPGA co-processing

without restructuring the existing firmware.

---

# Architecture Success Criteria

The firmware architecture is considered successful when:

- Every source file belongs to exactly one subsystem.
- Hardware abstraction is maintained.
- Module interfaces remain stable.
- New functionality can be added with minimal impact to existing code.