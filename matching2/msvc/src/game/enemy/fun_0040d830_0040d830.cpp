// 0x0040D830: initialize an enemy script record and bind its first instruction.
// The record embeds the interpreter instance at +0x8, its own instance link at
// +0x1030, and the animation/entity payload at +0x103C. The retail entry uses
// ESI for the record and a single stack word for the script name, returning
// the record in EAX with RET4. The native LTCG context supplies that private
// convention from a legal fastcall declaration. Its first argument preserves
// the caller's ECX for ClearAnims, whose ordinary fastcall interface ignores it.
#include "th10/game/enemy_script_bind_0040d830.hpp"
#include <string.h>

extern "C" float g_game_speed;
extern "C" unsigned char g_enemy_vtable_live;
struct BindGameState_0040d830 {
    unsigned char reserved[0x54];
    BindScriptTable_0040d830* table;
};
extern "C" BindGameState_0040d830* g_enemy_ctrl;
struct EnemyScriptEntity_0040d830;
struct BindScriptName_0040d830 { const char* value; };
struct BindFrameTimer_0040d830 {
    int previous, current;
    float elapsed;
    const float* speed;
    unsigned int flags;
    // Initialize the timer once, then reset its current and previous values.
    __forceinline void Reset() {
        if ((flags & 1) == 0) {
            current = 0;
            previous = 0xFFF0BDC1;
            elapsed = 0.0f;
            speed = &g_game_speed;
            flags |= 1;
        }
        int* tail = &current;
        tail[0] = 0;
        tail[1] = 0;
        tail[-1] = -1;
    }
};
struct BindInstance_0040d830 {
    float timer;
    void* instruction;
    unsigned char reserved_008[0x1008 - 8];
    int scratch_cursor;
    int unknown_100c;
    int name;
    EnemyScriptEntity_0040d830* owner;
    int unknown_1018;
    unsigned char mask;
    unsigned char reserved_101d[3];
    unsigned int flags;
    __forceinline void Reset(EnemyScriptEntity_0040d830* entity, unsigned int retained_flags) {
        timer = 0.0f;
        instruction = 0;
        owner = entity;
        flags = retained_flags & ~1u;
        int* reset_tail = &unknown_1018;
        reset_tail[0] = 0;
    }
};
struct BindInstanceNode_0040d830 {
    BindInstance_0040d830* instance;
    BindInstanceNode_0040d830* next;
    BindInstanceNode_0040d830* prev;
};
struct BindOwnerLink_0040d830 {
    EnemyScriptEntity_0040d830* owner;
    void* next;
    void* prev;
};
struct BindMarker_0040d830 { int reserved, first, second, flags; };
struct BindPayload_0040d830 {
    unsigned char reserved_103c[0x2C];
    unsigned int snapshot_a[11]; // +0x1068
    unsigned int snapshot_b[11]; // +0x1094
    unsigned int snapshot_c[11]; // +0x10C0
    float bounds[4]; // +0x10EC
    unsigned char reserved_10fc[0x5C];
    BindFrameTimer_0040d830 timer; // +0x1158
    BindOwnerLink_0040d830 manager_link; // +0x116C
    unsigned char reserved_1178[0x44];
    int field_11bc; // +0x11BC
    unsigned char reserved_11c0[0x48];
    int field_1208; // +0x1208
    unsigned char reserved_120c[0x38];
    int field_1244; // +0x1244
    unsigned char reserved_1248[0x38];
    int field_1280; // +0x1280
    unsigned char reserved_1284[0x38];
    int field_12bc; // +0x12BC
    unsigned char reserved_12c0[0x38];
    int field_12f8; // +0x12F8
    unsigned char reserved_12fc[0x1100];
    float position[3]; // +0x23FC
    float auxiliary_bounds[15]; // +0x2408
    unsigned char reserved_2444[0x14];
    BindFrameTimer_0040d830 auxiliary_timer; // +0x2458
    BindFrameTimer_0040d830 second_auxiliary_timer; // +0x246C
    unsigned char reserved_2480[0xC];
    int identifier; // +0x248C
    BindMarker_0040d830 markers[8]; // +0x2490
    unsigned char reserved_2510[0x4];
    EnemyScriptEntity_0040d830* owner; // +0x2514
};
struct EnemyScriptEntity_0040d830 {
    void* vtable;
    BindInstance_0040d830* running;
    BindInstance_0040d830 instance;
    BindScriptTable_0040d830* table;
    BindInstanceNode_0040d830 self;
    BindPayload_0040d830 payload;
};

#pragma code_seg(".text$30bind")
__declspec(noinline) EnemyScriptEntity_0040d830* __fastcall InitializeEnemyScriptEntity_0040d830(int unused, EnemyScriptEntity_0040d830* entity, BindScriptName_0040d830 label) {
    // These adjacent words belong to the embedded instance's scratch state.
    int* scratch_words = &entity->instance.scratch_cursor;
    scratch_words[0] = 0;
    scratch_words[1] = 0;
    entity->vtable = &g_enemy_vtable_live;
    ClearBoundAnimations_0040d830(unused, reinterpret_cast<BindAnimationOwner_0040d830*>(&entity->payload));
    memset(&entity->payload, 0, sizeof(entity->payload));
    // The entity starts with its embedded instance as the only chain entry.
    entity->instance.Reset(entity, entity->instance.flags);
    entity->running = &entity->instance;
    int* name_slot = &entity->instance.name;
    name_slot[0] = -1;
    entity->self.instance = &entity->instance;
    entity->self.next = 0;
    entity->self.prev = 0;
    entity->payload.owner = entity;
    // Keep typed word views for the payload's six independently reset fields.
    int* field_11bc_slot = &entity->payload.field_11bc;
    field_11bc_slot[0] = 0;
    int* field_1208_slot = &entity->payload.field_1208;
    field_1208_slot[0] = 0;
    int* field_1244_slot = &entity->payload.field_1244;
    field_1244_slot[0] = 0;
    int* field_1280_slot = &entity->payload.field_1280;
    field_1280_slot[0] = 0;
    int* field_12bc_slot = &entity->payload.field_12bc;
    field_12bc_slot[0] = 0;
    int* field_12f8_slot = &entity->payload.field_12f8;
    field_12f8_slot[0] = 0;
    memset(entity->payload.snapshot_c, 0, sizeof(entity->payload.snapshot_c));
    memset(entity->payload.snapshot_b, 0, sizeof(entity->payload.snapshot_b));
    memset(entity->payload.snapshot_a, 0, sizeof(entity->payload.snapshot_a));
    entity->payload.bounds[0] = 24.0f;
    entity->payload.bounds[1] = 24.0f;
    entity->payload.bounds[2] = 24.0f;
    entity->payload.bounds[3] = 24.0f;
    int* identifier_slot = &entity->payload.identifier;
    identifier_slot[0] = -1;
    entity->payload.manager_link.owner = entity;
    entity->payload.manager_link.next = 0;
    entity->payload.manager_link.prev = 0;
    float* auxiliary_bounds = entity->payload.auxiliary_bounds;
    memset(auxiliary_bounds, 0, sizeof(entity->payload.auxiliary_bounds));
    auxiliary_bounds[14] = 32.0f;
    auxiliary_bounds[13] = 32.0f;
    entity->payload.timer.Reset();
    entity->payload.auxiliary_timer.Reset();
    entity->payload.second_auxiliary_timer.Reset();
    // Resolve the script in the active game's table and start at time zero.
    entity->table = g_enemy_ctrl->table;
    entity->running->instruction = reinterpret_cast<void*>(entity->table->Resolve(label.value));
    entity->running->timer = 0.0f;
    float* position = entity->payload.position;
    position[0] = 0.0f;
    position[1] = 0.0f;
    position[2] = 0.0f;
    entity->payload.markers[0].first = -1;
    entity->payload.markers[0].second = -1;
    entity->payload.markers[1].first = -1;
    entity->payload.markers[1].second = -1;
    entity->payload.markers[2].first = -1;
    entity->payload.markers[2].second = -1;
    entity->payload.markers[3].first = -1;
    entity->payload.markers[3].second = -1;
    entity->payload.markers[4].first = -1;
    entity->payload.markers[4].second = -1;
    entity->payload.markers[5].first = -1;
    entity->payload.markers[5].second = -1;
    entity->payload.markers[6].first = -1;
    entity->payload.markers[6].second = -1;
    entity->payload.markers[7].first = -1;
    entity->payload.markers[7].second = -1;
    entity->payload.markers[0].flags = 0;
    entity->payload.markers[1].flags = 0;
    entity->payload.markers[2].flags = 0;
    entity->payload.markers[3].flags = 0;
    entity->payload.markers[4].flags = 0;
    entity->payload.markers[5].flags = 0;
    entity->payload.markers[6].flags = 0;
    entity->payload.markers[7].flags = 0;
    return entity;
}
#pragma code_seg()
