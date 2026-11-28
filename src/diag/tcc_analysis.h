#ifndef TCC_ANALYSIS_H
#define TCC_ANALYSIS_H

#include <cstdint>

enum class TccFillStage : uint8_t {
    Inactive = 0,
    Pulse = 1,
    Ramp = 2,
    Hold = 3,
    Handoff = 4,
};

enum class TccFillExitReason : uint8_t {
    None = 0,
    TorqueDetected = 1,
    HoldElapsed = 2,
    OpenCondition = 3,
    ShiftStarted = 4,
    SlipTarget = 5,
    ControlUnavailable = 6,
};

// RLI 0x2D, version 1. Integers are little endian on the ESP32.
struct __attribute__((packed)) TccAnalysisSnapshot {
    uint32_t tcu_time_ms = 0;
    uint16_t slip_rpm = UINT16_MAX;
    uint16_t slip_target_rpm = UINT16_MAX;
    uint16_t commanded_pressure_mbar = 0;
    uint16_t map_pressure_mbar = 0;
    int16_t pi_pressure_mbar = 0;
    uint16_t pwm_raw = 0;
    uint16_t coil_current_ma = 0;
    uint16_t engine_rpm = 0;
    uint16_t turbine_rpm = 0;
    uint16_t output_rpm = 0;
    int16_t engine_torque_nm = 0;
    int16_t input_torque_nm = 0;
    int16_t driver_torque_nm = 0;
    int16_t atf_temperature_c = 0;
    int16_t load_percent = 0;
    int16_t pedal_rate_pct_per_second = 0;
    uint16_t estimated_clutch_torque_nm = UINT16_MAX;
    uint8_t version = 1;
    uint8_t pedal_raw = UINT8_MAX; // 0–250 equals 0–100%.
    uint8_t target_actual_gear = 0x88;
    uint8_t current_state = 0;
    uint8_t target_state = 0;
    uint8_t adaptation_holdoff_ticks = 0;
    uint8_t pi_holdoff_ticks = 0;
    TccFillStage fill_stage = TccFillStage::Inactive;
    uint8_t fill_timer_ticks = 0;
    TccFillExitReason fill_exit_reason = TccFillExitReason::None; // Retained until the next fill starts.
    uint8_t controller_updated = 0;
};
static_assert(sizeof(TccAnalysisSnapshot) == 49);

#endif // TCC_ANALYSIS_H
