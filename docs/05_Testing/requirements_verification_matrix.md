# Requirements Verification Matrix

---

# Document Information

| Item | Value |
|------|-------|
| Project | Project Falcon |
| Document | Requirements Verification Matrix |
| Document ID | PF-CDR-006 |
| Revision | 1.0 |
| Status | Draft |
| Author | Paul Cervellero |
| Last Updated | July 2026 |

---

# Purpose

This document provides traceability between Project Falcon requirements and their planned verification methods.

No requirement is considered complete until it has been successfully verified.

---

# Verification Methods

| Method | Description |
|---------|-------------|
| Analysis | Mathematical or design verification |
| Inspection | Visual review of hardware or documentation |
| Demonstration | Functional operation observed |
| Test | Measured performance against requirements |

---

# Requirements Verification Matrix

| Requirement ID | Requirement | Verification Method | Evidence | Status |
|----------------|-------------|---------------------|----------|--------|
| R-001 | System shall generate telemetry packets | Test | UART telemetry capture | Pending |
| R-002 | Telemetry packets shall include CRC16 | Test | Python validator | Pending |
| R-003 | System shall log telemetry to SD card | Demonstration | SD card log review | Pending |
| R-004 | GPS data shall be received over UART | Test | Serial terminal output | Pending |
| R-005 | IMU data shall be acquired over I²C | Test | Sensor validation report | Pending |
| R-006 | Pressure data shall be acquired over I²C | Test | Sensor validation report | Pending |
| R-007 | Firmware shall compile successfully | Inspection | Successful build output | Pending |
| R-008 | Flight state machine shall transition correctly | Test | State machine test report | Pending |
| R-009 | Python tools shall decode telemetry | Demonstration | CSV output and plots | Pending |
| R-010 | Documentation shall match implementation | Inspection | Engineering review | Pending |

---

# Verification Philosophy

Every engineering requirement must have:

- A verification method
- Objective evidence
- A documented result

Requirements without verification are considered incomplete.

---

# Completion Criteria

Project Falcon Version 1.0 will not be considered complete until:

- Every requirement has evidence.
- Every verification activity has been completed.
- Every status is marked **Verified**.
- All supporting reports are stored in the `reports/` directory.

---

# Continuous Verification

Verification is performed throughout development rather than only at the end of the project.

This approach allows defects to be identified early and reduces integration risk.