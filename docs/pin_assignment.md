# STM32 Pin Assignment

## Project

Project Falcon – Embedded Flight Computer & Telemetry Logger

---

# Purpose

This document defines the STM32 pin assignments for all hardware interfaces used by Project Falcon Version 1.

This document is the authoritative reference for firmware development and hardware wiring.

---

> **Engineering Note**
>
> This document contains the preliminary pin assignments for Project Falcon Version 1.
>
> Final pin assignments will be verified against:
> - The STM32 NUCLEO-F401RE schematic
> - The STM32F401RE datasheet
> - The selected sensor module datasheets
>
> No pin assignments are considered final until the Hardware Readiness Review (HRR) is completed.

# Preliminary Pin Assignment Table

| STM32 Pin | Peripheral | Connected Device | Direction | Notes |
|-----------|------------|------------------|-----------|-------|
| PA9 | USART1_TX | GPS RX | Output | GPS Communication |
| PA10 | USART1_RX | GPS TX | Input | GPS Communication |
| PA2 | USART2_TX | USB Virtual COM | Output | PC Telemetry |
| PA3 | USART2_RX | USB Virtual COM | Input | Debug Console |
| PB8 | I²C1_SCL | IMU + BMP280 | Output | Shared I²C Clock |
| PB9 | I²C1_SDA | IMU + BMP280 | Bidirectional | Shared I²C Data |
| PA5 | SPI1_SCK | microSD | Output | SPI Clock |
| PA6 | SPI1_MISO | microSD | Input | SPI Data |
| PA7 | SPI1_MOSI | microSD | Output | SPI Data |
| PA4 | SPI1_CS | microSD | Output | Chip Select |
| PA5 | LED (User LED) | Onboard LED | Output | Heartbeat Indicator |

---

# Interface Summary

## USART1

Purpose:

GPS Receiver

Configuration:

115200 baud

---

## USART2

Purpose:

Telemetry Output

Configuration:

115200 baud

---

## I²C1

Purpose:

Sensor Bus

Devices

- IMU
- BMP280

Speed

400 kHz

---

## SPI1

Purpose

microSD Logging

Mode

SPI Master

---

# Design Rules

Project Falcon follows the following hardware rules:

- One peripheral has one responsibility.
- Pins are never reassigned without documentation.
- Interfaces remain stable throughout Version 1 whenever practical.
- Hardware documentation must be updated before firmware changes affecting interfaces are merged.

---

# Revision History

| Version | Description |
|----------|-------------|
| 1.0 | Initial Pin Assignment |