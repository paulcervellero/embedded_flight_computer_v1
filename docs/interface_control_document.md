# Interface Control Document (ICD)

## Project

Project Falcon – Embedded Flight Computer & Telemetry Logger

---

# Purpose

This document defines every electrical and logical interface used by Project Falcon.

The ICD serves as the single source of truth for hardware communication and interface configuration.

---

# System Interfaces

## UART1 — GPS Receiver

Purpose:

Receive GPS position and timing information.

Configuration

| Parameter | Value |
|-----------|-------|
| Baud Rate | 115200 |
| Data Bits | 8 |
| Stop Bits | 1 |
| Parity | None |
| Flow Control | None |

Protocol:

NMEA 0183

---

## UART2 — PC Telemetry

Purpose:

Transmit telemetry packets to the host computer.

Configuration

| Parameter | Value |
|-----------|-------|
| Baud Rate | 115200 |
| Data Bits | 8 |
| Stop Bits | 1 |
| Parity | None |

Protocol:

Custom Falcon Telemetry Packet V1

---

## I²C1 — Sensor Bus

Purpose:

Connect environmental sensors.

Devices

- BMP280
- IMU

Configuration

| Parameter | Value |
|-----------|-------|
| Speed | 400 kHz |
| Mode | Master |

---

## SPI1 — microSD

Purpose

Telemetry logging.

Configuration

| Parameter | Value |
|-----------|-------|
| Mode | SPI Master |
| Clock | 10 MHz (initial target) |

---

# Interface Philosophy

Each peripheral shall own one clearly defined responsibility.

Interfaces should remain stable throughout Project Falcon Version 1.

Any future interface modifications must be documented before implementation.