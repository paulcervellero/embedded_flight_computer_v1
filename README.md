# Falcon Flight Computer

A modular embedded flight computer software platform designed for STM32-based systems.

Falcon is an embedded systems engineering project focused on developing reliable, maintainable firmware for telemetry, flight-state management, and onboard data processing. The project follows a software-first development methodology, allowing firmware architecture and verification to mature before hardware integration.

---

## Overview

Project Falcon is designed to simulate a professional embedded software development environment. The project emphasizes modular firmware architecture, engineering documentation, version control, and verification before hardware integration.

The objective is to create firmware that can transition from simulated components to real STM32 hardware with minimal architectural changes.

---

## Project Goals

The primary goals of Falcon are to:

- Design modular embedded firmware
- Develop reliable telemetry generation
- Implement flight-state management
- Separate hardware abstraction from application logic
- Follow professional software engineering workflows
- Maintain comprehensive engineering documentation
- Prepare for seamless STM32 hardware integration

---

## Project Status

| Component | Status |
|-----------|:------:|
| Repository Organization | Complete |
| System Architecture | Complete |
| Engineering Documentation | Complete |
| Software Baseline | Complete |
| STM32 Hardware Integration | Planned |
| Sensor Integration | Planned |
| SD Card Logging | Planned |
| Flight Testing | Planned |

---

## System Architecture

```text
                    Ground Station
                           │
                      UART / USB
                           │
┌─────────────────────────────────────────┐
│          Falcon Flight Computer         │
├─────────────────────────────────────────┤
│ Application Layer                       │
│                                         │
│ • Flight Logic                          │
│ • Navigation                            │
│ • Telemetry                             │
│ • Health Monitoring                     │
│ • Data Logging                          │
├─────────────────────────────────────────┤
│ Hardware Abstraction Layer              │
├─────────────────────────────────────────┤
│ STM32 Drivers                           │
└─────────────────────────────────────────┘
```

---

## Current Capabilities

The current firmware software baseline includes:

- Modular application layer
- Cooperative scheduler
- Simulated sensors
- Navigation calculations
- Flight-state machine
- Health monitoring
- Telemetry packet generation
- RAM logger
- Startup self-tests

The firmware currently builds successfully in STM32CubeIDE.

---

## Repository Structure

```text
embedded_flight_computer_v1/
│
├── docs/
├── firmware/
├── reports/
├── sample_data/
├── tests/
├── tools/
│
├── CHANGELOG.md
├── LICENSE
├── README.md
└── requirements.txt
```

---

## Firmware

The STM32 firmware project is located in:

```text
firmware/Falcon_Firmware/
```

Open the project in **STM32CubeIDE** to build and run the firmware.

---

## Telemetry Decoder

A Python telemetry decoder is included for validating generated telemetry packets.

Location:

```text
tools/telemetry_decoder.py
```

Run:

```bash
python3 tools/telemetry_decoder.py <hex_packet>
```

Example:

```bash
python3 tools/telemetry_decoder.py AA550000E80300000000000000000000000000000000000000000000BEEF
```

The decoder verifies:

- Synchronization word
- CRC
- Packet integrity
- Telemetry contents

before displaying the decoded packet in a readable format.

---

## Documentation

Engineering documentation is organized into:

```text
docs/
├── 01_Project
├── 02_System
├── 03_Firmware
├── 04_Hardware
├── 05_Testing
├── 06_Diagrams
└── 07_Reviews
```

Documentation is maintained throughout development to capture architecture decisions, testing, design reviews, and verification activities.

---

## Development Workflow

Falcon follows a software-first engineering process.

1. Define system architecture.
2. Develop modular firmware.
3. Verify functionality using simulation and desktop tools.
4. Integrate STM32 hardware.
5. Validate complete system behavior.
6. Expand functionality through iterative development.

This workflow allows software architecture to mature independently of hardware availability while maintaining a clean and scalable design.

---

## Technologies

### Embedded Software

- Embedded C
- STM32 HAL
- UART
- SPI
- I²C

### Development Tools

- STM32CubeIDE
- Git
- GitHub
- Visual Studio Code

### Desktop Tools

- Python

---

## Roadmap

### Version 1.0

- Sensor acquisition
- Flight-state management
- Telemetry generation
- CRC validation
- UART communication
- SD card logging
- Python telemetry analysis
- Engineering verification reports

### Future Development

- RTOS integration
- Sensor fusion
- Hardware-in-the-loop testing
- Radio telemetry
- Autonomous flight algorithms
- FPGA co-processing

---

## License

This project is licensed under the Apache License 2.0.

See the `LICENSE` file for additional information.

---

## Author

**Paul Cervellero**

Computer Engineering Student  
University of South Carolina

Portfolio: https://paulcervellero.github.io

LinkedIn: https://www.linkedin.com/in/paul-cervellero-19b43a237/
