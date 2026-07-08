# ArduPilot Development Setup

This guide explains how to set up a local **ArduPilot** development environment and run your first **Software-in-the-Loop (SITL)** simulation for a tailless/flying-wing aircraft.

## Prerequisites

* Ubuntu or WSL2 (recommended)
* Git
* Internet connection to download dependencies

---

# 1. Fork and Clone the Repository

First, fork the official ArduPilot repository on GitHub, then clone your fork together with all required submodules.

```bash
git clone --recurse-submodules https://github.com/ArduPilot/ardupilot.git
cd ardupilot
```

> **Important**
>
> ArduPilot depends on multiple Git submodules. If you forgot to clone them, initialize them afterwards:

```bash
git submodule update --init --recursive
```

---

# 2. Install the Development Environment

On Ubuntu (or WSL), install the complete development toolchain using:

```bash
Tools/environment_install/install-prereqs-ubuntu.sh -y
. ~/.profile
```

This installs everything required for development, including:

* GCC ARM toolchain
* Python dependencies
* Waf build system
* Additional development tools

---

# 3. Build SITL

Configure ArduPilot for **Software-in-the-Loop (SITL)**.

```bash
./waf configure --board sitl
```

Then build **ArduPlane**:

```bash
./waf plane
```

## Why ArduPlane?

For a **tailless** or **flying-wing** aircraft, **ArduPlane** is the appropriate vehicle type.


---

# 4. Start the Simulator

Launch the SITL simulator:

```bash
Tools/autotest/sim_vehicle.py -v ArduPlane --console --map
```

This starts:

* ArduPlane SITL
* MAVProxy console
* Interactive map

---

# 5. Configure the Aircraft

For an elevon-based flying wing, you can start with the following parameters:

```text
param set SERVO1_FUNCTION 77
param set SERVO2_FUNCTION 78
param set MIXING_GAIN 0.5
param set RUDD_DT_GAIN 100
```

## Parameter Overview

| Parameter              | Description                                             |
| ---------------------- | ------------------------------------------------------- |
| `SERVO1_FUNCTION = 77` | Left elevon                                             |
| `SERVO2_FUNCTION = 78` | Right elevon                                            |
| `MIXING_GAIN = 0.5`    | Elevon mixing gain                                      |
| `RUDD_DT_GAIN = 100`   | Differential thrust for yaw control instead of a rudder |

Once your own parameter files are available, they can be loaded directly:

```text
param load your_aircraft.param
```

---

# 6. Connect to Webots

After confirming that the SITL environment is working correctly, the next step is integrating **Webots**.

ArduPilot already provides built-in support for external simulators using:

* `SIM_JSON`
* Example integrations located in `libraries/SITL/`

At this stage, OpenFuselage aircraft model—including aerodynamics, propulsion, sensors, and other dynamics—can be connected to the ArduPilot flight controller.

> **Recommendation:** Complete Steps 1–5 before beginning the Webots integration.

---

# Development Workflow

```text
Fork Repository
      │
      ▼
Clone Repository
      │
      ▼
Install Development Tools
      │
      ▼
Build ArduPlane SITL
      │
      ▼
Launch Simulator
      │
      ▼
Configure Elevons
      │
      ▼
Load Parameter File
      │
      ▼
Connect Webots
      │
      ▼
Flight Testing
```

---

# Next Steps

After successfully setting up the environment, we will continue with:

* Integrating aircraft model
* Webots simulation
* Creating custom `.param` files
* Differential thrust tuning
* Aerodynamic optimization
* Connecting a Pixhawk flight controller
* Performing real-world flight tests
