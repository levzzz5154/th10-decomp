// 0x00405860: start a bomb: its animation, sound and the power display.
#include <stddef.h>
#include "th10/game/entity.hpp"
#include "th10/platform/sound_queue.hpp"
extern "C" void* data_00491c10;
extern "C" const float data_00470b4c;
extern "C" const float data_00470b48;
extern "C" const float data_00470b20;
extern "C" const float data_00470b7c;
#include "../../layout/ltcg/player_initialize_00405860_dependencies/entity_init.cpp"
#include "../../layout/ltcg/player_initialize_00405860_dependencies/allocate.cpp"
#include "../../layout/ltcg/player_initialize_00405860_dependencies/load_script.cpp"
#include "../../layout/ltcg/player_initialize_00405860_dependencies/configure.cpp"
#include "th10/game/power_display_004054b0.hpp"
#include "../../layout/ltcg/player_initialize_00405860_dependencies/clear_flags.cpp"
#include "../../layout/ltcg/player_initialize_00405860_dependencies/sound_pan.cpp"
#include "th10/game/bomb.hpp"

struct PrimaryListNode {
    Entity* owner;
    PrimaryListNode* next;
    PrimaryListNode* previous;
};
struct AnimationPrimaryLists {
    unsigned char pad_000000[0x72DAD4];
    PrimaryListNode* head;
    PrimaryListNode* tail;
    unsigned char pad_72dadc[0x732454-0x72DADC];
    int serial;
    __declspec(noinline) int* RegisterPrimaryBack(int* out, Entity* entity);
};
#pragma code_seg(".text$a08register")
int* AnimationPrimaryLists::RegisterPrimaryBack(int* out, Entity* entity) {
    PrimaryListNode* node = reinterpret_cast<PrimaryListNode*>(&entity->manager_node_animation);
    node->owner = entity;
    node->next = 0;
    node->previous = 0;
    if (!head) head = node;
    else {
        PrimaryListNode* old = tail;
        if (old->next) {
            node->next = old->next;
            old->next->previous = node;
        }
        old->next = node;
        node->previous = old;
    }
    tail = node;
    ++serial;
    if (!serial) ++serial;
    entity->animation_handle = serial;
    *out = serial;
    return out;
}
#pragma code_seg(".text$a09create")
__declspec(noinline) int* __stdcall CreateScreenPositionedPrimary_00448db0(
    AnimationResource_0043e710* resource, int* out, int index, const Vector3* position) {
    Entity* object = reinterpret_cast<AnimationPool*>(data_00491c10)->Allocate();
    unsigned int flags = object->flags_35C;
    object->render_bucket = 0;
    object->flags_35C = flags | 0x40000000;
    object->position.x = position->x + data_00470b4c;
    object->position.y = position->y + data_00470b48;
    object->position.z = position->z;
    LoadScript_0043e710(resource, static_cast<AnimationObject_0043e710*>(object), index);
    reinterpret_cast<AnimationPrimaryLists*>(data_00491c10)->RegisterPrimaryBack(out, object);
    return out;
}

struct PlayerAnimationResources {
    unsigned char pad00[0x3E0B50];
    AnimationResource_0043e710* resource;
};
typedef PlayerFlags_00405500 PlayerInitializeGlobal;
extern "C" PlayerAnimationResources* data_004776f0;
extern "C" PlayerInitializeGlobal* g_card;
extern "C" PowerDisplayOwner_004054b0* data_0047770c;
extern "C" int data_00474c68;
extern "C" short data_00474c48;
extern "C" int data_00474c98;
#pragma code_seg(".text$a04initialize")
int __stdcall Bomb_Start(Bomb* bomb) {
    if (bomb->active) return -1;
    bomb->active = 1;
    bomb->timer.Reset();
    bomb->radius = 32.0f;
    bomb->unknown_40 = 4.0f;
    bomb->position = g_player->position;
    int index;
    if ((!(g_card->flags & 1) ||
         g_card->animation_state < 0x5D ||
         g_card->animation_state > 0x60) &&
        g_card->animation_state != 0x6D)
        index = data_00474c68 ? 0x197 : 0x190;
    else
        index = 0x1B9;
    int handle;
    bomb->animation = *CreateScreenPositionedPrimary_00448db0(
        data_004776f0->resource, &handle, index, &bomb->position);
    data_00492590.QueuePan(0x26, bomb->position.x);
    int power = data_00474c48;
    data_0047770c->SetPowerDigits(power / 20, (power % 20) * 100 / 20);
    PlayerInitializeGlobal* state = g_card;
    state->ClearExpiredFlags();
    data_00474c98 -= 0x80;
    if (data_00474c98 > 0x400) data_00474c98 = 0x400;
    else if (data_00474c98 < -0x400) data_00474c98 = -0x400;
    if ((state->flags & 1) && state->elapsed_frames >= 60) bomb->mode = 1;
    else bomb->mode = 0;
    return 0;
}
#pragma code_seg()
