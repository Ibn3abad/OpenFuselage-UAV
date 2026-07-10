# OpenFuselage-UAV

This repository contains the development data, 3D models, and simulations for a **groundbreaking, novel drone fuselage and airframe concept**. The goal of this open-source project is to drastically improve the efficiency, flight time, and stability of unmanned aerial vehicles (UAVs) through a revolutionary aerodynamic design.

<img width="704" height="384" alt="ArduPilot" src="https://github.com/user-attachments/assets/744ed0db-a217-4f36-a0a1-4e135fda0ce0" />


---

## 🦅 The Philosophy: Why are we still building aircraft like it's 1900?

For over a century, aviation has followed the exact same blueprint: a heavy fuselage equipped with rigid control surfaces and mechanical tail units (vertical and horizontal stabilizers) at the rear. This architecture was necessary when human pilots had slower reaction times and aircraft required inherent aerodynamic self-stability to remain airborne. 

**OpenFuselage-UAV breaks away from this century-old dogma.** Our vision is to create a bio-inspired airframe that moves through the air just like a **bird**—**completely without traditional tail rudders**. Birds do not have rigid tails; instead, they rely on dynamic geometry adjustments (wing morphing) and highly agile, inherently unstable aerodynamics. Thanks to modern flight controllers and embedded software, we can finally bring this evolutionary perfection to UAVs.

---

## 🚀 The Concept: Aerodynamic Revolution

By eliminating the tail assembly, we drastically reduce both weight and parasitic drag. The system is built upon three main pillars:
- **Fluid Fuselage Design:** Maximizing aerodynamic efficiency by ensuring the entire body contributes positively to the aircraft's lift and performance.
- **Rudderless Stabilization (Tailless Design):** Controlling the pitch and roll axes through combined wing elements (elevons) and, in the long term, flexible wing-warping (morphing wings).
- **Active Software Control Surfaces:** Utilizing differential thrust or thrust-vectoring mechanisms to purely dynamically replace the traditional yaw axis (rudder).

---

## 🐦 Development Roadmap: From Bird-Inspired Control to Full Biomimicry

The control concept of this airframe is being developed in incremental phases, each one moving closer to how a real bird actually flies. Every phase replaces one more "rigid aircraft" convention with a biologically inspired mechanism.

### Phase 1 — Elevator-Only Yaw (Feasibility Phase)
Before committing to any tail geometry, the first phase simply tested whether the airframe could be turned using elevator (pitch) input alone, with no dedicated yaw control surface at all. This was a quick, throwaway feasibility check rather than a real control strategy: it confirmed that the airframe *could* be coaxed into a turn this way, but authority was weak and imprecise, and it was never intended as anything more than a starting point for the phases below.

### Phase 2 — Shallow V-Tail (Ruddervator)
A fixed, shallow V-tail provides pitch control, with limited yaw authority through differential ("ruddervator") deflection of the two tail halves. This is the traditional, aerodynamics-only approach to a tailless-adjacent design — simple to implement, but geometrically limited: yaw effectiveness of a V-tail surface scales roughly with `sin(dihedral angle)`, so a *shallow* V-tail (chosen here for low drag and a bird-like silhouette) inherently has weak yaw authority.

This is implemented in ArduPilot as the `AP_BionicYaw` library's **differential VTail mode** (`BYAW_MODE = 0`, the default) — see [Software & Ecosystem](#-software--ecosystem) below.

### Phase 3 — Rotating Tail Assembly (Mechanical Yaw)
Rather than fighting the shallow V-tail's weak aerodynamic yaw authority, Phase 3 mirrors how a bird actually generates yaw: **a bird rotates its entire tail fan around its body axis** to redirect aerodynamic force, rather than deflecting a single fixed rudder flap.

We replicate this directly: the whole tail assembly is mounted on a dedicated actuator that physically **rotates the tail unit around the fuselage's longitudinal axis**. In the current implementation, this actuator is driven through a dedicated `Scripting` servo output (`SERVOx_FUNCTION = ScriptingN`, selected via the `BYAW_ROT_FN` parameter), rather than ArduPilot's standard `Rudder` output — this lets a single `AP_BionicYaw` library switch between Phase 2's differential mixer and Phase 3's rotator (`BYAW_MODE = 1`) via one parameter, without re-wiring servo function assignments between the two. The flight controller's yaw (rudder stick) demand still drives the rotation; the autopilot doesn't need to know that a rotating assembly, rather than a flap, produces the yawing moment. Pitch remains controlled by both tail halves deflecting **together** as a synchronized elevator.

This decouples pitch and yaw authority mechanically instead of blending them aerodynamically, which is exactly why a shallow, low-drag V-tail becomes viable in the first place.

### Phase 4 — Dynamic Center-of-Gravity Shift (Future Work)
Looking further ahead, birds don't just move their tails — they continuously shift their **body mass distribution** (via wing position, neck extension, and posture) to trim and steer with almost no aerodynamic drag penalty. A shifting center of gravity is one of the most efficient control mechanisms in nature, and historically it's also how the very earliest human gliders (e.g. Otto Lilienthal's weight-shift hang gliders) were controlled.

For a powered fixed-wing UAV, this is intentionally listed as **future work rather than a near-term goal**, because it comes with a fundamental engineering trade-off:

- **Effectiveness scales with `mass × displacement distance`**, not mass alone — on a small UAV, the achievable lever arm is short, so a mass-shift mechanism needs either a heavier shifting mass or a longer travel path to produce a meaningful moment.
- **The mechanism itself adds weight** (rails, motor, shifting mass carrier), which works directly against one of this project's core goals: minimizing weight and drag.
- Unlike control surfaces or a rotating tail, a mass-shift system reacts relatively **slowly**, making it better suited as a **trim/efficiency aid** (e.g. shifting CG slightly rearward in cruise to reduce trim drag) than as a primary, fast-reacting control axis.

The current plan for Phase 4 is therefore a **hybrid approach**: keep the rotating tail (Phase 3) as the primary, fast yaw actuator, and introduce a small, slow CG-shift mechanism purely as a cruise-efficiency trim aid — closer to how a soaring bird subtly repositions its body for efficiency, while still using its tail for active, fast maneuvering.

---

## 💻 Software & Ecosystem

Since a tailless, bird-like design is inherently unstable from an aerodynamic standpoint, the software takes on the role of the biological nervous system:
- **Firmware:** The project relies entirely on **[ArduPilot](https://ardupilot.org/)** (ArduCopter/ArduPlane).
- **Sensor Fusion as a Stabilizer:** We leverage the ultra-fast **EKF3 (Extended Kalman Filter)** and high-dynamic PID control loops of ArduPilot. The software corrects instabilities hundreds of times per second in real time—exactly how a falcon's brain constantly self-adjusts microscopically against the wind.
- **Tail actuation — `AP_BionicYaw`:** Phases 2 and 3 are both implemented in a single custom ArduPilot library, `AP_BionicYaw` (under `ardupilot/libraries/AP_BionicYaw/`), which replaces ArduPlane's standard VTail mixer for the tail servo outputs. Key parameters:
  - `BYAW_ENABLE` — master enable; when disabled, a plain pitch±yaw VTail mix is used instead.
  - `BYAW_MODE` — `0` selects Phase 2's differential VTail mixer, `1` selects Phase 3's rotating-tail actuator.
  - `BYAW_YAW_GAIN`, `BYAW_ROLL_GAIN`, `BYAW_PITCH_GAIN` — mixing gains for Phase 2 (differential VTail), including a turn-coordination roll assist.
  - `BYAW_ROT_MAX`, `BYAW_ROT_FN` — maximum deflection (deg) and target `ScriptingN` servo output for Phase 3's rotating tail actuator.
- **Configurations:** The repository provides custom parameter files (`.param`) tailored specifically to tune ArduPilot for this highly agile airframe behavior.

---

## 🛠️ The Engineering Toolchain (Simulation & Analysis)

To develop an inherently unstable, rudderless aircraft safely and efficiently, we utilize a two-stage digital design process:

### 1. Aerodynamic Validation & Geometry (OpenVSP)
Before writing code or exporting manufacturing files, the airframe is modeled and validated using **NASA's OpenVSP (Vehicle Sketch Pad)**. 
* We use OpenVSP's **Vortex Lattice Method (VLM)** to calculate lift, drag, and stability derivatives.
* This allows us to precisely find the **Neutral Point (Aerodynamic Center)** and optimize the fuselage geometry to ensure the body generates actual lift without relying on a tail.

### 2. Physics & Flight Control Simulation (Webots + ArduPilot SITL)
Once the geometry is verified, the model is brought into **Webots** for real-time dynamic simulation.
* **Webots** calculates aerodynamic and physical forces directly onto body surfaces, making it ideal for testing a tailless design.
* It is seamlessly coupled with **ArduPilot SITL (Software-in-the-Loop)** to virtually flight-test our control loops, tune PID values, and benchmark differential thrust behaviors before any hardware is built.

---

## 📂 Repository Structure & CAD Models

The mechanical CAD development is cloud-based. You can view and inspect the interactive 3D model directly in your browser:
👉 **[View OpenFuselage-UAV on Onshape](https://cad.onshape.com/documents/8b250d0c03d7a3b609c8d7fb/w/4129f33a8aafaadd1a6fb501/e/e16a9e18ad5e6c49e04cec56)**

```text
├── ardupilot/             # ArduPilot changes for this project, incl. the AP_BionicYaw tail-actuation library
├── mechanical/            # Local exports of 3D CAD models (STEP, STL)
├── openvsp/               # OpenVSP (.vsp3) models and VLM aero-analysis data
├── simulation/            # Webots worlds and drone models (PROTO files)
├── config/                # ArduPilot parameter files (.param) for tuning
├── docs/                  # Calculations, research papers, and test results
└── README.md              # This file
```

---

## 📄 License

The ArduPilot-related code in this repository (`ardupilot/`, including `AP_BionicYaw`) is licensed under the **GNU General Public License v3.0 (GPLv3)**, matching ArduPilot's own license, since it is built directly on and distributed alongside ArduPilot source code.
