# Risk Register

---

# Document Information

| Item | Value |
|------|-------|
| Project | Project Falcon |
| Document | Risk Register |
| Document ID | PF-CDR-005 |
| Revision | 1.0 |
| Status | Draft |
| Author | Paul Cervellero |
| Last Updated | July 2026 |

---

# Purpose

This document identifies technical risks associated with Project Falcon and defines mitigation strategies before implementation begins.

The objective is to reduce development risk through proactive engineering.

---

# Risk Assessment Scale

## Probability

| Rating | Description |
|---------|-------------|
| Low | Unlikely to occur |
| Medium | Possible |
| High | Expected or likely |

---

## Impact

| Rating | Description |
|---------|-------------|
| Low | Minor inconvenience |
| Medium | Delays development |
| High | Prevents system operation |

---

# Risk Register

| ID | Risk | Probability | Impact | Mitigation |
|----|------|-------------|--------|------------|
| R-001 | GPS unavailable indoors | High | Medium | Use telemetry simulator during indoor development |
| R-002 | Incorrect pin assignments | Medium | High | Verify against official STM32 schematics before wiring |
| R-003 | Sensor communication failure | Medium | High | Validate each sensor independently before integration |
| R-004 | SD card write failures | Low | High | Implement error handling and verify write status |
| R-005 | UART packet corruption | Medium | Medium | CRC16 validation on every packet |
| R-006 | Power instability | Low | High | Verify voltage requirements before hardware integration |
| R-007 | Firmware regression | Medium | Medium | Incremental testing and Git version control |
| R-008 | Hardware damage from wiring mistakes | Low | High | Double-check wiring before power-up |
| R-009 | Integration delays | Medium | Medium | Develop firmware incrementally and test frequently |
| R-010 | Documentation becomes outdated | Medium | Low | Update documentation with every major milestone |

---

# Engineering Philosophy

Every identified risk should have:

- A mitigation strategy
- A verification method
- A documented resolution if encountered

Managing risk is a continuous engineering activity throughout the project lifecycle.

---

# Review Process

The Risk Register will be reviewed:

- Before hardware integration
- Before major firmware milestones
- Before Version 1.0 release

New risks will be added as the project evolves.