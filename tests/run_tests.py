from __future__ import annotations

import sys
import tempfile
from pathlib import Path

PROJECT_ROOT = Path(__file__).resolve().parents[1]
TOOLS_DIR = PROJECT_ROOT / "tools"

sys.path.insert(0, str(TOOLS_DIR))

from generate_sample_log import generate_records
from telemetry_schema import crc_hex, read_records, validate_records, write_records


def test_crc_known_value() -> None:
    assert crc_hex("123456789") == "29B1"


def test_generated_log_validates() -> None:
    records = generate_records(duration_s=12.0, rate_hz=10.0)
    errors = validate_records(records, expected_rate_hz=10.0)

    assert not errors, errors[:5]


def test_csv_round_trip() -> None:
    records = generate_records(duration_s=5.0, rate_hz=10.0)

    with tempfile.TemporaryDirectory() as temp_dir:
        path = Path(temp_dir) / "flight.csv"
        write_records(path, records)
        loaded = read_records(path)

    assert len(loaded) == len(records)
    assert loaded[0].crc16 == records[0].crc16
    assert loaded[-1].seq == records[-1].seq


def test_corrupted_crc_fails() -> None:
    records = generate_records(duration_s=2.0, rate_hz=10.0)

    corrupted_records = records.copy()
    corrupted_records[3] = corrupted_records[3].__class__(
        **{
            **corrupted_records[3].__dict__,
            "crc16": "FFFF",
        }
    )

    errors = validate_records(corrupted_records, expected_rate_hz=10.0)

    assert any("CRC mismatch" in error for error in errors)


def main() -> None:
    tests = [
        test_crc_known_value,
        test_generated_log_validates,
        test_csv_round_trip,
        test_corrupted_crc_fails,
    ]

    for test in tests:
        test()
        print(f"PASS {test.__name__}")

    print("All tests passed.")


if __name__ == "__main__":
    main()
