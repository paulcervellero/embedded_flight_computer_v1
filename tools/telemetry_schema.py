from __future__ import annotations

import csv
from dataclasses import dataclass
from pathlib import Path
from typing import Iterable


HEADER = [
    "seq",
    "time_ms",
    "state",
    "accel_x_g",
    "accel_y_g",
    "accel_z_g",
    "gyro_x_dps",
    "gyro_y_dps",
    "gyro_z_dps",
    "pressure_hpa",
    "altitude_m",
    "batt_mv",
    "gps_fix",
    "lat_deg",
    "lon_deg",
    "crc16",
]

VALID_STATES = {"PRELAUNCH", "ASCENT", "DESCENT", "LANDED"}


@dataclass(frozen=True)
class TelemetryRecord:
    seq: int
    time_ms: int
    state: str
    accel_x_g: float
    accel_y_g: float
    accel_z_g: float
    gyro_x_dps: float
    gyro_y_dps: float
    gyro_z_dps: float
    pressure_hpa: float
    altitude_m: float
    batt_mv: int
    gps_fix: int
    lat_deg: float
    lon_deg: float
    crc16: str

    @classmethod
    def from_row(cls, row: dict[str, str]) -> "TelemetryRecord":
        missing_fields = [field for field in HEADER if field not in row]

        if missing_fields:
            raise ValueError(f"Missing fields in telemetry row: {missing_fields}")

        return cls(
            seq=int(row["seq"]),
            time_ms=int(row["time_ms"]),
            state=row["state"],
            accel_x_g=float(row["accel_x_g"]),
            accel_y_g=float(row["accel_y_g"]),
            accel_z_g=float(row["accel_z_g"]),
            gyro_x_dps=float(row["gyro_x_dps"]),
            gyro_y_dps=float(row["gyro_y_dps"]),
            gyro_z_dps=float(row["gyro_z_dps"]),
            pressure_hpa=float(row["pressure_hpa"]),
            altitude_m=float(row["altitude_m"]),
            batt_mv=int(row["batt_mv"]),
            gps_fix=int(row["gps_fix"]),
            lat_deg=float(row["lat_deg"]),
            lon_deg=float(row["lon_deg"]),
            crc16=row["crc16"].strip().upper(),
        )

    def row_without_crc(self) -> str:
        values = [
            str(self.seq),
            str(self.time_ms),
            self.state,
            f"{self.accel_x_g:.3f}",
            f"{self.accel_y_g:.3f}",
            f"{self.accel_z_g:.3f}",
            f"{self.gyro_x_dps:.3f}",
            f"{self.gyro_y_dps:.3f}",
            f"{self.gyro_z_dps:.3f}",
            f"{self.pressure_hpa:.2f}",
            f"{self.altitude_m:.2f}",
            str(self.batt_mv),
            str(self.gps_fix),
            f"{self.lat_deg:.6f}",
            f"{self.lon_deg:.6f}",
        ]

        return ",".join(values)


def crc16_ccitt_false(text: str) -> int:
    """
    CRC-16/CCITT-FALSE
    Polynomial: 0x1021
    Initial value: 0xFFFF
    Check value for "123456789": 0x29B1
    """
    crc = 0xFFFF

    for byte in text.encode("utf-8"):
        crc ^= byte << 8

        for _ in range(8):
            if crc & 0x8000:
                crc = ((crc << 1) ^ 0x1021) & 0xFFFF
            else:
                crc = (crc << 1) & 0xFFFF

    return crc


def crc_hex(text: str) -> str:
    return f"{crc16_ccitt_false(text):04X}"


def read_records(csv_path: str | Path) -> list[TelemetryRecord]:
    path = Path(csv_path)

    with path.open("r", newline="") as file:
        reader = csv.DictReader(file)

        if reader.fieldnames != HEADER:
            raise ValueError(
                f"Unexpected CSV header. Expected {HEADER}, got {reader.fieldnames}"
            )

        return [TelemetryRecord.from_row(row) for row in reader]


def write_records(csv_path: str | Path, records: Iterable[TelemetryRecord]) -> None:
    path = Path(csv_path)
    path.parent.mkdir(parents=True, exist_ok=True)

    with path.open("w", newline="") as file:
        writer = csv.writer(file)
        writer.writerow(HEADER)

        for record in records:
            writer.writerow(
                [
                    record.seq,
                    record.time_ms,
                    record.state,
                    f"{record.accel_x_g:.3f}",
                    f"{record.accel_y_g:.3f}",
                    f"{record.accel_z_g:.3f}",
                    f"{record.gyro_x_dps:.3f}",
                    f"{record.gyro_y_dps:.3f}",
                    f"{record.gyro_z_dps:.3f}",
                    f"{record.pressure_hpa:.2f}",
                    f"{record.altitude_m:.2f}",
                    record.batt_mv,
                    record.gps_fix,
                    f"{record.lat_deg:.6f}",
                    f"{record.lon_deg:.6f}",
                    record.crc16,
                ]
            )


def validate_records(
    records: list[TelemetryRecord],
    expected_rate_hz: float = 10.0,
) -> list[str]:
    errors: list[str] = []

    if not records:
        return ["No telemetry records found"]

    expected_dt_ms = int(round(1000.0 / expected_rate_hz))
    previous_seq: int | None = None
    previous_time_ms: int | None = None

    for index, record in enumerate(records):
        if record.state not in VALID_STATES:
            errors.append(f"Row {index}: invalid flight state: {record.state}")

        computed_crc = crc_hex(record.row_without_crc())

        if computed_crc != record.crc16:
            errors.append(
                f"Row {index}: CRC mismatch. Expected {computed_crc}, got {record.crc16}"
            )

        if previous_seq is not None:
            expected_seq = previous_seq + 1

            if record.seq != expected_seq:
                errors.append(
                    f"Row {index}: sequence error. Expected {expected_seq}, got {record.seq}"
                )

        if previous_time_ms is not None:
            dt_ms = record.time_ms - previous_time_ms

            if abs(dt_ms - expected_dt_ms) > 25:
                errors.append(
                    f"Row {index}: timing jitter too high. "
                    f"Expected about {expected_dt_ms} ms, got {dt_ms} ms"
                )

        if record.altitude_m < -5.0:
            errors.append(
                f"Row {index}: altitude below expected range: {record.altitude_m}"
            )

        if not 6500 <= record.batt_mv <= 9000:
            errors.append(
                f"Row {index}: battery voltage outside expected range: {record.batt_mv}"
            )

        if record.gps_fix not in (0, 1):
            errors.append(f"Row {index}: gps_fix must be 0 or 1, got {record.gps_fix}")

        previous_seq = record.seq
        previous_time_ms = record.time_ms

    return errors
