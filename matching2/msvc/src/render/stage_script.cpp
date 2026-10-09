// 0x00403C80: run the stage script up to the current frame, then advance the
// camera and fog moves it started and the sideways camera sway.
#include <math.h>
#include "th10/render/stage_objects.hpp"

struct AnimationResource_0043e710;
struct Entity;
__declspec(noinline) void __stdcall Entity_StartScript_00404f30(
    AnimationResource_0043e710* resource, Entity* entity, int script);
extern "C" int data_004923a8;

#pragma code_seg(".text$00403c80_fn")
int __stdcall StageObjects_RunScript(StageObjects* stage) {
    while (stage->instruction->time <= stage->script_timer.current) {
        StageInstruction* instruction = stage->instruction;
        switch (instruction->opcode) {
        case 0:
            goto moves;
        case 1:
            stage->script_timer.Set(instruction->args[1].i);
            stage->instruction =
                reinterpret_cast<StageInstruction*>(stage->script + stage->instruction->args[0].i);
            continue;
        case 2:
            stage->Travel() = stage->Position();
            stage->Position().x = instruction->args[0].f;
            stage->Position().y = instruction->args[1].f;
            stage->Position().z = instruction->args[2].f;
            stage->Travel() = stage->Position() - stage->Travel();
            break;
        case 3: {
            Vec3 target(instruction->args[2].f, instruction->args[3].f, instruction->args[4].f);
            stage->position_move.duration = instruction->args[0].i;
            stage->position_move.mode = instruction->args[1].i;
            stage->position_move.value = stage->Position();
            stage->position_move.target = target;
            stage->position_move.timer.Reset();
            break;
        }
        case 4:
            stage->Direction().x = instruction->args[0].f;
            stage->Direction().y = instruction->args[1].f;
            stage->Direction().z = instruction->args[2].f;
            break;
        case 5: {
            Vec3 target(instruction->args[2].f, instruction->args[3].f, instruction->args[4].f);
            stage->direction_move.duration = instruction->args[0].i;
            stage->direction_move.mode = instruction->args[1].i;
            stage->direction_move.value = stage->Direction();
            stage->direction_move.target = target;
            stage->direction_move.timer.Reset();
            break;
        }
        case 6:
            stage->Up().x = instruction->args[0].f;
            stage->Up().y = instruction->args[1].f;
            stage->Up().z = instruction->args[2].f;
            break;
        case 7:
            stage->view.camera.field_of_view = instruction->args[0].f;
            break;
        case 8:
            stage->Fog().packed = instruction->args[0].u;
            stage->Fog().blue = stage->Fog().packed_blue;
            stage->Fog().green = stage->Fog().packed_green;
            stage->Fog().red = stage->Fog().packed_red;
            stage->Fog().alpha = stage->Fog().packed_alpha;
            stage->Fog().start = instruction->args[1].f;
            stage->Fog().end = instruction->args[2].f;
            break;
        case 9: {
            StageFog target(instruction->args[3].f, instruction->args[4].f,
                            instruction->args[2].b0, instruction->args[2].b1,
                            instruction->args[2].b2, instruction->args[2].b3);
            stage->fog_move.duration = instruction->args[0].i;
            stage->fog_move.mode = instruction->args[1].i;
            stage->fog_move.value = stage->Fog();
            stage->fog_move.target = target;
            stage->fog_move.timer.Reset();
            break;
        }
        case 10: {
            Vec3 control(instruction->args[2].f, instruction->args[3].f, instruction->args[4].f);
            Vec3 target(instruction->args[5].f, instruction->args[6].f, instruction->args[7].f);
            Vec3 velocity(instruction->args[8].f, instruction->args[9].f, instruction->args[10].f);
            stage->position_move.duration = instruction->args[0].i;
            stage->position_move.value = stage->Position();
            stage->position_move.control = control;
            stage->position_move.target = target;
            stage->position_move.mode = 8;
            stage->position_move.velocity = velocity;
            stage->position_move.timer.Reset();
            break;
        }
        case 11: {
            Vec3 control(instruction->args[2].f, instruction->args[3].f, instruction->args[4].f);
            Vec3 target(instruction->args[5].f, instruction->args[6].f, instruction->args[7].f);
            Vec3 velocity(instruction->args[8].f, instruction->args[9].f, instruction->args[10].f);
            stage->direction_move.duration = instruction->args[0].i;
            stage->direction_move.value = stage->Direction();
            stage->direction_move.control = control;
            stage->direction_move.target = target;
            stage->direction_move.mode = 8;
            stage->direction_move.velocity = velocity;
            stage->direction_move.timer.Reset();
            break;
        }
        case 12:
            stage->sway_mode = instruction->args[0].b0;
            stage->sway_timer.Reset();
            break;
        case 13:
            data_004923a8 = instruction->args[0].i;
            break;
        case 14:
            if (instruction->args[1].i >= 0) {
                Entity_StartScript_00404f30(
                    static_cast<AnimationResource_0043e710*>(stage->animations),
                    reinterpret_cast<Entity*>(&stage->sprites[instruction->args[0].i]),
                    instruction->args[1].i);
            } else {
                StageEntity* sprite = &stage->sprites[instruction->args[0].i];
                sprite->flags &= ~1u;
            }
            break;
        }
        stage->instruction = reinterpret_cast<StageInstruction*>(
            reinterpret_cast<char*>(stage->instruction) + stage->instruction->size);
    }
    stage->script_timer.TickInline();
moves:
    if (stage->direction_move.duration) stage->Direction() = stage->direction_move.Step();
    if (stage->position_move.duration) stage->Position() = stage->position_move.Step();
    if (stage->fog_move.duration) stage->Fog() = stage->fog_move.Step();
    if (stage->sway_mode) {
        switch (stage->sway_mode) {
        case 1:
            stage->view.camera.eye_offset.x =
                sinf(stage->sway_timer.elapsed * 0.012271846644580364f - 3.1415927410125732f) * -100.0f;
            stage->sway_timer.Tick();
            if (stage->sway_timer.current >= 512) stage->sway_timer.Set(0);
            break;
        }
    }
    return 0;
}
#pragma code_seg()
