# Project Falcon

## Embedded Flight Computer and Telemetry System

Project Falcon is a software-first embedded systems engineering project focused on a modular STM32-based flight telemetry system.

The goal is to develop a clean firmware architecture now, then integrate the real hardware later without rewriting the whole system.

---

# Project Status

- Foundation — Complete
- Engineering Design — Complete
- Critical Design Review — Complete
- Software Baseline — Complete
- Hardware Integration — Planned

---

# Current Software Baseline

Falcon currently includes:

- application layer
- cooperative scheduler
- simulated sensors
- navigation calculations
- flight-state machine
- health monitoring
- telemetry packet generation
- RAM logger
- startup self-tests

The current firmware builds cleanly in STM32CubeIDE.

---

# Firmware Location

The STM32 firmware project lives here:

`firmware/Falcon_Firmware/`

---

# Telemetry Decoder

A Python telemetry decoder is included at:

`tools/telemetry_decoder.py`

Run it like this:

`python3 tools/telemetry_decoder.py <hex_packet>`

Example:

`python3 tools/telemetry_decoder.py AA550000E80300000000000000000000000000000000000000000000BEEF`

This tool validates the sync word and CRC, then prints the packet contents in a readable format.

---

# Documentation

Engineering documentation is organized into:

- `docs/01_Project`
- `docs/02_System`
- `docs/03_Firmware`
- `docs/04_Hardware`
- `docs/05_Testing`
- `docs/06_Diagrams`
- `docs/07_Reviews`

---

# Development Approach

Falcon follows a software-first workflow:

1. Define the architecture.
2. Build the software baseline.
3. Verify behavior with self-tests and desktop tools.
4. Integrate hardware later.
5. Replace simulation with real drivers without redesigning the whole project.

That approach keeps the firmware clean and makes the hardware phase much easier when the board and sensors arrive.

---

# Repository Structure

`embedded_flight_computer_v1/`

- `docs/`
- `firmware/`
- `reports/`
- `sample_data/`
- `tests/`
- `tools/`
- `README.md`
- `LICENSE`
- `CHANGELOG.md`
- `requirements.txt`

---

# Software Technologies

## Embedded Software

- Embedded C
- STM32 HAL
- UART
- SPI
- I²C

## Desktop Software

- Python
- Git
- GitHub
- Visual Studio Code

---

# Build Status

The current Falcon software baseline builds successfully in STM32CubeIDE.

---

# Planned Version 1.0 Capabilities

Project Falcon Version 1.0 will include:

- modular firmware architecture
- sensor acquisition
- flight state management
- telemetry generation
- CRC validation
- UART communication
- SD card logging
- Python telemetry analysis
- engineering verification reports

---

# Future Development

Future revisions may include:

- sensor fusion
- RTOS integration
- radio telemetry
- FPGA co-processing
- hardware-in-the-loop testing
- autonomous flight algorithms

---

# License

Licensed under the Apache License, Version 2.0.

See the LICENSE file for additional information.

---

# Author

Paul Cervellero