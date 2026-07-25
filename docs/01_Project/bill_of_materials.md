# Bill of Materials (BOM)

## Project Name

Project Falcon – Embedded Flight Computer & Telemetry Logger

---

# Purpose

This document lists every major hardware component required to build Project Falcon.

Each component has been selected based on reliability, documentation quality, industry acceptance, and compatibility with the STM32 platform.

---

# Hardware Summary

| Component | Manufacturer / Model | Estimated Price | Supplier | Purpose |
|-----------|----------------------|----------------:|----------|---------|
| STM32 Development Board | ST NUCLEO-F401RE | ~$22 | DigiKey / Mouser | Main Flight Computer |
| IMU | Adafruit BNO055 Breakout | ~$35 | Adafruit | Orientation & Motion |
| Barometer | Adafruit BMP280 Breakout | ~$15 | Adafruit | Pressure & Altitude |
| GPS Module | u-blox NEO-M8N | ~$30 | SparkFun / DigiKey | Position & Time |
| microSD Breakout | Adafruit MicroSD SPI Breakout | ~$10 | Adafruit | Telemetry Storage |
| Breadboard | 830 Tie Point Breadboard | ~$10 | Amazon | Prototype Development |
| Jumper Wire Kit | Male/Male + Male/Female | ~$10 | Amazon | Wiring |
| USB Cable | USB-A to Micro-USB | ~$8 | Amazon | Programming & Debugging |

---

# Estimated Total Cost

| Category | Cost |
|----------|------:|
| Development Board | ~$22 |
| Sensors | ~$80 |
| Prototyping Supplies | ~$28 |

**Estimated Total:** **$130–140**

---

# Why These Parts?

## STM32 NUCLEO-F401RE

Reasons:

- Official STMicroelectronics board
- Integrated ST-LINK debugger
- Large community support
- Widely used in university and industry
- Excellent STM32CubeIDE support

---

## BNO055 IMU

Reasons:

- Built-in sensor fusion
- Easy to begin development
- Stable I²C interface
- Reliable documentation

Future versions of Project Falcon may transition to a lower-level IMU for custom sensor fusion algorithms.

---

## BMP280

Reasons:

- High accuracy
- Widely supported
- Reliable altitude estimation
- Simple I²C interface

---

## u-blox NEO-M8N GPS

Reasons:

- Excellent documentation
- Fast satellite acquisition
- Reliable UART interface
- Better performance than older NEO-6M modules

---

## microSD SPI Breakout

Reasons:

- Industry-standard SPI communication
- Reliable logging
- Easy integration with STM32

---

# Optional Future Hardware

The following components are not required for Version 1 but are potential future upgrades.

- OLED Display
- LoRa Radio
- CAN Bus Transceiver
- External Flash Memory
- Battery Management System
- FPGA Co-Processor

---

# Purchasing Strategy

Hardware will be purchased in two stages.

## Stage 1

- STM32 Development Board
- Breadboard
- Jumper Wires
- USB Cable

Purpose:

Begin firmware development immediately.

---

## Stage 2

- IMU
- BMP280
- GPS
- microSD Module

Purpose:

Begin hardware integration after firmware validation.

---

# Version History

| Version | Date | Notes |
|----------|------|-------|
| 1.0 | July 2026 | Initial BOM created |