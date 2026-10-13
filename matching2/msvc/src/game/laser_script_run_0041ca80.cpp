// 0x0041CA80: run the embedded command stream of a line laser (virtual slot 0
// of the vtable at 0x0046DA60). The stream holds 18 fixed 24-byte commands at
// +0x450, walked by the program counter at +0x400. Each frame one command is
// dispatched: opcode 0 ends the script, and a command without a gate word ends
// the run as soon as the laser raised any scheduler flag. The commands prime
// the laser's scheduler slots (flags 1/0x10/0x20/0x40 and the sparse bits),
// aim and launch the beam (0x10 aims at the player when the angle parameter is
// above 1), queue the beam sound (0x20), grow the beam width (0x40/0x80/0x100),
// start the beam animation script (0x4000), set the length growth wait
// (0x8000), play a panned sound (0x20000), set the movement waits
// (0x100000/0x200000), switch the laser state (0x10000), set the laser id
// (0x1000000), jump to another command (0x2000000), move toward a point
// (0x4000000) and grow the beam length (0x400/0x800/0x8000000).
#include "th10/game/laser_script_run_0041ca80.hpp"
#include "th10/platform/sound_queue.hpp"

// 0x00405410: scheduler store; the record arrives in EAX, the value stays on
// the stack. Anchored as a co-compiled copy so the call keeps the retail shape.
struct PlayerSchedulerRecord {
    void SetSchedulerValue(int value);
};

// 0x00426660: angle from a point to an entity; the entity stays in ECX and
// the point arrives in EAX.
struct EntityAngleFromPoint_00426660 {
    float AngleFromPoint(const float* point);
};

// 0x00404F30: reinitialise an animation object and start script `script` of
// `resource` on it. The object arrives in ESI, the script index in EAX and
// only the resource is passed on the stack.
struct AnimationResource_0043e710;
void __stdcall Entity_StartScript_00404f30(AnimationResource_0043e710* resource,
                                           Entity* entity, int script);

#pragma code_seg(".text$0041ca80_fn")
void LaserScriptRun_0041ca80::Run() {
    while (pc_400 < 18) {
        LaserScriptCommand_0041ca80& cmd = commands[pc_400];
        if (cmd.opcode == 0)
            return;
        if (cmd.gate == 0 && flags_404 != 0)
            return;
        switch (cmd.opcode) {
        case 1u:
            flags_404 |= 1u;
            reinterpret_cast<PlayerSchedulerRecord*>(&timer_58)->SetSchedulerValue(0);
            duration_7C = 0;
            ++pc_400;
            break;
        case 0x10u:
            flags_404 |= 0x10u;
            speed_A0 = cmd.param0.f;
            float angle;
            if (cmd.param1.f > data_00470b50)
                angle = cmd.param1.f >= data_00470ccc
                    ? static_cast<EntityAngleFromPoint_00426660*>(data_00477834)
                        ->AngleFromPoint(&position_x_24)
                    : cmd.param1.f;
            else
                angle = angle_3C;
            angle_A4 = angle;
            reinterpret_cast<PlayerSchedulerRecord*>(&timer_8C)->SetSchedulerValue(0);
            sound_B4 = cmd.param2.i;
            polar_A8.SetPolar(angle_A4, speed_A0);
            if (pc_400 != 0 && sound_id_40C >= 0)
                data_00492590.Queue(sound_id_40C, 0);
            ++pc_400;
            break;
        case 0x20u:
            flags_404 |= 0x20u;
            offset_D4 = cmd.param0.f;
            offset_D8 = cmd.param1.f;
            reinterpret_cast<PlayerSchedulerRecord*>(&timer_C0)->SetSchedulerValue(0);
            sound_E8 = cmd.param2.i;
            if (pc_400 != 0 && sound_id_40C >= 0)
                data_00492590.Queue(sound_id_40C, 0);
            ++pc_400;
            break;
        case 0x40u:
        case 0x80u:
        case 0x100u:
            flags_404 |= cmd.opcode;
            mode_10C = cmd.param0.i;
            width_108 = cmd.param1.f > data_00470cc8 ? width_48 : cmd.param1.f;
            if (!(timer_F4.flags & 1u))
                timer_F4.InitDefaults();
            timer_F4.current = 0;
            timer_F4.elapsed = 0.0f;
            timer_F4.previous = -1;
            width_duration_11C = cmd.param2.i;
            width_duration_120 = cmd.param3.i;
            zero_124 = 0;
            ++pc_400;
            break;
        case 0x4000u: {
            int script = data_00474170[cmd.param2.i] + cmd.param3.i;
            Entity_StartScript_00404f30(
                reinterpret_cast<AnimationResource_0043e710*>(data_004776f0->resource),
                &beam, script);
            ++pc_400;
            break;
        }
        case 0x8000u:
            flags_404 |= cmd.opcode;
            timer_15C.SetSchedulerValue(cmd.param2.i);
            ++pc_400;
            break;
        case 0x20000u:
            data_00492590.QueuePan(cmd.param2.i, position_x_24);
            ++pc_400;
            break;
        case 0x10000u:
            state_C = 3;
            ++pc_400;
            break;
        case 0x100000u:
            flags_404 |= cmd.opcode;
            reinterpret_cast<PlayerSchedulerRecord*>(&timer_190)->SetSchedulerValue(cmd.param2.i);
            ++pc_400;
            break;
        case 0x200000u:
            flags_404 |= cmd.opcode;
            reinterpret_cast<PlayerSchedulerRecord*>(&timer_190)->SetSchedulerValue(cmd.param2.i);
            ++pc_400;
            break;
        case 0x1000000u:
            id_54 = cmd.param2.i;
            ++pc_400;
            break;
        case 0x400u:
        case 0x800u:
        case 0x8000000u:
            if (cmd.param2.i > 0) {
                flags_404 |= cmd.opcode;
                if (cmd.param0.f >= data_00470b04)
                    target_13C = cmd.param0.f;
                else
                    target_13C = width_48;
                --cmd.param2.i;
                phase_154 = 0;
                phase_150 = 0;
            }
            ++pc_400;
            break;
        case 0x4000000u:
            flags_404 |= 0x4000000u;
            move_x_20C = cmd.param0.f;
            move_y_210 = cmd.param1.f;
            if (!(timer_1F8.flags & 1u))
                timer_1F8.InitDefaults();
            timer_1F8.current = 0;
            timer_1F8.elapsed = 0.0f;
            timer_1F8.previous = -1;
            move_duration_220 = cmd.param2.i;
            ++pc_400;
            break;
        default:
            ++pc_400;
            break;
        }
    }
}
#pragma code_seg()
