// Full 0041F400..0041F66E (623 bytes) C++ recovery model.
// This routine is distinct from 0041E260: it conditionally creates an
// animation after an outer rectangle check and calls the outlined registrar.
#include "types/line_sweeps.hpp"
extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)

#pragma code_seg(".text$f0041f400F")
__declspec(noinline) int LineEffectSweep_0041e260::CreateSegmentsInBounds(int spawn_items) {
    float distance;
    int count = 0;
    distance = 6.0f;
    LineSweepStep_0041e260 step;
    step.velocity.SetPolar(angle, 6.0f);

    // Retail retains a three-word initial-position temporary, then copies it
    // into the point that advances along the line.  Z starts at the owner's Z
    // and the step's Z is zero, so every iteration preserves that coordinate.
    LineSweepVector_0041e260 point;
    point = LineSweepVector_0041e260(step.velocity.x + position.x,
        step.velocity.y + position.y, position.z);
    step.z = 0.0f;
    step.velocity.x = step.velocity.x + step.velocity.x;
    step.velocity.y = step.velocity.y + step.velocity.y;
    if (12.0f < length) {
    do {
        ++count;
        // Negated comparisons reproduce the observed x87 unordered behavior:
        // NaN passes these bounds.  TEST AH,41 / JNP rejects <=; TEST AH,1 /
        // JZ rejects >=.  Do not rewrite these as four ordinary strict tests.
        if (!(point.x + 16.0f <= -192.0f) &&
            !(point.x - 16.0f >= 192.0f)) {
            float animation_y = point.y + 16.0f;
            if (!(animation_y <= data_00470b04) &&
                !(point.y - 16.0f >= 448.0f)) {
                int script = script_in_bounds * 2 + 17;
                void* resource = g_laser_manager->line_animation;
                Entity* animation = static_cast<AnimationPool*>(data_00491c10)->Allocate();
                unsigned int flags = animation->flags_35C;
                animation->flags_35C = flags | 0x40000000u;
                animation->render_bucket = 0;
                Vector3* position_output = &animation->position;
                position_output->x = point.x + 224.0f;
                position_output->y = animation_y;
                position_output->z = point.z;
                LoadScript_0043e710(
                    static_cast<AnimationResource_0043e710*>(resource),
                    reinterpret_cast<AnimationObject_0043e710*>(animation), script);
                void* handle;
                asm_AnimationManager_RegisterPrimaryBack_004489d0(
                    data_00491c10, &handle, animation);

                // The second rectangle has a 32-unit margin and is reached
                // only after creating and registering the destruction effect.
                if (spawn_items &&
                    !(point.x + 32.0f <= -192.0f) &&
                    !(point.x - 32.0f >= 192.0f) &&
                    !(point.y + 32.0f <= data_00470b04) &&
                    !(point.y - 32.0f >= 448.0f)) {
                    data_00477818->Spawn(
                        &point, 8, -1, -1.57079637050628662109375f,
                        0.60000002384185791015625f);
                }
            }
        }
        point.x = point.x + step.velocity.x;
        point.y = point.y + step.velocity.y;
        // Preserve both floating-point reads when advancing Z.
        volatile float& point_z = point.z;
        point_z = point_z + step.z;
        distance = distance + 12.0f;
    } while (distance + 6.0f < length);
    }

    retired = 1;
    return count;
}
#pragma code_seg()
