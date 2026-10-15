// Callees of the player-state update, present so that the update sees their
// register conventions. Compiler context only; none of these bytes enter the
// image. The bodies repeat the recovered sources named beside them.
#include "player_state.hpp"
#include "animation_public_callers.hpp"
#pragma intrinsic(atan2)

struct OpenReplayState { unsigned char reserved_00[0x58]; unsigned int flags; int replay_mode; };
extern "C" {
extern OpenReplayState* data_00477810;
extern int data_00491fb8;
extern void* data_004776e0;
extern const float data_00470b04, data_00470b94;
__declspec(noinline) void __stdcall OpenInitialize_00420a90(void* resource, void* object, int script);
__declspec(noinline) int __stdcall OpenRegister_0043e460(void* lists, void* object);
}

// src/game/set_input_mode_0040ac90.cpp
#pragma code_seg(".text$f0040ac90F")
void PlayerInputMode::Set(int value) {
    if ((flags & 0x1000) == 0) mode = value;
    else mode = 2;
}
// src/game/entity_angle_to_point_00426610.cpp
#pragma code_seg(".text$f00426610F")
extern "C" __declspec(noinline) double __stdcall Entity_AngleToPoint_00426610(const Player* player, const Vec3* point) {
    float horizontal = point->x - player->position.x;
    float vertical = point->y - player->position.y;
    if (vertical == data_00470b04 && horizontal == data_00470b04)
        return data_00470b94;
    return atan2(vertical, horizontal);
}
// src/game/power_display_set_digits_004054b0.cpp
inline AnimationObject_0043e5a0* DigitSprite_004054b0(unsigned char* storage) {
    return reinterpret_cast<AnimationObject_0043e5a0*>(storage);
}

#pragma code_seg(".text$f004054b0F")
void PowerDisplayOwner_004054b0::SetPowerDigits(int whole, int fraction) {
    sprites->ConfigureObject(DigitSprite_004054b0(whole_digit), whole + 8);
    sprites->ConfigureObject(DigitSprite_004054b0(tens_digit), fraction / 10 + 8);
    sprites->ConfigureObject(DigitSprite_004054b0(ones_digit), fraction % 10 + 8);
}
// src/game/animation_object_configure_from_resource_0043e5a0.cpp
#pragma code_seg(".text$f0043e5a0F")
__declspec(noinline) int Resource_0043e5a0::ConfigureObject(
    AnimationObject_0043e5a0* object, int index) {
    unsigned char* res = reinterpret_cast<unsigned char*>(this);
    if (*reinterpret_cast<void**>(res + 0x108) == 0 ||
        *reinterpret_cast<unsigned int*>(res + 0x124) != 0)
        return -1;

    object->record_index = static_cast<unsigned short>(index);
    object->resource = this;
    object->record = *reinterpret_cast<unsigned char**>(res + 0x118) + index * 0x44;
    object->width = *reinterpret_cast<float*>(object->record + 0x34);
    object->height = *reinterpret_cast<float*>(object->record + 0x30);
    object->block_a.SetIdentity();
    object->block_b.SetIdentity();
    unsigned char* rec = object->record;
    object->block_a.values[0][0] = object->width * 0.00390625f;
    object->block_a.values[1][1] = object->height * 0.00390625f;
    object->block_b.values[0][0] =
        (*reinterpret_cast<float*>(rec + 0x38) /
         *reinterpret_cast<float*>(rec + 0x1C)) * object->width;
    object->block_b.values[1][1] =
        (*reinterpret_cast<float*>(rec + 0x3C) /
         *reinterpret_cast<float*>(rec + 0x18)) * object->height;
    object->block_copy = object->block_a;
    return 0;
}
// Stand-in for the pause opener at 0x004231D0 (src/game/pause_result_open.cpp).
// Like the real body it keeps its receiver live across the pool allocation,
// whose pool travels in ESI, so the receiver arrives in EDI.
#pragma code_seg(".text$f004231d0F")
int PlayerDeathScene::Open() {
    if (data_00477810->replay_mode == 1) {
        data_00491fb8 = 4;
        return 0;
    }
    phase = 6;
    timer.Set(0);
    data_00477810->flags |= 0x10;
    void* resource = data_004776e0;
    Entity* object = static_cast<AnimationPool*>(data_00491c10)->Allocate();
    OpenInitialize_00420a90(resource, object, 0);
    cursor = OpenRegister_0043e460(data_00491c10, object);
    object = static_cast<AnimationPool*>(data_00491c10)->Allocate();
    OpenInitialize_00420a90(resource, object, 128);
    background = OpenRegister_0043e460(data_00491c10, object);
    current_resource = 0;
    result_flag = 0;
    return 0;
}
#pragma code_seg()
