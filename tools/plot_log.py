from __future__ import annotations

import argparse
from pathlib import Path

import matplotlib.pyplot as plt

from telemetry_schema import read_records


def save_plot(
    x_values: list[float],
    y_values: list[float],
    xlabel: str,
    ylabel: str,
    title: str,
    out_path: Path,
) -> None:
    plt.figure()
    plt.plot(x_values, y_values)
    plt.xlabel(xlabel)
    plt.ylabel(ylabel)
    plt.title(title)
    plt.grid(True)
    plt.tight_layout()
    plt.savefig(out_path, dpi=150)
    plt.close()


def main() -> None:
    parser = argparse.ArgumentParser(
        description="Create engineering plots from telemetry CSV data."
    )

    parser.add_argument(
        "log",
        help="Path to telemetry CSV file",
    )

    parser.add_argument(
        "--out",
        default="reports",
        help="Output directory for generated plots",
    )

    args = parser.parse_args()

    records = read_records(args.log)

    if not records:
        raise SystemExit("No records found")

    out_dir = Path(args.out)
    out_dir.mkdir(parents=True, exist_ok=True)

    time_s = [record.time_ms / 1000.0 for record in records]

    save_plot(
        time_s,
        [record.altitude_m for record in records],
        "Time (s)",
        "Altitude (m)",
        "Altitude Profile",
        out_dir / "altitude_profile.png",
    )

    save_plot(
        time_s,
        [record.accel_z_g for record in records],
        "Time (s)",
        "Vertical Acceleration (g)",
        "Vertical Acceleration",
        out_dir / "acceleration_z.png",
    )

    save_plot(
        time_s,
        [record.gyro_x_dps for record in records],
        "Time (s)",
        "Gyro X (deg/s)",
        "Gyroscope X-Axis",
        out_dir / "gyro_x.png",
    )

    save_plot(
        time_s,
        [record.batt_mv for record in records],
        "Time (s)",
        "Battery Voltage (mV)",
        "Battery Voltage",
        out_dir / "battery_voltage.png",
    )

    save_plot(
        time_s,
        [record.pressure_hpa for record in records],
        "Time (s)",
        "Pressure (hPa)",
        "Barometric Pressure",
        out_dir / "pressure.png",
    )

    print(f"Saved plots to {out_dir}")


if __name__ == "__main__":
    main()
