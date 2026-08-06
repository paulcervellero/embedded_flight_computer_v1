# Falcon Flight Computer

A modular embedded flight computer software platform designed for STM32-based systems.

Falcon is an embedded systems engineering project focused on developing reliable, maintainable firmware for telemetry, flight-state management, and onboard data processing. The project follows a software-first development methodology, allowing firmware architecture and verification to mature before hardware integration.

---

## Contents

- Overview
- Project Goals
- Project Status
- System Architecture
- Current Capabilities
- Repository Structure
- Development Workflow
- Building the Firmware
- Telemetry Decoder
- Documentation
- Technologies
- Roadmap
- License

---

## Project Goals

Falcon was created to explore professional embedded software development using STM32 microcontrollers while following industry-style engineering practices.

Primary objectives include:

- Modular firmware architecture
- Reliable telemetry generation
- Flight-state management
- Hardware abstraction
- Software verification
- Engineering documentation
- Version-controlled development workflow

---

## Project Status

- [x] Repository organization
- [x] System architecture
- [x] Engineering documentation
- [x] Firmware software baseline
- [ ] STM32 hardware integration
- [ ] Sensor integration
- [ ] SD card logging
- [ ] Flight testing

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
│ ├── Flight Logic                        │
│ ├── Navigation                          │
│ ├── Telemetry                           │
│ ├── Health Monitoring                   │
│ └── Data Logging                        │
├─────────────────────────────────────────┤
│ Hardware Abstraction Layer              │
├─────────────────────────────────────────┤
│ STM32 Drivers                           │
└─────────────────────────────────────────┘
```

---

## Current Capabilities

The current firmware software baseline includes:

- Application layer
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

```
embedded_flight_computer_v1/
│
├── docs/
├── firmware/
├── reports/
├── sample_data/
├── tests/
├── tools/
├── README.md
├── LICENSE
├── CHANGELOG.md
└── requirements.txt
```

---

## Firmware Location

The STM32 firmware project is located in:

```
firmware/Falcon_Firmware/
```

---

## Building the Firmware

### Requirements

- STM32CubeIDE
- STM32 HAL
- ARM GCC Toolchain

Open the project located in:

```
firmware/Falcon_Firmware/
```

Then build the firmware using STM32CubeIDE.

---

## Telemetry Decoder

A Python telemetry decoder is included for validating generated telemetry packets.

Location:

```
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

The decoder validates:

- Synchronization word
- Packet integrity
- CRC
- Packet contents

before displaying the telemetry in a human-readable format.

---

## Documentation

Engineering documentation is organized into:

```
docs/
├── 01_Project
├── 02_System
├── 03_Firmware
├── 04_Hardware
├── 05_Testing
├── 06_Diagrams
└── 07_Reviews
```

---

## Development Workflow

Falcon follows a software-first engineering process.

1. Define the system architecture.
2. Implement modular firmware.
3. Verify behavior using desktop tools and self-tests.
4. Integrate STM32 hardware.
5. Validate the complete embedded system.
6. Expand capabilities through iterative development.

This workflow allows firmware development to mature independently of hardware availability while maintaining a clean, scalable architecture.

---

## Technologies

### Embedded Software

- Embedded C
- STM32 HAL
- UART
- SPI
- I²C

### Desktop Tools

- Python
- Git
- GitHub
- Visual Studio Code

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

Licensed under the Apache License 2.0.

See the LICENSE file for additional information.

---

## Author

**Paul Cervellero**

Computer Engineering Student  
University of South Carolina
