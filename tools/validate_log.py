from __future__ import annotations

import argparse
from statistics import mean

from telemetry_schema import read_records, validate_records


def main() -> None:
    parser = argparse.ArgumentParser(
        description="Validate a flight telemetry CSV log."
    )

    parser.add_argument(
        "log",
        help="Path to telemetry CSV file",
    )

    parser.add_argument(
        "--rate-hz",
        type=float,
        default=10.0,
        help="Expected telemetry sample rate in Hz",
    )

    args = parser.parse_args()

    records = read_records(args.log)
    errors = validate_records(records, expected_rate_hz=args.rate_hz)

    if records:
        duration_s = (records[-1].time_ms - records[0].time_ms) / 1000.0
        max_altitude = max(record.altitude_m for record in records)
        min_battery = min(record.batt_mv for record in records)

        avg_dt_ms = (
            mean(
                records[i].time_ms - records[i - 1].time_ms
                for i in range(1, len(records))
            )
            if len(records) > 1
            else 0.0
        )

        print("Telemetry summary")
        print(f"  Records:      {len(records)}")
        print(f"  Duration:     {duration_s:.2f} s")
        print(f"  Average dt:   {avg_dt_ms:.2f} ms")
        print(f"  Max altitude: {max_altitude:.2f} m")
        print(f"  Min battery:  {min_battery} mV")

    if errors:
        print("\nValidation failed:")

        for error in errors[:50]:
            print(f"  - {error}")

        if len(errors) > 50:
            print(f"  ... plus {len(errors) - 50} more errors")

        raise SystemExit(1)

    print("\nValidation passed: CRC, sequence timing, and ranges look good.")


if __name__ == "__main__":
    main()
