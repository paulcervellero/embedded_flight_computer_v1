# System Requirements

## Project Name

Embedded Flight Computer & Telemetry Logger

## Project Purpose

The goal of this project is to design, build, test, and document an embedded telemetry system similar to what could be used in a small rocket, UAV, test vehicle, or aerospace sensor platform.

The system will begin as a software telemetry simulator, then expand into STM32 firmware, real sensors, onboard logging, and hardware-in-the-loop testing.

## High-Level Requirements

### R1: Telemetry Generation

The system shall generate flight-style telemetry records at a target rate of 10 Hz.

Each telemetry record shall include:

- Sequence number
- Timestamp
- Flight state
- Acceleration data
- Gyroscope data
- Barometric pressure
- Estimated altitude
- Battery voltage
- GPS fix status
- Latitude
- Longitude
- CRC-16 checksum

### R2: Flight State Tracking

The system shall support the following flight states:

- PRELAUNCH
- ASCENT
- DESCENT
- LANDED

### R3: Packet Integrity

Each telemetry packet shall include a CRC-16 checksum so corrupted packets can be detected during validation.

### R4: Data Logging

The system shall save telemetry data in a CSV format that can be analyzed after a test run.

### R5: Validation Tools

The Python tools shall validate:

- CSV header correctness
- CRC checksum correctness
- Sequence number continuity
- Timing consistency
- Battery voltage range
- Altitude range
- GPS fix value validity

### R6: Engineering Plots

The Python tools shall generate engineering plots for:

- Altitude profile
- Vertical acceleration
- Gyroscope X-axis
- Battery voltage
- Barometric pressure

### R7: Future Hardware Integration

The system shall be designed so simulated telemetry can later be replaced with real embedded sensor readings from:

- IMU
- Barometer
- GPS module
- Battery monitor
- SD card logger

## Non-Functional Requirements

### Reliability

The system should detect corrupted or missing telemetry records.

### Modularity

The project should separate firmware, analysis tools, tests, documentation, and generated data.

### Testability

The system should include automated tests for key telemetry functions.

### Documentation

The repository should include architecture notes, packet specifications, test plans, and hardware plans.

## Current Project Status

Part 1 is complete:

- Telemetry simulator
- CSV log generation
- CRC validation
- Plot generation
- Automated tests
- GitHub repository setup

Part 2 adds formal engineering documentation before hardware work begins.
