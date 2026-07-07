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

## 💻 Software & Ecosystem

Since a tailless, bird-like design is inherently unstable from an aerodynamic standpoint, the software takes on the role of the biological nervous system:
- **Firmware:** The project relies entirely on **[ArduPilot](https://ardupilot.org/)** (ArduCopter/ArduPlane). 
- **Sensor Fusion as a Stabilizer:** We leverage the ultra-fast **EKF3 (Extended Kalman Filter)** and high-dynamic PID control loops of ArduPilot. The software corrects instabilities hundreds of times per second in real time—exactly how a falcon's brain constantly self-adjusts microscopically against the wind.
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
├── mechanical/            # Local exports of 3D CAD models (STEP, STL)
├── openvsp/               # OpenVSP (.vsp3) models and VLM aero-analysis data
├── simulation/            # Webots worlds and drone models (PROTO files)
├── config/                # ArduPilot parameter files (.param) for tuning
├── docs/                  # Calculations, research papers, and test results
└── README.md              # This file
