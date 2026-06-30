from __future__ import annotations

import argparse
import math
import random
from pathlib import Path

from telemetry_schema import TelemetryRecord, crc_hex, write_records


def pressure_from_altitude_hpa(altitude_m: float) -> float:
    ratio = max(0.01, min(1.2, 1.0 - altitude_m / 44330.0))
    return 1013.25 * (ratio ** 5.255)


def smoothstep(x: float) -> float:
    x = max(0.0, min(1.0, x))
    return x * x * (3.0 - 2.0 * x)


def state_at_time(t_s: float) -> str:
    if t_s < 10.0:
        return "PRELAUNCH"

    if t_s < 35.0:
        return "ASCENT"

    if t_s < 70.0:
        return "DESCENT"

    return "LANDED"


def altitude_at_time(t_s: float) -> float:
    if t_s < 10.0:
        return 0.15 * math.sin(t_s * 2.0)

    if t_s < 35.0:
        x = (t_s - 10.0) / 25.0
        return 520.0 * smoothstep(x)

    if t_s < 70.0:
        x = (t_s - 35.0) / 35.0
        return 520.0 * (1.0 - smoothstep(x))

    return 0.0


def accel_z_for_state(t_s: float, state: str) -> float:
    if state == "PRELAUNCH":
        return 1.000 + random.uniform(-0.025, 0.025)

    if state == "ASCENT":
        return 1.260 + 0.08 * math.sin(t_s * 0.7) + random.uniform(-0.025, 0.025)

    if state == "DESCENT":
        return 0.830 + 0.07 * math.sin(t_s * 0.9) + random.uniform(-0.025, 0.025)

    return 1.000 + random.uniform(-0.025, 0.025)


def make_record(seq: int, time_ms: int) -> TelemetryRecord:
    t_s = time_ms / 1000.0
    state = state_at_time(t_s)
    altitude_m = altitude_at_time(t_s)
    pressure_hpa = pressure_from_altitude_hpa(altitude_m)
    batt_mv = max(7200, 8400 - int(t_s * 4.0))
    gps_fix = 1 if t_s > 3.0 else 0

    record_without_crc = TelemetryRecord(
        seq=seq,
        time_ms=time_ms,
        state=state,
        accel_x_g=0.020 * math.sin(t_s * 0.8) + random.uniform(-0.010, 0.010),
        accel_y_g=0.018 * math.cos(t_s * 0.6) + random.uniform(-0.010, 0.010),
        accel_z_g=accel_z_for_state(t_s, state),
        gyro_x_dps=1.50 * math.sin(t_s * 0.35) + random.uniform(-0.050, 0.050),
        gyro_y_dps=1.10 * math.cos(t_s * 0.40) + random.uniform(-0.050, 0.050),
        gyro_z_dps=0.80 * math.sin(t_s * 0.25) + random.uniform(-0.050, 0.050),
        pressure_hpa=pressure_hpa,
        altitude_m=altitude_m,
        batt_mv=batt_mv,
        gps_fix=gps_fix,
        lat_deg=34.000000 + 0.000015 * t_s,
        lon_deg=-81.000000 - 0.000012 * t_s,
        crc16="0000",
    )

    return TelemetryRecord(
        **{
            **record_without_crc.__dict__,
            "crc16": crc_hex(record_without_crc.row_without_crc()),
        }
    )


def generate_records(duration_s: float, rate_hz: float) -> list[TelemetryRecord]:
    if duration_s <= 0:
        raise ValueError("duration_s must be positive")

    if rate_hz <= 0:
        raise ValueError("rate_hz must be positive")

    random.seed(221)

    sample_count = int(duration_s * rate_hz)
    dt_ms = int(round(1000.0 / rate_hz))

    return [make_record(seq=i, time_ms=i * dt_ms) for i in range(sample_count)]


def main() -> None:
    parser = argparse.ArgumentParser(
        description="Generate a simulated flight telemetry CSV log."
    )

    parser.add_argument(
        "--out",
        default="sample_data/flight_log_sample.csv",
        help="Output CSV path",
    )

    parser.add_argument(
        "--duration",
        type=float,
        default=90.0,
        help="Duration in seconds",
    )

    parser.add_argument(
        "--rate-hz",
        type=float,
        default=10.0,
        help="Telemetry sample rate in Hz",
    )

    args = parser.parse_args()

    records = generate_records(duration_s=args.duration, rate_hz=args.rate_hz)
    write_records(Path(args.out), records)

    print(f"Wrote {len(records)} records to {args.out}")


if __name__ == "__main__":
    main()
