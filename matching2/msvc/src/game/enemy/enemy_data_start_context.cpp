// Link context for the 0x0040DC80 model: models of the helpers it calls, so
// the checking LTCG link derives the private register conventions retail
// has. Only EnemyDataStart is compared. The bodies follow the
// recovered sources named beside them.
#include "th10/runtime/game/enemy/enemy_data_start_context.hpp"
#include <string.h>
#include "th10/math/interpolator_step.hpp"

// The counters and managers are the game's own objects at their retail
// addresses; the cluster binds them absolutely.
extern "C" {
extern Player* g_player;
extern Bomb* g_bomb;
extern GameThreadFlagsView* g_card;
extern Gui2* g_front;
extern EnemyAnmManagerView* g_sprt_ctrl;
extern ScoreState2 g_globals;
extern SoundQueue g_sound_manager;
extern int g_enemy_hittable;
extern PolarVec3 g_enemy_scroll;
}
extern float g_frame_timer_normal_lower;
extern float g_frame_timer_normal_upper;
extern "C" float g_game_speed;

extern "C" short g_sound_priority[];
extern "C" void __stdcall ext_call(void* a, int b);
extern "C" void __cdecl ext_free(void* memory);
extern "C" int __stdcall ext_run(EclChildState* state, float delta);

// src/game/background/vec3_interpolator.cpp, src/game/enemy/trajectory_interpolator.cpp
// The two Interpolator Step bodies come from their own recovered sources
// (wrappers in the cluster layout): template members take the section in
// effect at the end of the file, so they cannot share this translation unit.

// src/core/zunlib/polar_motion_advance.cpp
#pragma code_seg(".text$0044c2a0_pma")
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
#pragma code_seg(".text$0044bf40_fta")
void FrameTimer::Advance(float delta) {
    previous = current;
    if (*speed > g_frame_timer_normal_lower && *speed < g_frame_timer_normal_upper) {
        elapsed += delta;
    } else {
        elapsed += delta * *speed;
    }
    current = int(elapsed);
}

// src/core/sprtlib/animation_manager_find.cpp
struct AnimationNode4 {
    AnimationNode4* object;
    AnimationNode4* next;
    unsigned char reserved_08[0x0C];
    AnimationNode4* children;
    int children_flagged;
    unsigned char reserved_1c[0x324];
    PolarVec3 position;                  // +0x340
};
struct EnemyAnmManagerView {
    unsigned char reserved[0x72DAD4];
    AnimationNode4* primary_bucket;
    int reserved_2;
    AnimationNode4* secondary_bucket;
};
#pragma code_seg(".text$004491c0_find")
Animation2* __fastcall AnimationFinder::Find(
        EnemyAnmManagerView* manager, ScriptChangeHandle id) {
    if (!id.id)
        return 0;
    for (AnimationNode4* node = manager->primary_bucket; node != 0; node = node->next)
        if (*(int*)node->object == id.id)
            return (Animation2*)node->object;
    for (AnimationNode4* node = manager->secondary_bucket; node != 0; node = node->next)
        if (*(int*)node->object == id.id)
            return (Animation2*)node->object;
    return 0;
}

// src/core/sprtlib/animation_manager_set_translated_position.cpp
#pragma code_seg(".text$00449350_sett")
void __fastcall SetAnimationTranslatedPosition(
        EnemyAnmManagerView* manager, const PolarVec3* position, ScriptChangeHandle id) {
    AnimationNode4* entry = (AnimationNode4*)AnimationManager_Find(manager, id);
    if (entry != 0) {
        entry->position.x = position->x + 224.0f;
        entry->position.y = position->y + 16.0f;
        entry->position.z = position->z;
        if (!entry->children_flagged) {
            for (AnimationNode4* child = entry->children; child; child = child->next) {
                PolarVec3* destination = &child->object->position;
                destination->x = position->x + 224.0f;
                destination->y = position->y + 16.0f;
                destination->z = position->z;
            }
        }
    }
}

// src/game/laser/laser_manager.cpp
#pragma code_seg(".text$004492f0_setp")
void __fastcall Animation_SetPosition(
        EnemyAnmManagerView* manager, const PolarVec3* position, ScriptChangeHandle id) {
    AnimationNode4* object = (AnimationNode4*)AnimationManager_Find(manager, id);
    if (object != 0) {
        object->position = *position;
        if (object->children_flagged == 0)
            for (AnimationNode4* child = object->children; child != 0; child = child->next)
                child->object->position = *position;
    }
}

// src/core/sprtlib/animation_handle_change_script.cpp
#pragma code_seg(".text$004496d0_chg")
void ScriptChangeHandle::ChangeScript(int index) {
    Animation2* object = AnimationManager_Find(g_sprt_ctrl, *this);
    if (object) ext_call(object, index);
}

// src/script/sptcmd/ecl_vm_children.cpp
#pragma code_seg(".text$0044fd10_tck")
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

// src/game/enemy/enemy_clear_resource_list.cpp
struct ResourceRecord {
    void* resource;
    ResourceRecord* next;
};
struct EnemyRecordLayout {
    unsigned char pad_0000[0x08];
    float root_time;                 // +0x0008
    void* root_instruction;          // +0x000C
    unsigned char pad_0010[0x1018 - 0x10];
    int slot_id;                     // +0x1018
    void* owner_self;                // +0x101C
    int state_word;                  // +0x1020
    unsigned char pad_1024[0x04];
    unsigned int script_flags;       // +0x1028
    unsigned char pad_102c[0x04];
    void* frame_head;                // +0x1030
    ResourceRecord* resource_head;   // +0x1034
    void* resource_tail;             // +0x1038
};
struct FrontBossView {
    unsigned char pad_0000[0x9EB8];
    int boss_active;
};
struct PlayerHitboxView {
    unsigned char pad_0000[0x404];
    Vec2 hitbox_min;                 // +0x0404
    unsigned char pad_040c[0x04];
    Vec2 hitbox_max;                 // +0x0410
    unsigned char pad_0418[0x4310 - 0x418];
    int invincible_timer;            // +0x4310
};
#pragma code_seg(".text$0040c6e0_clr")
void EnemyRecord::ClearResourceList() {
    ResourceRecord* record = reinterpret_cast<EnemyRecordLayout*>(this)->resource_head;
    while (record != 0) {
        ResourceRecord* next = record->next;
        ext_free(record->resource);
        ext_free(record);
        record = next;
    }
}

// src/game/enemy/ecl_record_reset.cpp
#pragma code_seg(".text$0040c730_rst")
void EnemyRecord::ResetScript() {
    EnemyRecordLayout* self = reinterpret_cast<EnemyRecordLayout*>(this);
    self->root_time = 0.0f;
    self->root_instruction = 0;
    self->script_flags &= ~1u;
    self->owner_self = this;
    self->slot_id = -1;
    self->state_word = 0;
    current = reinterpret_cast<ScriptFrame*>(&self->root_time);
    self->frame_head = &self->root_time;
    self->resource_head = 0;
    self->resource_tail = 0;
}

// src/script/sptlib/final_script_runtime.cpp
#pragma code_seg(".text$00450470_rsl")
int ScriptTable2::Resolve(const char* name) {
    int low = 0;
    int high = this->count;
    if (--high >= 0) {
        const EclTableEntry* entries = this->entries;
        do {
            const int middle = low + (high - low) / 2;
            const EclTableEntry* entry = &entries[middle];
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

// src/script/sptlib/ecl_bind_name.cpp
#pragma code_seg(".text$00450700_bnd")
int __fastcall BindName(EnemyRecord* record, const char* name) {
    ScriptTable2* script_table = record->table;
    record->table = script_table;
    record->current->instruction = script_table->Resolve(name);
    record->current->time = 0;
    return 0;
}

// src/game/player/field_contact.cpp
#pragma code_seg(".text$004266b0_fld")
int __fastcall FieldContact(
        const PolarVec3* position, Player* player, const Vec2* size) {
    const PlayerHitboxView* hitbox = reinterpret_cast<const PlayerHitboxView*>(player);
    const Vec2* low = &hitbox->hitbox_min;
    const Vec2* high = &hitbox->hitbox_max;
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
    if (g_front && reinterpret_cast<FrontBossView*>(g_front)->boss_active)
        return 0;
    if (player->state == 2 || player->state == 4 || player->state == 3)
        return 0;
    if (hitbox->invincible_timer <= 0)
        ext_call(player, 0);
    return 1;
}

// src/core/sound/sound_queue_pan.cpp
#pragma code_seg(".text$0043dd10_pan")
void SoundQueue::QueuePan(int sound_id, float pan) {
    int priority = g_sound_priority[sound_id * 4];
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
#pragma code_seg()
