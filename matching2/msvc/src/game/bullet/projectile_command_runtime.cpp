// 0x00406D90, equivalent-recovery model: run one batch of a spawned
// projectile's command script.
//
// The record arrives in ECX. Up to eighteen commands are executed per call;
// each command is a 24-byte record whose id selects the scheduler flag, timer,
// velocity or spawn action it performs. A zero id ends the script, a guard
// word of zero stops it once motion flags are set, and the 0x80000000 id just
// advances.
//
// The region covers the code and its two switch tables (1604 bytes); this
// model is verified through the equivalent-recovery layout
// build_support/layout/equivalent/projectile_command_runtime_00406d90.json.
#include <string.h>
#include "th10/game/projectile_spawn_runtime_004067d0.hpp"
#include "th10/game/enemy_grid_scan_004073e0.hpp"
#include "th10/platform/sound_queue.hpp"

// The vanishing activation 0x00408030, whose receiver retail keeps in ESI;
// PlayerCollisionRecord and the manager root data_004776f0 are declared by
// the activate.cpp anchor included at the bottom of this file.

// The point the aim commands fall back to: the player origin, with the point
// supplied in EAX by the co-compiled callee 0x00426660 (the type arrives with
// the angle_from_point.cpp anchor included below).
struct AnimationResource_0043e710;
void __stdcall Entity_StartScript_00404f30(AnimationResource_0043e710* resource,
                                           Entity* entity, int script);

// The command interpreter; the definition closes this translation unit.
struct ProjectileCommandRuntime {
    __declspec(noinline) void Tick();
};

// Whole-program context: the ABI anchors whose bodies the /GL pass needs to
// derive the retail register states at the command interpreter's call sites.
#include "../../../build_support/layout/ltcg/projectile_spawn_runtime/scheduler_set.cpp"
#include "../../../build_support/layout/ltcg/projectile_spawn_runtime/activate.cpp"
#include "../../../build_support/layout/ltcg/projectile_spawn_runtime/angle_from_point.cpp"
#include "../../../build_support/layout/ltcg/projectile_spawn_runtime/queue.cpp"
#include "th10/game/player.hpp"

// Aim angle for the velocity commands: values below -990 keep the slot's
// angle, values below 990 are the angle itself, anything larger aims from the
// record to the player.
__forceinline static float SpawnCommand_AimAngle(ProjectileSpawnRecord& record,
                                                 const float& value) {
    if (value <= data_00470b50)
        return record.angle_3e4;
    if (value >= data_00470ccc)
        return g_player->AngleFromPoint(reinterpret_cast<const float*>(&record.position));
    return value;
}

#pragma code_seg(".text$00406d90_fn")
void ProjectileCommandRuntime::Tick() {
    ProjectileSpawnRecord& record = *reinterpret_cast<ProjectileSpawnRecord*>(this);
    // The 0x210-byte scan request (a ProjectileBlueprint_004067d0) built by
    // command 0x400000; a word buffer, as retail's frame has no /GS cookie.
    // No __declspec(align(8)): explicit over-alignment marks the function for
    // the /GL pass, which then keeps EBX free in every direct callee and the
    // sound queue loses its sound id register (retail's frame is aligned anyway).
    unsigned int pattern_words[132];
    while (record.command_index < 18) {
        const int index = record.command_index;
        SpawnCommandRecord* command = &record.commands[index];
        const unsigned int cmd = (unsigned int)command->command;
        if (cmd == 0)
            return;
        if (command->guard == 0 && record.motion_flags != 0)
            return;
        if (cmd == 0x80000000u) {
            record.command_index = index + 1;
            continue;
        }
        switch ((unsigned int)command->command) {
        case 1:
            record.motion_flags |= 1u;
            record.scheduler_614.SetSchedulerValue(0);
            record.field_638 = 0;
            break;
        case 0x10:
            record.motion_flags |= 0x10u;
            record.field_65c = command->value_a;
            record.field_660 = SpawnCommand_AimAngle(record, command->value_b);
            record.scheduler_648.SetSchedulerValue(0);
            record.field_670 = command->value_c;
            record.polar_664.SetScorePolar(record.field_660, record.field_65c);
            if (record.command_index != 0 && record.field_458 >= 0)
                data_00492590.Queue(record.field_458, 0);
            break;
        case 0x20:
            record.motion_flags |= 0x20u;
            record.field_690 = command->value_a;
            record.field_694 = command->value_b;
            record.scheduler_67c.SetSchedulerValue(0);
            record.field_6a4 = command->value_c;
            if (record.command_index != 0 && record.field_458 >= 0)
                data_00492590.Queue(record.field_458, 0);
            break;
        case 0x40:
        case 0x80:
        case 0x100:
            record.motion_flags |= cmd;
            record.field_6c8 = SpawnCommand_AimAngle(record, command->value_a);
            record.field_6c4 = command->value_b > data_00470cc8
                ? command->value_b : record.fall_speed_3d8;
            if (!(record.timer_6b0.flags & 1u)) {
                record.timer_6b0.flags |= 1u;
                record.timer_6b0.current = 0;
                record.timer_6b0.previous = -999999;
                record.timer_6b0.elapsed = 0.0f;
                record.timer_6b0.speed = &data_00476f78;
            }
            record.timer_6b0.current = 0;
            record.timer_6b0.elapsed = 0.0f;
            record.timer_6b0.previous = -1;
            record.field_6d8 = command->value_c;
            record.field_6dc = command->value_d;
            record.field_6e0 = 0;
            break;
        case 0x400:
        case 0x800:
        case 0x8000000:
            record.motion_flags |= cmd;
            record.field_6f8 = command->value_a;
            record.field_710 = command->value_c;
            record.field_70c = 0;
            break;
        case 0x1000:
            record.countdown = command->value_c;
            break;
        case 0x2000:
            record.bounds_grace = command->value_c;
            record.command_index = index + 1;
            continue;
        case 0x4000:
            Entity_StartScript_00404f30(
                reinterpret_cast<AnimationResource_0043e710*>(
                    reinterpret_cast<ProjectileSpawnManager*>(data_004776f0)->animations),
                &record.sprite,
                data_00474170[command->value_c] + command->value_d);
            break;
        case 0x8000:
            record.motion_flags |= cmd;
            reinterpret_cast<PlayerSchedulerRecord*>(&record.immunity_timer)
                ->SetSchedulerValue(command->value_c);
            break;
        case 0x10000:
            reinterpret_cast<PlayerCollisionRecord*>(this)->Activate();
            break;
        case 0x20000:
            data_00492590.QueuePan(command->value_c, record.position.x);
            break;
        case 0x100000:
            record.motion_flags |= cmd;
            reinterpret_cast<PlayerSchedulerRecord*>(&record.scheduler_74c)
                ->SetSchedulerValue(command->value_c);
            break;
        case 0x200000:
            record.motion_flags |= cmd;
            reinterpret_cast<PlayerSchedulerRecord*>(&record.scheduler_780)
                ->SetSchedulerValue(command->value_c);
            break;
        case 0x400000: {
            // A grid spawn: this record and the next one describe the command->
            memset(pattern_words, 0, sizeof(pattern_words));
            ProjectileBlueprint_004067d0& pattern =
                *reinterpret_cast<ProjectileBlueprint_004067d0*>(pattern_words);
            *reinterpret_cast<Vec3*>(&pattern.field_04) = record.position;
            const unsigned int vanish = command->value_c & 0x80000000u;
            const int word = command->value_c;
            pattern.layout = 0;
            pattern.colour = 0;
            pattern.script_offset = reinterpret_cast<const signed char*>(&command->value_c)[1];
            pattern.command_index = word & 0xFF;
            pattern.columns = (short)command->value_d;
            pattern.y_head = command->value_a;
            pattern.y_tail = command->value_b;
            ++command;
            record.command_index = index + 1;
            pattern.rows = (short)command->value_c;
            pattern.flags = (unsigned int)command->value_d;
            pattern.x_spacing = command->value_b;
            pattern.x_base = command->value_a;
            pattern.field_204 = -1;
            memcpy(pattern.commands, record.commands, sizeof(record.commands));
            EnemyGrid_ScanCells_004073e0(
                reinterpret_cast<ProjectilePattern_004073e0*>(pattern_words),
                reinterpret_cast<ProjectileManager_004073e0*>(data_004776f0));
            ++record.command_index;
            if (vanish == 0)
                continue;
            reinterpret_cast<PlayerCollisionRecord*>(this)->Activate();
            break;
        }
        case 0x1000000:
            record.turn_420 = command->value_c;
            record.command_index = index + 1;
            continue;
        case 0x2000000:
            record.command_index = command->value_c;
            continue;
        case 0x4000000:
            record.motion_flags |= 0x4000000u;
            record.field_7c8 = command->value_a;
            record.field_7cc = command->value_b;
            if (!(record.timer_7b4.flags & 1u)) {
                record.timer_7b4.flags |= 1u;
                record.timer_7b4.current = 0;
                record.timer_7b4.previous = -999999;
                record.timer_7b4.elapsed = 0.0f;
                record.timer_7b4.speed = &data_00476f78;
            }
            record.timer_7b4.current = 0;
            record.timer_7b4.elapsed = 0.0f;
            record.timer_7b4.previous = -1;
            record.field_7dc = command->value_c;
            break;
        }
        ++record.command_index;
    }
}
#pragma code_seg()
