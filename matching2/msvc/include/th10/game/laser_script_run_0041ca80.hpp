#ifndef TH10_GAME_LASER_SCRIPT_RUN_0041CA80_HPP
#define TH10_GAME_LASER_SCRIPT_RUN_0041CA80_HPP

#include <stddef.h>
#include "th10/game/entity.hpp"
#include "th10/game/player.hpp"

// One scheduler slot of a line laser. The layout is the shared
// PlayerSchedulerRecord shape: `previous` holds the raw value minus one (or
// 0xFFF0BDC1 before the first store), `current` the raw value, `elapsed` the
// value as float and `marker` the 0x476F78 default marker; bit 0 of `flags`
// says the slot has been initialised. The laser keeps one slot every 0x34
// bytes starting at +0x58, with the slot's own state fields living in the
// reserved tail behind the five scheduler words.
struct LaserScriptTimer_0041ca80 {
    int previous;                       // +0x00
    int current;                        // +0x04
    float elapsed;                      // +0x08
    int marker;                         // +0x0C
    unsigned int flags;                 // +0x10

    __forceinline void InitDefaults() {
        current = 0;
        previous = static_cast<int>(0xFFF0BDC1u);
        elapsed = 0.0f;
        marker = 0x476F78;
        flags |= 1u;
    }

    // The scheduler store 0x00405410 inlined: prime the slot on first use and
    // then record the value in all three shapes.
    __forceinline void SetSchedulerValue(int value) {
        if (!(flags & 1u))
            InitDefaults();
        current = value;
        elapsed = static_cast<float>(value);
        previous = value - 1;
    }
};

// One command of the embedded laser script. The four parameter words come
// first, then the opcode and the gate word; the stream starts at +0x450 and
// holds 18 commands, ending exactly where the beam sprite begins.
union LaserScriptValue_0041ca80 {
    int i;
    float f;
    unsigned int u;
};

struct LaserScriptCommand_0041ca80 {
    LaserScriptValue_0041ca80 param0;   // +0x00
    LaserScriptValue_0041ca80 param1;   // +0x04
    LaserScriptValue_0041ca80 param2;   // +0x08
    LaserScriptValue_0041ca80 param3;   // +0x0C
    unsigned int opcode;                // +0x10
    unsigned int gate;                  // +0x14
};

// The polar velocity pair written by the movement command; the setter at
// 0x0041F800 fills it from an angle and a speed.
struct LinePolarVelocity_0041f800 {
    float x;                            // +0x00
    float y;                            // +0x04
    LinePolarVelocity_0041f800* SetPolar(float angle, float speed);
};

// 0x0041CA80: run the embedded command stream of a line laser (virtual slot 0
// of the vtable at 0x0046DA60). Each frame the laser advances its program
// counter through the 18 fixed commands at +0x450; opcodes set scheduler
// flags, aim and launch the beam, start sounds and animations, grow the beam
// width, wait, and jump.
struct LaserScriptRun_0041ca80 {
    __declspec(noinline) void Run();

    unsigned char reserved_000[0xC];
    int state_C;                        // +0x0C laser state
    unsigned char reserved_010[0x24 - 0x10];
    float position_x_24;                // +0x24 beam origin x
    float position_y_28;                // +0x28 beam origin y
    unsigned char reserved_02C[0x3C - 0x2C];
    float angle_3C;                     // +0x3C current beam angle
    unsigned char reserved_040[0x48 - 0x40];
    float width_48;                     // +0x48 current beam width
    unsigned char reserved_04C[0x54 - 0x4C];
    int id_54;                          // +0x54 laser id
    LaserScriptTimer_0041ca80 timer_58; // +0x58 slot 0
    unsigned char reserved_06C[0x7C - 0x6C];
    int duration_7C;                    // +0x7C slot 0 tail
    unsigned char reserved_080[0x8C - 0x80];
    LaserScriptTimer_0041ca80 timer_8C; // +0x8C slot 1
    float speed_A0;                     // +0xA0 beam speed
    float angle_A4;                     // +0xA4 beam angle target
    LinePolarVelocity_0041f800 polar_A8;// +0xA8 polar velocity
    unsigned char reserved_0B0[0xB4 - 0xB0];
    int sound_B4;                       // +0xB4 slot 1 tail
    unsigned char reserved_B8[0xC0 - 0xB8];
    LaserScriptTimer_0041ca80 timer_C0; // +0xC0 slot 2
    float offset_D4;                    // +0xD4 movement target x
    float offset_D8;                    // +0xD8 movement target y
    unsigned char reserved_DC[0xE8 - 0xDC];
    int sound_E8;                       // +0xE8 slot 2 tail
    unsigned char reserved_EC[0xF4 - 0xEC];
    LaserScriptTimer_0041ca80 timer_F4; // +0xF4 slot 3
    float width_108;                    // +0x108 width growth target
    int mode_10C;                       // +0x10C width growth mode
    unsigned char reserved_110[0x11C - 0x110];
    int width_duration_11C;             // +0x11C width growth duration
    int width_duration_120;             // +0x120 width growth duration
    int zero_124;                       // +0x124 always cleared
    unsigned char reserved_128[0x13C - 0x128];
    float target_13C;                   // +0x13C length growth target
    unsigned char reserved_140[0x150 - 0x140];
    int phase_150;                      // +0x150 length growth phase
    int phase_154;                      // +0x154 length growth phase
    unsigned char reserved_158[0x15C - 0x158];
    LaserScriptTimer_0041ca80 timer_15C;// +0x15C slot 5
    unsigned char reserved_170[0x190 - 0x170];
    LaserScriptTimer_0041ca80 timer_190;// +0x190 slot 6
    unsigned char reserved_1A4[0x1C4 - 0x1A4];
    LaserScriptTimer_0041ca80 spare_1C4;// +0x1C4 slot 7
    unsigned char reserved_1D8[0x1F8 - 0x1D8];
    LaserScriptTimer_0041ca80 timer_1F8;// +0x1F8 slot 8
    float move_x_20C;                   // +0x20C movement target x
    float move_y_210;                   // +0x210 movement target y
    unsigned char reserved_214[0x220 - 0x214];
    int move_duration_220;              // +0x220 slot 8 tail
    unsigned char reserved_224[0x400 - 0x224];
    int pc_400;                         // +0x400 program counter
    unsigned int flags_404;             // +0x404 scheduler flags
    unsigned char reserved_408[0x40C - 0x408];
    int sound_id_40C;                   // +0x40C queued sound id
    unsigned char reserved_410[0x450 - 0x410];
    LaserScriptCommand_0041ca80 commands[18]; // +0x450
    Entity beam;                        // +0x600 beam animation object
};

typedef char LaserScriptTimerSize_0041ca80[
    sizeof(LaserScriptTimer_0041ca80) == 0x14 ? 1 : -1];
typedef char LaserScriptCommandSize_0041ca80[
    sizeof(LaserScriptCommand_0041ca80) == 0x18 ? 1 : -1];
typedef char LaserScriptPolarOffset_0041ca80[
    offsetof(LaserScriptRun_0041ca80, polar_A8) == 0xA8 ? 1 : -1];
typedef char LaserScriptTimer15COffset_0041ca80[
    offsetof(LaserScriptRun_0041ca80, timer_15C) == 0x15C ? 1 : -1];
typedef char LaserScriptTimer1F8Offset_0041ca80[
    offsetof(LaserScriptRun_0041ca80, timer_1F8) == 0x1F8 ? 1 : -1];
typedef char LaserScriptPcOffset_0041ca80[
    offsetof(LaserScriptRun_0041ca80, pc_400) == 0x400 ? 1 : -1];
typedef char LaserScriptCommandsOffset_0041ca80[
    offsetof(LaserScriptRun_0041ca80, commands) == 0x450 ? 1 : -1];
typedef char LaserScriptBeamOffset_0041ca80[
    offsetof(LaserScriptRun_0041ca80, beam) == 0x600 ? 1 : -1];

// The player, aimed at by the aim command; the manager holding the beam
// animation resources; and the script index table.
struct BulletAnimationResourceSource {
    unsigned char reserved_000[0x3E0B50];
    void* resource;                    // +0x3E0B50
};
extern "C" BulletAnimationResourceSource* g_bullet_manager;
extern "C" const int data_00474170[];
extern "C" float flt_0, flt_neg990, flt_neg999, flt_990;

#endif
