// 0x0040DC80..0x0040E5EB: the enemy start tick. The enemy arrives on the
// stack; every motion subsystem advances, the script interpreter runs to
// its first wait, and the item/blink bookkeeping follows.
//
// Equivalent recovery: the ECL VM callees keep their private register
// conventions through the ecl_tick_children cluster context; the motion
// helpers are the recovered members.
//
// Structure (per reference/recovery_notes/enemy_data_start_0040dc80_decode
// _2026_10_12.md): the 11-dword snapshot, four trajectory steps, the two
// polar/vector motions with their scroll and clamp paths, the off-screen
// test, the script change, the interpreter tick, the pickup sweep and
// score, the spell-timer advance, the field contact, the off-screen state
// machine, the animation positioning, the blink counter and the wait
// bookkeeping.
#include "th10/game/enemy_data_start_0040dc80.hpp"
#include "th10/game/polar_motion.hpp"
#include "th10/math/trajectory_vector.hpp"
#include "th10/render/animation_script_change.hpp"
#include "th10/game/recovery_script_executor_0040bd80.hpp"
#include "th10/script/ecl_children.hpp"

extern "C" {
extern void* data_004776e0;              // the game thread (cursor resource)
extern void* data_00477834;              // the player state
extern void* data_004776f4;              // the play-mode flags
extern void* data_0047770c;              // the result overlay state
extern void* data_00474c50;              // the enemy-drop marker
extern unsigned int data_00474e36;       // the input mask
extern float data_00470b0c;              // the clamp scale
// The off-screen bounds: read through the recovery-named homes so the
// CIL module cannot pool private copies.
extern "C" float bounds_high_x_00470b40;
extern "C" float bounds_low_x_00470b3c;
extern "C" float bounds_high_y_00470b04;
extern "C" float bounds_low_y_00470b38;
extern float data_00470d30, data_00470c18;
extern float data_00470b68, data_00470b64, data_00470afc;
extern float data_00491e6c, data_00491e70, data_00491e74;  // scroll drift
extern void* data_00477810;              // the front-end game state
extern unsigned int data_00491ff4;
extern unsigned int enemy_dropped_marker_00474c50;
}

// The trajectory interpolator step (0x00412AC0) and the Vec3 one
// (0x00404610); the angle normalizer (0x0044BC70).
struct TrajectoryVec2Step {
    __declspec(noinline) TrajectoryVec2 Step();
};
struct Vec3 { float x, y, z; };
struct Vec3Step {
    __declspec(noinline) Vec3* Step();
};
extern "C" float __stdcall Angle_Normalize_0044bc70(float value);

// The polar setter (0x0044C5D0, thiscall) and PolarMotion::Advance
// (0x0044C2A0): the recovered members the two motions call.
struct RecoveryPolarVector {
    float x, y;
    __declspec(noinline) RecoveryPolarVector* SetPolar(float angle, float radius);
};
struct PolarMotionAdv {
    void Advance();
};

// 0x0042A3D0/0x0042A3E0/0x0042A430 are the scheduler callbacks; the node
// initialization writes them directly.

// The spell timer, ECL record and script table views.
struct SpellTimerState_004127a0 {
    void* AdvanceSlots();
};
struct EclRecord_0040c730 {
    void Reset();
};
struct ScriptVm_00450560;
struct ScriptTable_00450470 {
    int Resolve(const char* name);
};

struct ScriptFrame_00450560 {
    int instruction;
    int time;
};
struct ScriptVm_00450560 {
    ScriptTable_00450470* table;
    ScriptFrame_00450560* current;
    char name[0x100];                    // +0x08: the entry being run
};

// 0x0042AB20: free the stage pools (runtime in ECX, stage in EAX).
extern "C" void __fastcall ReplayPool_Release_0042ab20(void* runtime, int stage);
// 0x0042AA50: append a pool page (runtime in ECX).
extern "C" void* __fastcall ReplayPool_Append_0042aa50(void* runtime);
// 0x00418C40: the config defaults (this in ECX).
extern "C" void __fastcall GameConfig_Defaults_00418c40(void* config);
// 0x00418B80: add score.
extern "C" void __fastcall ScoreState_Add_00418b80(unsigned* state, int amount);
// 0x0042A930: restore the score gauge.
extern "C" void __fastcall ScoreGauge_Restore_0042a930(unsigned* state, int value);
// 0x00450700: bind the named subroutine.
extern "C" int __fastcall BindName_00450700(const char* name, ScriptVm_00450560* vm);
// 0x00452422, 0x004524A1: the frees.
extern "C" void __cdecl free_00452422(void* memory);
extern "C" void __cdecl free_004524a1(void* memory);
// 0x0043DD10: queue a panned sound; 0x0043DC90: the plain queue.
struct SoundQueue_0043dd10 {
    void QueuePan(int sound, float pan);
};
// 0x0044FD10: the ECL child tick (owner in EDI, delta on the stack).
extern "C" __declspec(noinline) int __stdcall
EclVm_TickChildren(EclChildOwner* owner, float delta);
// 0x0044BE70/0x0044BEA0: the menu cursor helpers.
// 0x00409E50: stop the animation tree a handle refers to.
extern "C" void __stdcall RecoveryMusicStopHandle_00409e50(void* handle);
// 0x004496D0: the script change handle.
// 0x00449350/0x004492F0: the animation position setters.
extern "C" void __fastcall SetAnimationTranslatedPosition_00449350(
    const void* positions, void* entity);
extern "C" void __fastcall MovementSetPosition_004492f0(
    const void* positions, void* entity);
// 0x004491C0: find a running animation by handle.
extern "C" void* __fastcall AnimationManager_Find_004491c0(
    void* manager, unsigned handle);
// 0x004266B0: the field contact.
extern "C" void __stdcall FieldContact_004266b0(
    void* player, void* result, void* position);
// 0x00428630: the pickup sweep.
struct PickupSweepResult_00428630 {
    int value;
    int Sweep(void* manager, const void* center, const void* size);
};
// 0x00409D90: the score bookkeeping (state in ECX, amount on the stack).
// 0x0040E5F0: release the enemy on death.
extern "C" int __stdcall Enemy_ReleaseOnDeath_0040e5f0(void* enemy);
// 0x0040C6E0/0x0040C730: the resource list and the ECL record.
extern "C" void __stdcall BulletEntity_ClearResourceList_0040c6e0(void* entity);
extern "C" void __stdcall EclRecord_Reset_0040c730(void* record);
// 0x0042C5C0/0x0042C620/0x0042C670/0x0042C6D0/0x0042C770: the manager
// helpers (the timer, the animation slots).
extern "C" void __stdcall GameState_DisableTimerWithOwner_0042c5c0(
    void* state, int owner);

namespace {

// One scheduler node, initialized the way retail writes it and registered
// with the recovered helpers.
struct Scheduler_0040dc80 {
    void* primary;
    void* secondary;
};

}

#pragma code_seg(".text$0040dc80_fn")
extern "C" __declspec(noinline) int __stdcall EnemyDataStart_0040dc80(
    EnemyData_0040cfb0* enemy) {
    EnemyDataMotion_0040dc80* m = reinterpret_cast<EnemyDataMotion_0040dc80*>(enemy);
    EnemyFlags_0040cfb0& flags = enemy->flags;
    unsigned int raw_flags = *reinterpret_cast<unsigned int*>(&flags);

    if (raw_flags & 0x400) {
        *reinterpret_cast<unsigned int*>(&flags) = raw_flags & ~0x400u;
        return 0;
    }
    *reinterpret_cast<unsigned int*>(&flags) = raw_flags | 0x400u;

    // The position snapshot.
    {
        unsigned int* source = reinterpret_cast<unsigned int*>(enemy) + 11;
        unsigned int* target = reinterpret_cast<unsigned int*>(enemy);
        for (int words = 11; words != 0; --words) *target++ = *source++;
    }
    // The four trajectory steps with the angle normalizer.
    if (*reinterpret_cast<unsigned int*>(m->trajectory_a) != 0) {
        TrajectoryVec2Step* step = reinterpret_cast<TrajectoryVec2Step*>(m->trajectory_a + 4);
        TrajectoryVec2 value = step->Step();
        m->heading[0] = Angle_Normalize_0044bc70(value.x);
        m->heading[1] = value.y;
    }
    if (*reinterpret_cast<unsigned int*>(m->trajectory_c) != 0) {
        TrajectoryVec2Step* step = reinterpret_cast<TrajectoryVec2Step*>(m->trajectory_c + 4);
        TrajectoryVec2 value = step->Step();
        m->heading_rate[0] = value.x;
        m->heading_rate[1] = value.y;
    }
    if (*reinterpret_cast<unsigned int*>(m->trajectory_b) != 0) {
        TrajectoryVec2Step* step = reinterpret_cast<TrajectoryVec2Step*>(m->trajectory_b + 4);
        TrajectoryVec2 value = step->Step();
        enemy->reserved_0064[0] = 0;     // the angle home pair
        m->heading_b[0] = Angle_Normalize_0044bc70(value.x);
    }
    if (*reinterpret_cast<unsigned int*>(m->trajectory_d) != 0) {
        TrajectoryVec2Step* step = reinterpret_cast<TrajectoryVec2Step*>(m->trajectory_d + 4);
        TrajectoryVec2 value = step->Step();
        m->heading_c[0] = value.x;
        m->heading_c[1] = value.y;
    }
    // The base position: the Vec3 interpolator or the polar pair.
    if (m->base_interp_enabled != 0) {
        Vec3Step* step = reinterpret_cast<Vec3Step*>(m->base_interp + 4);
        Vec3* value = step->Step();
        m->delta_a[0] = value->x - m->base_position[0];
        m->delta_a[1] = value->y - m->base_position[1];
        m->delta_a[2] = value->z - m->base_position[2];
    } else if (!(m->mode_flags & 1)) {
        // SetPolar(angle at +0x70, radius at +0x74) on the base polar at
        // +0x64; the z home is cleared.
        reinterpret_cast<RecoveryPolarVector*>(m->base_polar)->SetPolar(
            m->heading[0], m->heading[1]);
        m->base_polar[2] = 0.0f;
    } else {
        // The orbit path: the heading accumulates the rate and the speed
        // angle is renormalized.
        m->heading_rate[0] += m->heading_rate[1];
        m->heading[1] = Angle_Normalize_0044bc70(
            m->heading[1] + m->heading[0]);
    }
    // The drift position: the same treatment plus the scroll.
    if (m->drift_interp_enabled != 0) {
        Vec3Step* step = reinterpret_cast<Vec3Step*>(m->base_interp + 4);
        Vec3* value = step->Step();
        m->position_b[0] = value->x - m->base_position[0];
        m->position_b[1] = value->y - m->base_position[1];
        m->position_b[2] = value->z - m->base_position[2];
    } else if (!(m->mode_flags & 1)) {
        // The drift polar at +0x90 with the angle/radius pair at
        // +0x9C/+0xA0; the +0xA4 home cleared.
        reinterpret_cast<RecoveryPolarVector*>(m->polar_b)->SetPolar(
            m->heading_b[0], m->heading_b[1]);
        m->polar_b[2] = 0.0f;
    } else {
        m->heading_b[1] += m->heading_c[0];
        m->heading_b[0] = Angle_Normalize_0044bc70(
            m->heading_b[0] + m->heading_c[1]);
    }
    // PolarMotion::Advance on the base home, the scroll offset on the
    // drift position, Advance on the drift home, then the field delta.
    m->base_position[0] += m->base_polar[0];
    m->base_position[1] += m->base_polar[1];
    m->base_position[2] += m->base_polar[2];
    if (raw_flags & 0x40000) {
        m->position_b[0] += data_00491e6c;
        m->position_b[1] += data_00491e70;
        m->position_b[2] += data_00491e74;
    }
    m->position_b[0] += m->base_position[0];
    m->position_b[1] += m->base_position[1];
    m->position_b[2] += m->base_position[2];
    m->delta_a[0] = m->position_b[0] - reinterpret_cast<float*>(enemy)[11];
    m->delta_a[1] = m->position_b[1] - reinterpret_cast<float*>(enemy)[12];
    m->delta_a[2] = m->position_b[2] - reinterpret_cast<float*>(enemy)[13];
    // The clamp path (flag 0x200): pull the drift x into
    // [0x13AC ± 0x13B4·scale] and the drift y into [0x13B0 ± 0x13B8·scale]
    // when the enemy moves relative to the scroll origin; the base
    // position recomputes from the clamped drift.
    if (raw_flags & 0x200) {
        float reach = m->clamp_rate_x * data_00470b0c;
        float low = m->clamp_x - reach;
        float high = m->clamp_x + reach;
        if (m->position_b[0] < low || m->position_b[0] > high)
            m->position_b[0] = (m->position_b[0] < low) ? low : high;
        else
            m->position_b[0] = m->clamp_x;
        reach = m->clamp_rate_y * data_00470b0c;
        low = m->clamp_y - reach;
        high = m->clamp_y + reach;
        if (m->position_b[1] < low || m->position_b[1] > high)
            m->position_b[1] = (m->position_b[1] < low) ? low : high;
        else
            m->position_b[1] = m->clamp_y;
        m->base_position[0] = m->position_b[0] - m->delta_a[0];
        m->base_position[1] = m->position_b[1] - m->delta_a[1];
        m->base_position[2] = m->position_b[2] - m->delta_a[2];
    }
    // The off-screen despawn test.
    {
        float x = m->position_b[0] + m->clamp_x * data_00470b0c;
        float y = m->position_b[1] + m->clamp_y * data_00470b0c;
        if (x < bounds_low_x_00470b3c || x > bounds_high_x_00470b40
                || y < bounds_low_y_00470b38 || y > bounds_high_y_00470b04) {
            if (!(raw_flags & 0x200))
                *reinterpret_cast<unsigned int*>(&flags) |= 0x100u;
        }
    }
    // The script change (0x100000) and the device-lost reset (0x200000).
    if (raw_flags & 0x100000) {
        void** outer = static_cast<void**>(data_004776e0);
        if (outer[5] != 0) {
            if (!(raw_flags & 0x200000)) {
                m->off_screen_state = m->script_change_a;
                ScriptChangeHandle handle;
                *reinterpret_cast<RecoveryScriptId_0040bd80*>(&handle) =
                    *reinterpret_cast<RecoveryScriptId_0040bd80*>(&m->animation_handles[0]);
                handle.ChangeScript(m->script_change_a);
                *reinterpret_cast<unsigned int*>(&flags) |= 0x200001u;
            }
        } else if (m->script_change_b != 0) {
            m->off_screen_state = m->script_change_b;
            ScriptChangeHandle handle;
            *reinterpret_cast<RecoveryScriptId_0040bd80*>(&handle) =
                *reinterpret_cast<RecoveryScriptId_0040bd80*>(&m->animation_handles[0]);
            handle.ChangeScript(m->script_change_b);
            *reinterpret_cast<unsigned int*>(&flags) &= ~0x200001u;
        }
    }
    // The interpreter tick; nonzero ends the enemy with an error.
    if (EclVm_TickChildren(static_cast<EclChildOwner*>(m->script_vm),
                           *m->wait_frames) != 0)
        return -1;
    *reinterpret_cast<unsigned int*>(&flags) &= ~0x200u;
    if ((raw_flags & 0x11) == 0) {
        // The item drop: sweep, divide by five, the score bookkeeping.
        int dropped = reinterpret_cast<PickupSweepResult_00428630*>(
            &m->pickup_result_a)->Sweep(data_00477834, 0, 0);
        if (dropped != 0) {
            dropped /= 5;
            unsigned char* game_thread =
                static_cast<unsigned char*>(data_004776f4);
            if (game_thread[0x378C] & 1) {
                if (static_cast<int>(*reinterpret_cast<unsigned int*>(&flags)) >= 0) {
                    if (dropped <= 0) dropped = 1;
                }
            }
            // +0x1420 is the invulnerable timer's current frame: the
            // score only drains while it is not running.
            if (!(raw_flags & 8) && enemy->invulnerable_timer.current <= 0)
                enemy->score -= dropped;
            enemy_dropped_marker_00474c50 = 1;
            ScoreState_Add_00418b80(reinterpret_cast<unsigned*>(&data_00474c40), enemy->life);
            if (Enemy_ReleaseOnDeath_0040e5f0(enemy) != 0)
                return 1;
            *reinterpret_cast<unsigned int*>(&flags) |= 0x2000u;
        }
        if (!(m->mode_flags & 0x12) && enemy->death_effect <= 0)
            FieldContact_004266b0(data_00477834, &m->pickup_result_b,
                                  &enemy->position);
    }
    // The spell timer advance.
    {
        SpellTimerState_004127a0* timer = static_cast<SpellTimerState_004127a0*>(
            m->script_vm);
        void* slot = timer->AdvanceSlots();
        if (slot != 0) {
            BulletEntity_ClearResourceList_0040c6e0(enemy);
            EclRecord_Reset_0040c730(enemy);
            // Rebind the script entry: resolve the name the VM owns and
            // store it into the current frame (retail 0x0040E2A2).
            {
                ScriptVm_00450560* vm =
                    static_cast<ScriptVm_00450560*>(m->script_vm);
                ScriptTable_00450470* table = vm->table;
                int resolved = table->Resolve(vm->name);
                vm->current->instruction = resolved;
                vm->current->time = 0;
            }
            if (EclVm_TickChildren(static_cast<EclChildOwner*>(m->script_vm),
                                   *m->wait_frames) != 0)
                return -1;
        }
    }
    // The field contact for the non-item path.
    if (!(raw_flags & 0x12) && enemy->death_effect <= 0)
        FieldContact_004266b0(data_00477834, &m->pickup_result_b, &enemy->position);
    // The off-screen state machine.
    if (raw_flags & 0x1000) {
        int state;
        float x = m->delta_a[0];
        if (x < data_00470d30) state = -1;
        else if (x > data_00470c18) state = 1;
        else state = 0;
        if (m->off_screen_previous != state) {
            int step;
            if (m->off_screen_previous == -1)
                step = (state != -1) ? 3 : 2;
            else if (m->off_screen_previous == 0)
                step = (state == -1) ? 1 : 2;
            else
                step = (state != 1) ? 4 : 1;
            m->off_screen_previous = state;
            ScriptChangeHandle handle;
            *reinterpret_cast<RecoveryScriptId_0040bd80*>(&handle) =
                *reinterpret_cast<RecoveryScriptId_0040bd80*>(&m->animation_handles[0]);
            handle.ChangeScript(m->script_change_a + step);
        }
    }
    // The eight animation positions.
    {
        void** handles = m->animation_handles;
        for (int index = 8; index != 0; --index, ++handles) {
            if (raw_flags & 0x40000)
                MovementSetPosition_004492f0(
                    reinterpret_cast<const void*>(&enemy->position), *handles);
            else
                SetAnimationTranslatedPosition_00449350(
                    reinterpret_cast<const void*>(&enemy->position), *handles);
        }
    }
    // The blink counter and the highlight sound.
    if (*reinterpret_cast<int*>(&enemy->death_callback) == 0) {
        void* object = AnimationManager_Find_004491c0(reinterpret_cast<void*>(data_00491c10),
            *reinterpret_cast<unsigned*>(&m->animation_handles[0]));
        if (object == 0)
            m->animation_handles[0] = 0;
        if (raw_flags & 0x2000) {
            // The invulnerable highlight: color + flags + the countdown.
            m->blink_countdown = 4;
            if (raw_flags & 0x8000) {
                SoundQueue_0043dd10* queue = reinterpret_cast<SoundQueue_0043dd10*>(0x492590);
                queue->QueuePan(0x23, 0.0f);
            }
        }
    } else {
        m->blink_countdown -= 1;
    }
    // The wait bookkeeping: the fractional and integer frame counts.
    {
        float frames = *m->wait_frames;
        if (frames >= data_00470b68 && frames <= data_00470b64) {
            m->wait_fraction += data_00470afc;
            m->wait_count += 1;
        } else {
            m->wait_fraction += frames;
            m->wait_count = static_cast<int>(m->wait_fraction);
        }
        m->wait_last = m->wait_count;
    }
    return 0;
}
#pragma code_seg()
