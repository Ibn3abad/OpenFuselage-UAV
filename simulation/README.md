
# OpenFuselage-UAV — Control Mixing Concept

## Airframe Overview

This airframe uses **ailerons** for roll and a **shallow V-tail** for pitch control. Unlike a conventional fixed-wing aircraft, there is **no dedicated rudder surface**. Instead, yaw authority is provided by a **rotating tail actuator** that physically rotates the entire tail assembly around the fuselage's longitudinal axis.

This document explains the control surface mapping and the reasoning behind it, for use with ArduPlane firmware.

## Why Not Standard V-Tail Mixing?

ArduPlane natively supports V-tail aircraft through the `VTail Left` / `VTail Right` servo functions (79/80), which mix pitch and yaw demand into two asymmetric control surfaces (a "ruddervator"). That approach works well for a conventional V-tail, but it has a geometric limitation:

> Yaw effectiveness of a V-tail surface scales roughly with `sin(dihedral angle)`, while pitch effectiveness scales with `cos(dihedral angle)`. A **shallow** V-tail (small dihedral angle) therefore has strong pitch authority but very weak yaw authority from the same control deflection — a limit that cannot be compensated in software.

To solve this without relying on a shallow V-tail's weak yaw authority, this design separates the two axes mechanically instead of mixing them aerodynamically:

- **Pitch** — both tail surfaces move **together** (synchronized), acting as a plain elevator.
- **Yaw** — a **separate actuator physically rotates the whole tail assembly**, replacing the aerodynamic function of a rudder with a mechanical one.

## Control Surface Mapping

| Axis | Control Surface | ArduPlane Servo Function | Function # |
|---|---|---|---|
| Roll | Left aileron | Aileron | 4 |
| Roll | Right aileron | Aileron (reversed) | 4 |
| Pitch | Left tail half | Elevator | 19 |
| Pitch | Right tail half | Elevator (synced, same direction) | 19 |
| Yaw | Tail rotation actuator | Rudder | 21 |
| Throttle | Motor | Throttle | 3 |

Because ArduPlane always computes an internal pitch demand and yaw demand regardless of which physical channels are assigned, this mapping lets the autopilot control the airframe exactly as it would a conventional aircraft with a real rudder — the only difference is mechanical (rotating the tail unit instead of deflecting a flap), which is transparent to the flight control software.

## Key Parameters

```
SERVO1_FUNCTION,4      # Left aileron
SERVO5_FUNCTION,4      # Right aileron (reversed)

SERVO2_FUNCTION,19     # Left tail half (elevator)
SERVO4_FUNCTION,19     # Right tail half (elevator, synced)

SERVO6_FUNCTION,21     # Tail rotation actuator (rudder replacement)

SERVO3_FUNCTION,3      # Throttle

KFF_RDDRMIX,1          # Rudder-to-aileron mixing for coordinated turns
                        # (works normally since real yaw authority exists)
```

**Do not** assign `SERVO_FUNCTION = 79/80` (VTail Left/Right) to the tail surfaces in this configuration — that would introduce an aerodynamic pitch/yaw mixing that this airframe does not need, since yaw is handled mechanically by the rotation actuator instead.

## Testing in SITL

1. Load the parameter file into ArduPlane SITL (Mission Planner → Full Parameter List → Load from file, or `param load <file>.parm` in MAVProxy).
2. Verify axis separation:
   - Command pure pitch (`rc 2 <value>`) → both tail-half servos (SERVO2/SERVO4) should move **synchronously**; the rotation actuator (SERVO6) should stay still.
   - Command pure yaw (`rc 4 <value>`) → only the rotation actuator (SERVO6) should move; the tail halves should stay still.
3. If the two tail-half servos move in opposite directions instead of together, flip `SERVO4_REVERSED` (0 ↔ 1) depending on your physical servo/linkage orientation.
4. If the rotation actuator moves in the wrong direction, flip `SERVO6_REVERSED`.

> Note: ArduPlane's built-in SITL physics model does not simulate the aerodynamics of a physically rotating tail assembly. SITL testing at this stage only validates the **control logic and servo mapping**, not real aerodynamic behavior. For aerodynamic validation of the rotating-tail mechanism itself, a custom physics model (e.g. via Webots, coupled to ArduPilot SITL through the JSON backend) is required.

## Mechanical Considerations

- If the rotation actuator has a limited mechanical range (e.g. ±45° instead of full servo travel), set `SERVO6_MIN` / `SERVO6_MAX` to match the actual physical limits so the software scaling lines up with real travel.
- `ARMING_CHECK,0` in the test parameter file is intended for SITL testing only and must be re-enabled before any real flight.

## Project Phases

- **Phase 1** — Fixed shallow V-tail with standard ruddervator mixing (elevator + limited yaw via differential V-tail deflection).
- **Phase 2** (this document) — Rotating tail assembly, with yaw handled by mechanical rotation of the whole tail unit rather than aerodynamic mixing, addressing the shallow V-tail's limited yaw authority.
