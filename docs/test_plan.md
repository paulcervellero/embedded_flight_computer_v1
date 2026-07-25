# Test Plan

## Project Name

Project Falcon – Embedded Flight Computer & Telemetry Logger

---

# Purpose

This document defines the verification strategy used throughout Project Falcon.

Testing will be performed incrementally as new firmware, hardware, and software components are introduced.

Each subsystem must pass its individual tests before integration into the complete system.

---

# Testing Philosophy

The project follows a staged verification process.

1. Verify each component independently.
2. Integrate one new component at a time.
3. Re-test existing functionality after every integration.
4. Document all observed failures and corrective actions.

This approach reduces debugging time and improves overall system reliability.

---

# Phase 1 – Software Validation

Objective:

Verify the Python telemetry tools.

Tests:

- Telemetry packet generation
- CRC validation
- CSV logging
- Plot generation
- Automated unit tests

Expected Result:

All software tools execute successfully without errors.

---

# Phase 2 – Firmware Validation

Objective:

Verify STM32 firmware functionality.

Tests:

- LED heartbeat
- GPIO operation
- UART transmission
- Flight state machine
- Telemetry packet generation

Expected Result:

The STM32 continuously generates valid telemetry packets.

---

# Phase 3 – Sensor Validation

Objective:

Verify each sensor independently.

Tests:

## IMU

- Read acceleration
- Read angular velocity
- Verify stable output

## Barometer

- Read pressure
- Calculate altitude
- Verify repeatability

## GPS

- Acquire satellite lock
- Read latitude and longitude
- Verify timestamp data

Expected Result:

Each sensor produces consistent and valid measurements.

---

# Phase 4 – System Integration

Objective:

Verify complete system operation.

Tests:

- Telemetry packet transmission
- Python logger reception
- CSV generation
- Plot generation
- CRC verification
- SD card logging

Expected Result:

All subsystems operate together without data loss.

---

# Acceptance Criteria

Project Falcon will be considered functionally complete when:

- All firmware compiles successfully.
- All sensors communicate correctly.
- Telemetry packets pass CRC validation.
- Python tools successfully decode every packet.
- Data is logged to the SD card.
- Engineering plots are generated correctly.
- Documentation reflects the final implementation.

---

# Test Documentation

Every major milestone will include:

- Test objective
- Test procedure
- Expected result
- Actual result
- Pass/Fail status
- Notes and observations

All significant testing results will be stored in the `reports/` directory.

---

# Continuous Improvement

Any defect discovered during testing will be:

1. Documented.
2. Investigated.
3. Corrected.
4. Re-tested.
5. Recorded in the project history.

This process helps ensure that improvements do not introduce regressions into previously verified functionality.