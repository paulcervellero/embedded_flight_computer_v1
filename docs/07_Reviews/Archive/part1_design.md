# Part 1 Design Notes

## Purpose

Part 1 creates the telemetry foundation for the Embedded Flight Computer project.

Before connecting real embedded hardware, the system defines:

- A telemetry packet format
- Flight states
- Sensor-style data fields
- CRC validation
- Python analysis tools
- Automated tests

This allows the telemetry pipeline to be tested before hardware is introduced.

## Telemetry Fields

Each telemetry record contains:

- Sequence number
- Timestamp
- Flight state
- Acceleration values
- Gyroscope values
- Barometric pressure
- Estimated altitude
- Battery voltage
- GPS fix status
- Latitude and longitude
- CRC-16 checksum

## Flight States

The simulated flight uses four states:

1. PRELAUNCH
2. ASCENT
3. DESCENT
4. LANDED

## Validation Checks

The validator checks:

- Correct CSV header
- CRC checksum integrity
- Sequence continuity
- Timing consistency
- Battery range
- Altitude range
- GPS fix value

## Why This Matters

In an embedded system, the hardware is only one part of the project. A strong system also needs repeatable testing, logging, validation, and analysis tools.

This part proves that the project has a clean data interface before firmware and sensors are added.
