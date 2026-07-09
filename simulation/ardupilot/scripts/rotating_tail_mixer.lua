-- =============================================================
-- OpenFuselage-UAV Phase 2: Rotating Tail Mixer
-- =============================================================
-- Konzept: Die komplette V-Tail-Einheit rotiert um die Fuselage-
-- Längsachse (0..90 Grad). Ein Rotationsservo dreht die Einheit,
-- zwei weitere Servos steuern die Flächen selbst. Dieses Skript
-- rechnet Pitch/Yaw-Demand abhängig vom aktuellen Rotationswinkel
-- in die korrekten Servo-Ausschläge um.
--
-- WICHTIG: Dies ist experimentell (Phase 2). Vor Realflug
-- ausgiebig in SITL + Webots testen!
-- =============================================================

-- ---------- Konfiguration ----------
local MIXING_GAIN   = 0.5      -- Anteil Yaw-Beimischung (wie MIXING_GAIN bei Standard-VTail)
local TAIL_ROT_CH   = 7        -- RC-Kanal, der den Ziel-Rotationswinkel vorgibt (Aux-Kanal am Sender)
local TAIL_ROT_MIN  = 0        -- Grad, Rotationswinkel bei RC-Wert 1000
local TAIL_ROT_MAX  = 90       -- Grad, Rotationswinkel bei RC-Wert 2000
local UPDATE_HZ     = 50

-- Output-Funktionen (SERVOx_FUNCTION muss entsprechend gesetzt sein)
local FUNC_LEFT   = SRV_Channel.k_scripting1   -- 94: linke Tail-Fläche
local FUNC_RIGHT  = SRV_Channel.k_scripting2   -- 95: rechte Tail-Fläche
local FUNC_ROTATE = SRV_Channel.k_scripting3   -- 96: Rotationsservo der Tail-Einheit

-- ---------- Hilfsfunktionen ----------
local function deg_to_rad(d)
    return d * math.pi / 180.0
end

local function get_tail_angle_deg()
    local rc = rc:get_pwm(TAIL_ROT_CH)
    if rc == nil then
        return TAIL_ROT_MIN
    end
    -- PWM 1000-2000 linear auf TAIL_ROT_MIN..TAIL_ROT_MAX abbilden
    local frac = (rc - 1000) / 1000.0
    if frac < 0 then frac = 0 end
    if frac > 1 then frac = 1 end
    return TAIL_ROT_MIN + frac * (TAIL_ROT_MAX - TAIL_ROT_MIN)
end

-- ---------- Hauptschleife ----------
function update()
    -- 1) Interne Pitch/Yaw-Demand-Werte auslesen
    --    (ArduPilot berechnet diese immer, auch ohne physischen
    --    Elevator/Rudder-Kanal)
    local pitch_demand = SRV_Channels:get_output_scaled(SRV_Channel.k_elevator)
    local yaw_demand   = SRV_Channels:get_output_scaled(SRV_Channel.k_rudder)

    -- 2) Aktuellen Rotationswinkel der Tail-Einheit bestimmen
    local theta_deg = get_tail_angle_deg()
    local theta = deg_to_rad(theta_deg)

    -- 3) Rotationsmatrix anwenden
    local eff_pitch = pitch_demand * math.cos(theta) - yaw_demand * math.sin(theta)
    local eff_yaw   = pitch_demand * math.sin(theta) + yaw_demand * math.cos(theta)

    -- 4) V-Tail-Mischung auf die rotierten Demand-Werte anwenden
    local servo_left  = eff_pitch - eff_yaw * MIXING_GAIN
    local servo_right = eff_pitch + eff_yaw * MIXING_GAIN

    -- 5) Ausgabe auf die Scripting-Servo-Funktionen
    SRV_Channels:set_output_scaled(FUNC_LEFT,  servo_left)
    SRV_Channels:set_output_scaled(FUNC_RIGHT, servo_right)

    -- 6) Rotationsservo ansteuern (Winkel -> Skalierter Output -4500..4500)
    local rotate_scaled = ((theta_deg - TAIL_ROT_MIN) / (TAIL_ROT_MAX - TAIL_ROT_MIN)) * 9000 - 4500
    SRV_Channels:set_output_scaled(FUNC_ROTATE, rotate_scaled)

    return update, 1000 / UPDATE_HZ
end

return update()
