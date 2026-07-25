# System Architecture

## Project Name

Project Falcon – Embedded Flight Computer & Telemetry Logger

---

# System Overview
Project Falcon follows a modular architecture where each subsystem has one clearly defined responsibility.

Separating the project into independent modules allows the firmware, Python tools, testing framework, and hardware interfaces to evolve independently while sharing a common telemetry protocol.

This modular design simplifies debugging, testing, future hardware expansion, and long-term maintenance.

The complete system is shown below.
               +----------------------+
               |  STM32 Flight        |
               |  Computer            |
               +----------+-----------+
                          |
                          |
             UART Telemetry Packets
                          |
                          |
        +-----------------+-----------------+
        |                                   |
        |                                   |
 Python Serial Logger                 SD Card Logger
        |                                   |
        +-----------------+-----------------+
                          |
                    CSV Flight Log
                          |
         +----------------+----------------+
         |                                 |
         |                                 |
  Telemetry Validator              Plot Generator
         |                                 |
         |                                 |
  Validation Report              Engineering Graphs

---

# Software Modules

## Telemetry Generator

Responsibility:

Generate flight-style telemetry.

Current Version:

Python

Future Version:

STM32 firmware

---

## Packet Builder

Responsibility:

Build telemetry packets.

Each packet contains:

- Sequence number
- Timestamp
- Flight state
- Sensor values
- CRC

---

## CRC Generator

Responsibility:

Protect every telemetry packet.

Purpose:

Detect corrupted packets.

---

## Serial Logger

Responsibility:

Receive UART packets from the STM32.

Convert them into CSV logs.

---

## Validator

Responsibility:

Verify:

- CRC
- Timing
- Missing packets
- Invalid values

---

## Plot Generator

Responsibility:

Convert telemetry logs into engineering plots.

Examples:

- Altitude
- Battery
- Pressure
- Acceleration

---

# Hardware Modules

## STM32 Flight Computer

Responsibilities:

- Read sensors
- Build telemetry
- Calculate CRC
- Send UART packets
- Log to SD card

---

## IMU

Provides:

- Acceleration
- Gyroscope
- Orientation

Interface:

I2C

---

## Barometer

Provides:

- Pressure
- Estimated altitude

Interface:

I2C

---

## GPS

Provides:

- Position
- GPS Fix

Interface:

UART

---

## SD Card

Stores telemetry logs.

Interface:

SPI

---

# Communication Interfaces

| Interface | Purpose |
|-----------|---------|
| UART | Telemetry + GPS |
| I2C | IMU + Barometer |
| SPI | SD Card |

---

# Repository Structure

```text
embedded_flight_computer_v1
│
├── docs
├── reports
├── sample_data
├── tests
├── tools
├── firmware
├── README.md
├── requirements.txt
└── .gitignore
```

# Design Philosophy

Every module should have one job.

Firmware should generate telemetry.

Python should analyze telemetry.

Documentation should explain telemetry.

Testing should validate telemetry.

No module should perform multiple unrelated responsibilities.

This architecture allows new sensors and new software tools to be added without changing the overall design.

---

# Engineering Goal

This project is intended to demonstrate the complete embedded systems development lifecycle, including requirements definition, architecture design, firmware development, hardware integration, verification, and engineering documentation.

Every project milestone must compile, execute, pass its tests, and be documented before additional functionality is introduced.