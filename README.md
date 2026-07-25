# Project Falcon

## Embedded Flight Computer and Telemetry System

Project Falcon is a professional embedded systems engineering project focused on the design, implementation, verification, and documentation of a modular flight telemetry system based on the STM32 platform.

The objective of the project is to demonstrate disciplined embedded systems engineering through structured system design, modular firmware development, hardware integration, verification, and technical documentation.

---

# Project Status

**Current Phase**

Phase 4 — Firmware and Hardware Implementation

**Project Status**

- Foundation — Complete
- Engineering Design — Complete
- Critical Design Review — Complete
- Firmware Development — Beginning

---

# Project Objectives

Project Falcon is designed to demonstrate the complete embedded systems development lifecycle.

Primary objectives include:

- Design a modular embedded flight computer
- Acquire and process sensor data
- Generate structured telemetry packets
- Log telemetry to removable storage
- Communicate with external software over UART
- Verify system performance through documented testing
- Produce professional engineering documentation

---

# System Overview

Project Falcon consists of the following major subsystems:

- STM32 Embedded Flight Computer
- Telemetry Packet Generator
- Sensor Interface Layer
- Data Logging System
- Python Telemetry Tools
- Verification and Test Framework

---

# Hardware Platform

The current hardware platform consists of:

- STM32 NUCLEO-F401RE
- ICM-20948 Inertial Measurement Unit
- BMP280 Barometric Pressure Sensor
- u-blox GPS Receiver
- SPI microSD Storage Module

---

# Software Technologies

Embedded Software

- Embedded C
- STM32 HAL
- UART
- SPI
- I²C

Desktop Software

- Python
- Git
- GitHub
- Visual Studio Code

---

# Repository Structure

```text
embedded_flight_computer_v1/

docs/
firmware/
reports/
sample_data/
tests/
tools/

README.md
LICENSE
CHANGELOG.md
requirements.txt
```

---

# Engineering Documentation

Engineering documentation is organized into the following categories.

```text
01_Project
02_System
03_Firmware
04_Hardware
05_Testing
06_Diagrams
07_Reviews
```

Current documentation includes:

- Project Execution Plan
- Requirements
- System Architecture
- Telemetry Packet Specification
- Hardware Plan
- Interface Control Document
- Firmware Architecture
- Coding Standard
- Risk Register
- Requirements Verification Matrix
- Test Plan
- Bill of Materials

---

# Engineering Principles

Project Falcon is developed according to the following engineering principles.

- Design before implementation.
- One responsibility per module.
- Every requirement shall be verifiable.
- Official documentation takes precedence over assumptions.
- Version control all engineering artifacts.
- Build incrementally.
- Understand every line of code.
- Design for failure and recovery.
- Every engineering artifact must provide measurable value.
- Build for long-term maintainability.

---

# Development Lifecycle

| Stage | Status |
|--------|--------|
| Foundation | Complete |
| Engineering Design | Complete |
| Critical Design Review | Complete |
| Firmware Development | In Progress |
| Hardware Integration | Planned |
| System Verification | Planned |
| Version 1.0 Release | Planned |

---

# Planned Version 1.0 Capabilities

Project Falcon Version 1.0 will include:

- Modular firmware architecture
- Sensor acquisition
- Flight state management
- Telemetry generation
- CRC validation
- UART communication
- SD card logging
- Python telemetry analysis
- Engineering verification reports

---

# Future Development

Future revisions may include:

- Sensor fusion
- RTOS integration
- Radio telemetry
- FPGA co-processing
- Hardware-in-the-loop testing
- Autonomous flight algorithms

---

# License

Licensed under the Apache License, Version 2.0.

See the LICENSE file for additional information.

---

# Author

Paul Cervellero