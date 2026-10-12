#ifndef TH10_GAME_ENEMY_DATA_START_0040DC80_HPP
#define TH10_GAME_ENEMY_DATA_START_0040DC80_HPP
#include "th10/game/enemy_spawn_0040cfb0.hpp"

// The EnemyData fields the start tick touches beyond the shared view.
struct EnemyDataMotion_0040dc80 {
    unsigned char reserved_000[0x38];
    float delta_a[3];                    // +0x38
    unsigned char reserved_044[0x58 - 0x44];
    float base_position[3];              // +0x58
    float base_polar[3];                 // +0x64
    float heading[2];                    // +0x70
    float heading_rate[2];               // +0x78
    unsigned char mode_flags;            // +0x80
    unsigned char reserved_081[3];
    float position_b[3];                 // +0x84
    float polar_b[3];                    // +0x90
    float heading_b[2];                  // +0x9C
    float heading_c[2];                  // +0xA4
    unsigned char reserved_0ac[0xB0 - 0xAC];
    void* pickup_result_a;               // +0xB0
    void* pickup_result_b;               // +0xB8
    unsigned char reserved_0c0[0xC0 - 0xB8];
    void* animation_handles[8];          // +0xC0
    unsigned char reserved_0e0[0xF4 - 0xE0];
    int off_screen_state;                // +0xF4
    int off_screen_previous;             // +0xF8
    unsigned char reserved_0fc[0x11C - 0xFC];
    int wait_last;                       // +0x11C
    int wait_count;                      // +0x120
    float wait_fraction;                 // +0x124
    float* wait_frames;                  // +0x128 (pointer into the script)
    unsigned char reserved_12c[0x180 - 0x12C];
    int base_interp_enabled;             // +0x180
    unsigned char base_interp[8];        // +0x184
    unsigned char reserved_18c[0x1CC - 0x18C];
    int drift_interp_enabled;            // +0x1CC
    unsigned char reserved_1d0[0x1D4 - 0x1D0];
    unsigned char trajectory_a[0x34];    // +0x1D4
    unsigned char reserved_208[8];
    unsigned char trajectory_b[0x34];    // +0x210
    unsigned char reserved_244[8];
    unsigned char trajectory_c[0x34];    // +0x24C
    unsigned char reserved_280[8];
    unsigned char trajectory_d[0x34];    // +0x288
    unsigned char reserved_2bc[8];
    unsigned char trajectory_e[0x34];    // +0x2BC
    unsigned char reserved_2f0[0x13A4 - 0x2F0];
    float scroll_scale_x;                // +0x13A4
    float scroll_scale_y;                // +0x13A8
    float clamp_x;                       // +0x13AC
    float clamp_y;                       // +0x13B0
    float clamp_rate_x;                  // +0x13B4
    float clamp_rate_y;                  // +0x13B8
    unsigned char reserved_13bc[0x1414 - 0x13BC];
    int blink_countdown;                 // +0x1414
    unsigned char reserved_1418[0x141C - 0x1418];
    unsigned char reserved_1430[0x1430 - 0x1418 - 8];
    float blink_timer;                   // +0x1430 (FrameTimer view)
    unsigned char reserved_1434[0x1444 - 0x1434];
    int script_change_a;                 // +0x1448
    int script_change_b;                 // +0x144C
    unsigned char reserved_1450[0x14D8 - 0x1450];
    void* script_vm;                     // +0x14D8
};

// 0x0040DC80: run the enemy's script up to its first wait. Nonzero when
// the enemy finished (released or a script error).
extern "C" __declspec(noinline) int __stdcall EnemyDataStart_0040dc80(
    EnemyData_0040cfb0* enemy);
#endif
