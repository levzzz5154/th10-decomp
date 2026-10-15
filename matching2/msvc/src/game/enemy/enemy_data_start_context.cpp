// Link context for the 0x0040DC80 model: models of the helpers it calls, so
// the checking LTCG link derives the private register conventions retail
// has. Only EnemyDataStart_0040dc80 is compared. The bodies follow the
// recovered sources named beside them.
#include "th10/runtime/game/enemy/enemy_data_start_context.hpp"
#include <string.h>
#include "th10/math/interpolator_step.hpp"

float g_frame_timer_normal_lower = 0.99f;
float g_frame_timer_normal_upper = 1.01f;
float g_score_default_speed = 1.0f;
extern "C" {
Player* g_player;
Bomb* g_bomb;
GameThread_0040dc80* g_card;
Gui_0040dc80* g_front;
AnimationManager_0040dc80* g_sprt_ctrl;
ScoreState_0040dc80 data_00474c40;
SoundQueue data_00492590;
int data_00474c50;
PolarVec3 data_00491e6c;
}

extern "C" short data_004749ce[];
extern "C" void __stdcall ext_call(void* a, int b);
extern "C" void __cdecl ext_free(void* memory);
extern "C" int __stdcall ext_run(EclChildState* state, float delta);

// src/game/background/vec3_interpolator.cpp, src/game/enemy/trajectory_interpolator.cpp
template struct Interpolator<Vec3>;
template struct Interpolator<TrajectoryVec2>;

// src/core/zunlib/polar_motion_advance.cpp
void PolarMotion::Advance() {
    PolarVec3 offset;
    if ((flags & 1) == 0) {
        position += velocity;
        position.SnapToHundredths();
        return;
    }
    offset.SetPolar(angle, radius);
    offset.z = 0.0f;
    position = offset + velocity;
    position.SnapToHundredths();
}

// build_support/layout/units/frame_timer_ef24e7.cpp
void FrameTimer::Advance(float delta) {
    previous = current;
    if (*speed > g_frame_timer_normal_lower && *speed < g_frame_timer_normal_upper) {
        elapsed += delta;
    } else {
        elapsed += delta * *speed;
    }
    current = int(elapsed);
}

// src/core/sprtlib/animation_manager_find_004491c0.cpp
struct AnimationNode_0040dc80 {
    AnimationNode_0040dc80* object;
    AnimationNode_0040dc80* next;
    unsigned char reserved_08[0x0C];
    AnimationNode_0040dc80* children;
    int children_flagged;
    unsigned char reserved_1c[0x324];
    PolarVec3 position;                  // +0x340
};
struct AnimationManager_0040dc80 {
    unsigned char reserved[0x72DAD4];
    AnimationNode_0040dc80* primary_bucket;
    int reserved_2;
    AnimationNode_0040dc80* secondary_bucket;
};
Animation_0040dc80* __fastcall AnimationFinder_0040dc80::Find(
        AnimationManager_0040dc80* manager, ScriptChangeHandle id) {
    if (!id.id)
        return 0;
    for (AnimationNode_0040dc80* node = manager->primary_bucket; node != 0; node = node->next)
        if (*(int*)node->object == id.id)
            return (Animation_0040dc80*)node->object;
    for (AnimationNode_0040dc80* node = manager->secondary_bucket; node != 0; node = node->next)
        if (*(int*)node->object == id.id)
            return (Animation_0040dc80*)node->object;
    return 0;
}

// src/core/sprtlib/animation_manager_set_translated_position_00449350.cpp
void __fastcall SetAnimationTranslatedPosition_00449350(
        AnimationManager_0040dc80* manager, const PolarVec3* position, ScriptChangeHandle id) {
    AnimationNode_0040dc80* entry = (AnimationNode_0040dc80*)AnimationManager_Find_004491c0(manager, id);
    if (entry != 0) {
        entry->position.x = position->x + 224.0f;
        entry->position.y = position->y + 16.0f;
        entry->position.z = position->z;
        if (!entry->children_flagged) {
            for (AnimationNode_0040dc80* child = entry->children; child; child = child->next) {
                PolarVec3* destination = &child->object->position;
                destination->x = position->x + 224.0f;
                destination->y = position->y + 16.0f;
                destination->z = position->z;
            }
        }
    }
}

// src/game/laser/laser_manager.cpp
void __fastcall Animation_SetPosition(
        AnimationManager_0040dc80* manager, const PolarVec3* position, ScriptChangeHandle id) {
    AnimationNode_0040dc80* object = (AnimationNode_0040dc80*)AnimationManager_Find_004491c0(manager, id);
    if (object != 0) {
        object->position = *position;
        if (object->children_flagged == 0)
            for (AnimationNode_0040dc80* child = object->children; child != 0; child = child->next)
                child->object->position = *position;
    }
}

// src/core/sprtlib/animation_handle_change_script_004496d0.cpp
void ScriptChangeHandle::ChangeScript(int index) {
    Animation_0040dc80* object = AnimationManager_Find_004491c0(g_sprt_ctrl, *this);
    if (object) ext_call(object, index);
}

// src/script/sptcmd/ecl_vm_children.cpp
extern "C" __declspec(noinline) int __stdcall EclVm_TickChildren(EclChildOwner* owner, float delta) {
    EclChildNode* node = &owner->children;
    int first = 1;
    while (node) {
        EclChildNode* next = node->next;
        owner->active = node->state;
        if (first) {
            if (ext_run(owner->active, delta)) return -1;
            first = 0;
        } else if (ext_run(owner->active, delta)) {
            ext_free(owner->active);
            node->Unlink();
            ext_free(node);
        }
        node = next;
    }
    owner->active = &owner->root;
    return 0;
}

// src/game/enemy/bullet_entity_clear_resource_list_0040c6e0.cpp
struct ResourceRecord_0040dc80 {
    void* resource;
    ResourceRecord_0040dc80* next;
};
void EnemyRecord_0040dc80::ClearResourceList() {
    ResourceRecord_0040dc80* record = *(ResourceRecord_0040dc80**)((unsigned char*)this + 0x1034);
    while (record != 0) {
        ResourceRecord_0040dc80* next = record->next;
        ext_free(record->resource);
        ext_free(record);
        record = next;
    }
}

// src/game/enemy/ecl_record_reset_0040c730.cpp
void EnemyRecord_0040dc80::ResetScript() {
    unsigned char* self = (unsigned char*)this;
    *(float*)(self + 0x8) = 0.0f;
    *(void**)(self + 0xC) = 0;
    *(unsigned int*)(self + 0x1028) &= ~1u;
    *(void**)(self + 0x101C) = this;
    *(int*)(self + 0x1018) = -1;
    *(int*)(self + 0x1020) = 0;
    current = (ScriptFrame_0040dc80*)(self + 0x8);
    *(void**)(self + 0x1030) = self + 0x8;
    *(void**)(self + 0x1034) = 0;
    *(void**)(self + 0x1038) = 0;
}

// src/script/sptlib/final_script_runtime.cpp
int ScriptTable_00450470::Resolve(const char* name) {
    int low = 0;
    int high = this->count;
    if (--high >= 0) {
        const ScriptEntry_00450470* entries = this->entries;
        do {
            const int middle = low + (high - low) / 2;
            const ScriptEntry_00450470* entry = &entries[middle];
            const int order = strcmp(name, entry->name);
            if (order == 0)
                return static_cast<int>(entry->value) + 16;
            if (order < 0)
                high = middle - 1;
            else
                low = middle + 1;
        } while (low <= high);
    }
    return 0;
}

// src/script/sptlib/fun_00450700_00450700.cpp
int __fastcall BindName_00450700(const char* name, EnemyRecord_0040dc80* record) {
    ScriptTable_00450470* script_table = record->table;
    record->table = script_table;
    record->current->instruction = script_table->Resolve(name);
    record->current->time = 0;
    return 0;
}

// src/game/player/field_contact_004266b0.cpp
int __fastcall FieldContact_004266b0(
        const PolarVec3* position, Player* player, const Vec2* size) {
    const Vec2* low = (const Vec2*)((unsigned char*)player + 0x404);
    const Vec2* high = (const Vec2*)((unsigned char*)player + 0x410);
    Vec2 minimum(position->x - size->x * 0.5f, position->y - size->y * 0.5f);
    Vec2 maximum(position->x + size->x * 0.5f, position->y + size->y * 0.5f);
    if (low->x > maximum.x || maximum.y < low->y || high->x < minimum.x || high->y < minimum.y) {
        minimum.x = position->x - 24.0f;
        minimum.y = position->y - 24.0f;
        Vec2 outer(position->x + 24.0f, position->y + 24.0f);
        if (outer.x < low->x || low->y > outer.y || high->x < minimum.x || high->y < minimum.y)
            return 0;
        return 2;
    }
    if (g_front && *(int*)((unsigned char*)g_front + 0x9EB8))
        return 0;
    if (player->state == 2 || player->state == 4 || player->state == 3)
        return 0;
    if (*(int*)((unsigned char*)player + 0x4310) <= 0)
        ext_call(player, 0);
    return 1;
}

// src/core/sound/sound_queue_pan_0043dd10.cpp
void SoundQueue::QueuePan(int sound_id, float pan) {
    int priority = data_004749ce[sound_id * 4];
    int request = int(pan * (1000.0f / 192.0f));
    int slot;
    for (slot = 0; slot < 12; ++slot) {
        if (sound_ids[slot] < 0)
            break;
        if (sound_ids[slot] == sound_id) {
            int count = counts[slot];
            if (count < 128) {
                requests[slot][count] = request;
                ++counts[slot];
            }
            return;
        }
    }
    if (slot < 12) {
        sound_ids[slot] = sound_id;
        priorities[sound_id] = priority;
        requests[slot][0] = request;
        ++counts[slot];
    }
}

extern "C" int __stdcall RigEntry(EnemyTick_0040dc80** enemies, int count) {
    int total = 0;
    for (int i = 0; i < count; ++i) total += EnemyDataStart_0040dc80(enemies[i]);
    return total;
}
