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

#include "AP_BionicYaw.h"

const AP_Param::GroupInfo AP_BionicYaw::var_info[] = {

    // @Param: ENABLE
    // @DisplayName: BionicYaw enable
    // @Description: Enables the BionicYaw differential/turn-coordination tail mixer. When disabled, a plain pitch+/-yaw VTail mix is used instead.
    // @Values: 0:Disabled,1:Enabled
    // @User: Standard
    AP_GROUPINFO_FLAGS("ENABLE", 0, AP_BionicYaw, _enabled, 1, AP_PARAM_FLAG_ENABLE),

    // @Param: YAW_GAIN
    // @DisplayName: BionicYaw yaw mixing gain
    // @Description: Amount of yaw demand mixed differentially into the tail surfaces.
    // @Range: 0.0 1.0
    // @User: Standard
    AP_GROUPINFO("YAW_GAIN", 1, AP_BionicYaw, _yaw_gain, 0.80f),

    // @Param: ROLL_GAIN
    // @DisplayName: BionicYaw roll assist gain
    // @Description: Amount of roll demand mixed differentially into the tail surfaces, for turn coordination (mimicking how birds use asymmetric tail deflection during banked turns).
    // @Range: 0.0 1.0
    // @User: Standard
    AP_GROUPINFO("ROLL_GAIN", 2, AP_BionicYaw, _roll_gain, 0.15f),

    // @Param: PITCH_GAIN
    // @DisplayName: BionicYaw pitch gain
    // @Description: Scaling applied to pitch demand before mixing into the tail surfaces.
    // @Range: 0.5 1.5
    // @User: Standard
    AP_GROUPINFO("PITCH_GAIN", 3, AP_BionicYaw, _pitch_gain, 1.00f),

    AP_GROUPEND
};

void AP_BionicYaw::set_gains(float yaw_gain,
                             float roll_gain,
                             float pitch_gain)
{
    _yaw_gain.set(yaw_gain);
    _roll_gain.set(roll_gain);
    _pitch_gain.set(pitch_gain);
}

AP_BionicYaw::Output AP_BionicYaw::update(float roll,
                                          float pitch,
                                          float yaw)
{
    Output out;

    if (_enabled <= 0) {
        // Fallback auf Standard-Mischung
        out.left = pitch + yaw;
        out.right = pitch - yaw;
        return out;
    }

    const float pitch_cmd = pitch * _pitch_gain;
    const float yaw_cmd   = yaw * _yaw_gain;
    const float roll_cmd  = roll * _roll_gain;

    out.left =
        pitch_cmd +
        yaw_cmd +
        roll_cmd;

    out.right =
        pitch_cmd -
        yaw_cmd -
        roll_cmd;

    out.left  = constrain_float(out.left,  -4500.0f, 4500.0f);
    out.right = constrain_float(out.right, -4500.0f, 4500.0f);

    return out;
}