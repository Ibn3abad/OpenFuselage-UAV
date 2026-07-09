#pragma once

/*
   BionicYaw
   Biomimetic tail mixer for ArduPilot

   Copyright (C) 2026 Your Name

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#include <AP_Math/AP_Math.h>
#include <AP_Param/AP_Param.h>

class AP_BionicYaw
{
public:

    struct Output
    {
        float left;
        float right;
    };

    AP_BionicYaw() = default;

    // AP_Param group info, registered as a subgroup in Plane's
    // Parameters2 (g2) table so gains show up as BYAW_YAW_GAIN,
    // BYAW_ROLL_GAIN, BYAW_PITCH_GAIN in the GCS.
    static const struct AP_Param::GroupInfo var_info[];

    void set_gains(float yaw_gain,
                   float roll_gain,
                   float pitch_gain = 1.0f);

    // roll/pitch/yaw are expected in centidegrees (ArduPilot's
    // standard SRV_Channels::get_output_scaled() range, -4500..4500),
    // matching k_aileron/k_elevator/k_rudder scaling.
    Output update(float roll,
                  float pitch,
                  float yaw);

private:

    AP_Float _yaw_gain;
    AP_Float _roll_gain;
    AP_Float _pitch_gain;
};
