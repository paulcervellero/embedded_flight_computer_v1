# Telemetry Packet Specification

## Project Name

Project Falcon – Embedded Flight Computer & Telemetry Logger

---

# Purpose

This document defines the telemetry packet format used throughout Project Falcon.

Every subsystem communicates using this packet structure.

The packet format is intentionally fixed-length to simplify parsing, validation, logging, and future hardware expansion.

---

# Packet Overview

Each telemetry packet contains:

- Packet synchronization bytes
- Packet counter
- Flight state
- System timestamp
- Sensor data
- CRC for error detection

---

# Packet Structure

| Byte(s) | Field | Type | Description |
|---------:|-------|------|-------------|
| 0-1 | Sync Word | uint16 | Packet start identifier (0xAA55) |
| 2 | Packet ID | uint8 | Sequential packet number |
| 3 | Flight State | uint8 | Current flight mode |
| 4-7 | Timestamp | uint32 | Milliseconds since startup |
| 8-11 | Altitude | float | Altitude (meters) |
| 12-15 | Velocity | float | Vertical velocity (m/s) |
| 16-19 | Temperature | float | Temperature (°C) |
| 20-23 | Pressure | float | Pressure (Pa) |
| 24-27 | Battery Voltage | float | System voltage |
| 28-29 | CRC16 | uint16 | Packet integrity check |

# Packet Layout

```
+---------+----------+--------------+-------------+
| Sync    | PacketID | Flight State | Timestamp   |
| 2 Bytes | 1 Byte   | 1 Byte       | 4 Bytes     |
+---------+----------+--------------+-------------+
| Altitude (4) | Velocity (4) | Temperature (4) |
+-----------------------------------------------+
| Pressure (4) | Battery Voltage (4) | CRC (2)   |
+-----------------------------------------------+

Total Packet Size = 30 Bytes
```

---

# Packet Size

Total packet size:

30 bytes

Every packet transmitted by the flight computer shall contain exactly 30 bytes.

---

# Flight States

| Value | State |
|-------:|-------|
| 0 | Idle |
| 1 | Initialization |
| 2 | Ready |
| 3 | Launch |
| 4 | Ascent |
| 5 | Apogee |
| 6 | Descent |
| 7 | Landing |

---

# Synchronization Word

The synchronization word identifies the beginning of every telemetry packet.

Value:

```
0xAA55
```

If synchronization is lost, the receiver searches for the next synchronization word before continuing packet decoding.

---

# Packet Counter

The packet counter increments by one for every transmitted packet.

Purpose:

- Detect dropped packets
- Verify communication reliability
- Simplify debugging

---

# Timestamp

The timestamp represents the number of milliseconds since system startup.

This value allows every telemetry sample to be associated with a precise point in time.

---

# Sensor Fields

The initial implementation includes:

- Altitude
- Velocity
- Temperature
- Pressure
- Battery Voltage

Additional sensors may be appended in future revisions while maintaining backward compatibility where practical.

---

# CRC

Each packet ends with a 16-bit CRC.

The receiver recalculates the CRC after reception.

If the calculated CRC differs from the transmitted CRC, the packet is discarded.

---

# Engineering Design Notes

The packet is intentionally compact to minimize UART bandwidth while remaining readable and extensible.

The packet format is fixed-length because predictable packet sizes simplify embedded firmware, desktop software, automated testing, and validation tools.

Future versions may introduce additional telemetry fields while preserving compatibility through version-controlled protocol updates.

# Future Expansion

The current packet structure represents Version 1 of the Project Falcon telemetry protocol.

Future revisions may introduce additional telemetry fields such as:

- GPS Latitude
- GPS Longitude
- Roll
- Pitch
- Yaw
- Accelerometer Data
- Gyroscope Data
- Magnetometer Data

Protocol changes will be documented through version-controlled updates to preserve compatibility between firmware and software components.