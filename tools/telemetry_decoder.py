#!/usr/bin/env python3
"""
Project Falcon
Telemetry packet decoder for Falcon's 30-byte binary frame.
"""

from __future__ import annotations

import struct
import sys
from dataclasses import dataclass


PACKET_SIZE = 30
SYNC_WORD = 0xAA55
CRC_POLY = 0x1021


FLIGHT_STATES = {
    0: "IDLE",
    1: "INITIALIZATION",
    2: "READY",
    3: "LAUNCH",
    4: "ASCENT",
    5: "APOGEE",
    6: "DESCENT",
    7: "LANDING",
}


@dataclass
class TelemetryPacket:
    packet_id: int
    flight_state: int
    timestamp_ms: int
    altitude_m: float
    vertical_velocity_mps: float
    temperature_c: float
    pressure_pa: float
    battery_voltage_v: float
    crc16: int


def crc16_ccitt_false(data: bytes) -> int:
    crc = 0xFFFF
    for byte in data:
        crc ^= byte << 8
        for _ in range(8):
            if crc & 0x8000:
                crc = ((crc << 1) ^ CRC_POLY) & 0xFFFF
            else:
                crc = (crc << 1) & 0xFFFF
    return crc


def decode_packet(packet: bytes) -> TelemetryPacket:
    if len(packet) != PACKET_SIZE:
        raise ValueError(f"Packet must be exactly {PACKET_SIZE} bytes")

    sync_word = struct.unpack_from("<H", packet, 0)[0]
    if sync_word != SYNC_WORD:
        raise ValueError(f"Bad sync word: 0x{sync_word:04X}")

    packet_id = packet[2]
    flight_state = packet[3]
    timestamp_ms = struct.unpack_from("<I", packet, 4)[0]
    altitude_m = struct.unpack_from("<f", packet, 8)[0]
    vertical_velocity_mps = struct.unpack_from("<f", packet, 12)[0]
    temperature_c = struct.unpack_from("<f", packet, 16)[0]
    pressure_pa = struct.unpack_from("<f", packet, 20)[0]
    battery_voltage_v = struct.unpack_from("<f", packet, 24)[0]
    crc16 = struct.unpack_from("<H", packet, 28)[0]

    computed_crc = crc16_ccitt_false(packet[:28])
    if computed_crc != crc16:
        raise ValueError(
            f"CRC mismatch: packet=0x{crc16:04X}, computed=0x{computed_crc:04X}"
        )

    return TelemetryPacket(
        packet_id=packet_id,
        flight_state=flight_state,
        timestamp_ms=timestamp_ms,
        altitude_m=altitude_m,
        vertical_velocity_mps=vertical_velocity_mps,
        temperature_c=temperature_c,
        pressure_pa=pressure_pa,
        battery_voltage_v=battery_voltage_v,
        crc16=crc16,
    )


def format_packet(pkt: TelemetryPacket) -> str:
    state_name = FLIGHT_STATES.get(pkt.flight_state, f"UNKNOWN({pkt.flight_state})")
    return (
        f"Packet ID:            {pkt.packet_id}\n"
        f"Flight State:         {state_name}\n"
        f"Timestamp (ms):       {pkt.timestamp_ms}\n"
        f"Altitude (m):         {pkt.altitude_m:.3f}\n"
        f"Vertical Velocity:    {pkt.vertical_velocity_mps:.3f} m/s\n"
        f"Temperature:          {pkt.temperature_c:.3f} C\n"
        f"Pressure:             {pkt.pressure_pa:.3f} Pa\n"
        f"Battery Voltage:       {pkt.battery_voltage_v:.3f} V\n"
        f"CRC16:                0x{pkt.crc16:04X}"
    )


def main() -> int:
    if len(sys.argv) != 2:
        print(f"Usage: {sys.argv[0]} <hex_packet>")
        print("Example:")
        print(f"  {sys.argv[0]} AA550000E80300000000000000000000000000000000000000000000BEEF")
        return 1

    hex_packet = sys.argv[1].strip().replace(" ", "")
    try:
        packet = bytes.fromhex(hex_packet)
        decoded = decode_packet(packet)
        print(format_packet(decoded))
        return 0
    except ValueError as exc:
        print(f"Error: {exc}", file=sys.stderr)
        return 1


if __name__ == "__main__":
    raise SystemExit(main())