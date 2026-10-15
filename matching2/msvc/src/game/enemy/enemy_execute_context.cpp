// Link context for the 0x0040E770 equivalent recovery: models of the helpers it
// calls and of a caller, so the checking LTCG link derives the same private
// register conventions as retail. Only Enemy::Execute_0040e770 is compared.
#include "th10/runtime/game/enemy/enemy_execute.hpp"

float data_00470b04 = 0.0f;
float data_00470b60 = -1.0f;
float g_game_speed = 1.0f;
int g_difficulty_00474c74;
int g_rank_00474c98;
Float3 g_zero_vector_00491c14;
Float2 g_zero_vector2_00491c20;
Float3 g_camera_offset_00491d7c;
RngState g_effect_rng_004918b0;
EnemyCtrl* g_enemy_ctrl;
BulletManager* g_bullet_manager;
LaserManager* g_laser_manager;
Gui* g_front;
Player* g_player;
Card* g_card;
RenderStageState g_application;
unsigned char data_00491e48[64], data_00491e08[64], data_00491dc8[64], data_00474df0[24];
ScoreState g_globals;
SoundQueue g_sound_manager;
extern "C" void* g_sprt_ctrl;
extern "C" void* g_item_manager;
extern "C" int data_00474c84, data_00474c8c;
extern "C" short g_sound_priority[];
extern "C" Float3 g_offset_point_00497d80;
extern "C" unsigned int g_offset_point_state_00497d8c;

extern "C" void* __cdecl ext_new(unsigned int size);
extern "C" void __stdcall ext_call(void* a, int b);
extern "C" void* __fastcall ext_find(void* context, int id);
extern "C" void* __fastcall ext_find_node(void* value, void* manager, int unused);
extern "C" void* __fastcall ext_set_flag(void* manager, void* context, int id);
extern "C" void* __cdecl ext_alloc_vm(void* manager);
extern "C" AnmHandle* __cdecl ext_register(int which, void* manager, AnmHandle* out, void* vm);
extern "C" int __stdcall ext_init_sprite(void* anm, void* vm, int script);
extern "C" void __stdcall ext_spawn_item(void* manager, const void* position, int kind, int a, float angle, float speed);
extern "C" void __stdcall ext_scatter(const void* position, ItemDrops* drops);
extern "C" unsigned char* __stdcall ext_construct(void* memory, const char* name);
extern "C" int __stdcall ext_laser(void* laser, const void* params);
extern "C" void __stdcall ext_configure(void* owner, int priority, int mode, int a, int b, int c, int d);
extern "C" int __stdcall ext_shoot(void* manager, int i, int j, float angle);
extern "C" void* g_background;
extern "C" int __fastcall ext_fc_spawn(const void* position, int kind, int a, float angle, float speed);
extern "C" int __fastcall ext_outside(const void* position, int unused, float x, float y);
extern "C" void* __stdcall ext_display(void* memory, const char* table);

// ---- ECL operand helpers (as in the 0x0044E1A0 recovery's context) ----
float EclVm::FloatValue(int selector, EclVm* vm, float value) {
    unsigned short mask = vm->instr->mask;
    if (mask & (1 << selector)) {
        if (value >= data_00470b04) {
            return *(float*)&vm->stack.data[vm->stack.base + (int)value];
        } else if (value == data_00470b60) {
            vm->stack.PopFloat(&value);
        } else {
            return vm->owner->ResolveFloat((int)value);
        }
    }
    return value;
}
int EclVm::IntOperand(int selector) {
    EclInstr* table = instr;
    unsigned short mask = table->mask;
    if ((mask & (1 << selector)) != 0) {
        int value = table->i[selector];
        if (value >= 0) {
            return *(int*)&stack.data[stack.base + value];
        } else if (value == -1) {
            int o;
            if (stack.sp - 4 >= 0) {
                stack.sp -= 4; o = stack.sp;
                selector = *(int*)&stack.data[o];
                stack.sp -= 4; o = stack.sp;
                if (stack.data[o] == 'f') return (int)*(float*)&selector;
            }
            return selector;
        } else {
            return owner->ResolveInt(value);
        }
    }
    return table->i[selector];
}
int EclVm::IntValue(int selector, int value) {
    if ((instr->mask & (1 << selector)) != 0) {
        if (value >= 0) {
            EclStack* s = &stack;
            return *(int*)&s->data[s->base + value];
        } else if (value == -1) {
            stack.PopInt(&value);
            return value;
        } else {
            return owner->ResolveInt(value);
        }
    }
    return value;
}
float* EclVm::FloatDest(int index) {
    if (instr->mask & (1 << index)) {
        const float& displacement = instr->f[index];
        if (displacement >= 0.0f) {
            EclStack* frame = &this->stack;
            return (float*)((char*)frame + frame->base + (int)displacement);
        }
        return owner->ResolveFloatDest((int)displacement);
    }
    return 0;
}
float EclVm::FloatOperand(int selector) {
    EclInstr* operands = instr;
    unsigned short mask = operands->mask;
    if (mask & (1 << selector)) {
        const float& d = operands->f[selector];
        if (d >= data_00470b04) {
            return *(float*)&stack.data[stack.base + (int)d];
        } else if (d == data_00470b60) {
            union { int integer; float real; } value;
            if (stack.sp - 4 >= 0) {
                stack.sp -= 4;
                value.integer = *(int*)&stack.data[stack.sp];
                stack.sp -= 4;
                char tag = stack.data[stack.sp];
                if (tag == 'f') return value.real;
                if (tag == 'i') return (float)value.integer;
            }
            return value.real;
        } else {
            return owner->ResolveFloat((int)d);
        }
    }
    return operands->f[selector];
}
float Enemy::FloatValue_00412aa0(int selector, float value) {
    EnemyFull* slot = ecl;
    return EclVm::FloatValue(selector, slot->active, value);
}
int Enemy::IntArg_00412a00(int selector) { return Int(selector); }
int* Enemy::IntDest_00412a10(int index) {
    EclVm* vm = ecl->active;
    EclInstr* table = vm->instr;
    if (table->mask & (1 << index)) {
        const int& displacement = table->i[index];
        if (displacement >= 0) {
            EclStack* frame = &vm->stack;
            return (int*)((char*)frame + frame->base + displacement);
        }
        return vm->owner->ResolveIntDest(displacement);
    }
    return 0;
}

// ---- timers, angles, random numbers ----
void FrameTimer::Set_00405410(int value) {
    if (!(flags & 1)) {
        current = 0;
        previous = 0xFFF0BDC1;
        elapsed = 0.0f;
        speed = &g_game_speed;
        flags |= 1;
    }
    current = value;
    previous = value - 1;
    elapsed = (float)value;
}
static __forceinline void RestartTimer(FrameTimer* timer) {
    if (!(timer->flags & 1u)) {
        timer->current = 0;
        timer->previous = -999999;
        timer->elapsed = 0;
        timer->speed = &g_game_speed;
        timer->flags |= 1u;
    }
    timer->current = 0;
    timer->elapsed = 0;
    timer->previous = -1;
}
void Float3Interp::Restart_004050d0() { RestartTimer(&timer); }
void Float2Interp::Restart_00412db0() { RestartTimer(&timer); }
static __forceinline unsigned short NextWord(RngState* s) {
    unsigned short value = s->seed ^ 0x9630;
    value -= 0x6553;
    s->seed = (value >> 14) + (value << 2);
    ++s->generation;
    return s->seed;
}
float RngState::NextFloatSigned_0044bb90() {
    unsigned short high = NextWord(this);
    unsigned short low = NextWord(this);
    return ((unsigned int)high << 16 | low) * (1.0f / 2147483648.0f) - 1.0f;
}

// ---- animations ----
void AnmHandle::Release_00449630() {
    ext_set_flag(0, g_sprt_ctrl, id);
    id = 0;
}
struct AnmNode {
    AnmNode* field_000;
    AnmNode* field_004;
    unsigned char pad_008[0x0C];
    AnmNode* field_014;
    AnmNode* field_018;
    unsigned char pad_01c[0x340];
    unsigned int flags_35c;
};
void AnmHandle::Show_004495e0() {
    AnmNode* node = (AnmNode*)ext_find_node((void*)id, g_sprt_ctrl, id);
    if (node == 0) return;
    node->flags_35c &= ~2u;
    if (node->field_018 != 0) return;
    for (AnmNode* child = node->field_014; child != 0; child = child->field_004) child->field_000->flags_35c &= ~2u;
}
void AnmHandle::Hide_00449590() {
    AnmNode* node = (AnmNode*)ext_find_node((void*)id, g_sprt_ctrl, id);
    if (node == 0) return;
    node->flags_35c |= 2;
    if (node->field_018 != 0) return;
    for (AnmNode* child = node->field_014; child != 0; child = child->field_004) child->field_000->flags_35c |= 2;
}
#define CREATE(name, which) \
    AnmHandle* __stdcall name(AnmLoaded* anm, AnmHandle* out, int script, int layer) { \
        unsigned char* vm = (unsigned char*)ext_alloc_vm(g_sprt_ctrl); \
        unsigned int flags = *(unsigned int*)(vm + 0x35C); \
        *(int*)(vm + 0x20) = layer; \
        *(unsigned int*)(vm + 0x35C) = flags | 0x40000000u; \
        ext_init_sprite(anm, vm, script); \
        ext_register(which, g_sprt_ctrl, out, vm); \
        return out; \
    }
CREATE(Anm_CreateBack_00448d00, 0)
CREATE(Anm_CreateFront_00448e30, 1)
AnmVm* __stdcall Anm_Resolve_00449450(AnmHandle* handle) {
    AnmVm* vm = (AnmVm*)ext_find(g_sprt_ctrl, handle->id);
    if (vm == 0) handle->id = 0;
    return vm;
}
Float3* __stdcall OffsetPoint_00418810(const Float3* point) {
    if (!(g_offset_point_state_00497d8c & 1)) g_offset_point_state_00497d8c |= 1;
    g_offset_point_00497d80.x = point->x + 224.0f;
    g_offset_point_00497d80.y = point->y + 16.0f;
    g_offset_point_00497d80.z = point->z;
    return &g_offset_point_00497d80;
}
struct RigCamera { __declspec(noinline) void Apply(); };
void RigCamera::Apply() {
    unsigned char* self = (unsigned char*)this;
    if (g_sprt_ctrl) ((AnmHandle*)g_sprt_ctrl)->Release_00449630();
    ext_call(self + 0x4C, (int)(self + 0x18));
    ext_call(self + 0x8C, *(int*)(self + 0x48));
    ext_call(self + 0x30, (int)(self + 0x0C));
    if (g_sprt_ctrl) {
        ((int*)g_sprt_ctrl)[0x5C / 4] = *(int*)(self + 0xE8);
        ((int*)g_sprt_ctrl)[0x60 / 4] = *(int*)(self + 0xEC);
    }
}
struct RigDevice { void** vtable; };
void RenderStageState::SelectStage_00401d20(int index) {
    unsigned char* self = (unsigned char*)this;
    *(unsigned char**)(self + 0x384) = self + 0x154 + index * 0x118;
    (*(RigCamera**)(self + 0x384))->Apply();
    typedef long (__stdcall *Viewport)(void*, void*);
    RigDevice* device = *(RigDevice**)(self + 8);
    ((Viewport)device->vtable[0xBC / 4])(device, *(unsigned char**)(self + 0x384) + 0xCC);
    *(int*)(self + 0x388) = index;
}

// ---- enemies, items ----
EnemyFull* __stdcall EnemyCtrl_Spawn_0040cfb0(const EnemySpawn* p, EnemyCtrl* manager, const char* name) {
    void* memory = ext_new(0x2518);
    unsigned char* enemy = memory ? ext_construct(memory, name) : 0;
    *(Float3*)(enemy + 0x1094) = p->position;
    *(int*)(enemy + 0x23F8) = p->score;
    *(int*)(enemy + 0x23FC) = p->life;
    *(int*)(enemy + 0x2408) = p->item;
    *(unsigned int*)(enemy + 0x2480) ^= ((p->mirrored << 11) ^ *(unsigned int*)(enemy + 0x2480)) & 0x800;
    enemy[0x1024] = 1 << g_difficulty_00474c74;
    memcpy(enemy + 0x1138, p->variables, 32);
    if (!(*(unsigned int*)(enemy + 0x2468) & 1)) {
        *(int*)(enemy + 0x245C) = 0;
        *(int*)(enemy + 0x2458) = -999999;
        *(float*)(enemy + 0x2460) = 0.0f;
        *(float**)(enemy + 0x2464) = &g_game_speed;
        *(unsigned int*)(enemy + 0x2468) |= 1;
    }
    *(int*)(enemy + 0x245C) = 2;
    *(float*)(enemy + 0x2460) = 2.0f;
    *(int*)(enemy + 0x2458) = 1;
    *(unsigned int*)(enemy + 0x2480) ^= ((p->flags << 18) ^ *(unsigned int*)(enemy + 0x2480)) & 0x40000;
    ext_call(enemy + 0x103C, 0);
    if (*(unsigned int*)(enemy + 0x2480) & 0x8000) {
        int item = *(int*)(enemy + 0x2408);
        if (item == 1) item = 10;
        else if (item == 4) item = 11;
        *(int*)(enemy + 0x2408) = item;
    }
    *(int*)(enemy + 0x2444) = (*(int*)((char*)manager + 0x64) & 1) + 2;
    *(int*)(enemy + 0x2448) = 0x167;
    if (*(int*)(enemy + 0x1128) == 1) {
        switch (*(int*)(enemy + 0x112C)) {
        case 0: case 20: case 49: *(int*)(enemy + 0x2448) = 0x167; break;
        case 5: case 25: case 50: *(int*)(enemy + 0x2448) = 0x164; break;
        case 15: case 35: case 52: *(int*)(enemy + 0x2448) = 0x16D; break;
        case 10: case 30: case 51: *(int*)(enemy + 0x2448) = 0x16A; break;
        }
    }
    // Stand-in for retail reusing EBX after the parameters are consumed.
    if (*(int*)(enemy + 0x2444) == 99) g_sound_manager.QueuePan_0043dd10(*(int*)(enemy + 0x2448), 0.0f);
    *(int*)(enemy + 0x244C) = 0;
    void** node = (void**)(enemy + 0x116C);
    void*** first = (void***)((char*)manager + 0x58);
    void*** last = (void***)((char*)manager + 0x5C);
    if (*first == 0) {
        *first = node;
    } else {
        void** tail = *last;
        if (tail[1]) {
            node[1] = tail[1];
            ((void**)tail[1])[2] = node;
        }
        tail[1] = node;
        node[2] = tail;
    }
    *last = node;
    ++*(int*)((char*)manager + 0x60);
    ++*(int*)((char*)manager + 0x64);
    return (EnemyFull*)enemy;
}
void __stdcall EnemyCtrl_SweepDeaths_0040e6a0(EnemyCtrl* manager) {
    void** next;
    for (void** node = *(void***)((char*)manager + 0x58); node; node = next) {
        unsigned char* enemy = (unsigned char*)node[0];
        next = (void**)node[1];
        unsigned int flags = *(unsigned int*)(enemy + 0x2480);
        if (((flags & 0x50) || (flags & 0xC000)) && !(flags & 0x80)) continue;
        if (*(int*)(enemy + 0x2448) >= 0) {
            AnmHandle burst;
            ext_register(*(int*)(enemy + 0x2448), g_enemy_ctrl->anm[*(int*)(enemy + 0x244C)], &burst, enemy + 0x1068);
        }
        *(unsigned int*)(enemy + 0x2480) |= 0x20000;
    }
    FrameTimer* clock = (FrameTimer*)((char*)manager + 0x68);
    ext_call(clock, 0);
}
void __stdcall Enemy_BindSlot_00412720(EnemyFull* enemy, int index, int id, int value, const char* data) {
    enemy->body.slots[index].id = id;
    if (id >= 0) {
        enemy->body.slots[index].value = value;
        enemy->body.slots[index].begin = data;
        enemy->body.slots[index].cursor = data;
    }
}
__declspec(noinline) void __stdcall Rig_Scatter(const Float3* position, ItemDrops* drops) {
    ext_call(&drops, 0);
    float angle = (float)ext_laser(&g_effect_rng_004918b0, 0) * 3.1415927f;
    for (int kind = 0; kind < 11; ++kind) {
        for (int i = 0; i < drops->items[kind + 1]; ++i) {
            Float3 target;
            target.x = position->x + angle * drops->spread_x;
            target.y = position->y + angle * drops->spread_y;
            target.z = position->z;
            ext_spawn_item(g_item_manager, &target, kind + 1, -1, -1.5707964f, 2.2f);
            angle = Angle_Normalize(angle + 1.5707964f);
        }
    }
    memset(&drops->items[1], 0, 44);
}
void __stdcall Drops_Flush_0040c9a0(const Float3* position, ItemDrops* drops) {
    if (drops->items[0] > 0) ext_spawn_item(g_item_manager, position, drops->items[0], -1, -1.5707964f, 2.2f);
    Rig_Scatter(position, drops);
    drops->items[0] = 0;
}

// ---- bullets, lasers ----
int Shooter::Shoot_004073e0(BulletManager* manager) {
    float dx = g_player->position.x - position.x;
    float dy = g_player->position.y - position.y;
    float angle;
    if (dy == 0.0f && dx == 0.0f) angle = 1.5707964f;
    else angle = (float)atan2(dy, dx);
    for (int j = 0; j < count_2; ++j) {
        for (int i = 0; i < count_1; ++i) {
            if (ext_shoot(manager, i, j, angle)) goto done;
        }
    }
done:
    if (flags & 0x400) ((RigCamera*)g_player)->Apply();
    if (flags & 0x200) g_sound_manager.QueuePan_0043dd10(sound, position.x);
    return 0;
}
int BulletManager::Sweep_00408210(int convert) {
    unsigned char* self = (unsigned char*)this;
    Float3 half(*(float*)(self + 0x50) * 0.5f, *(float*)(self + 0x54) * 0.5f, *(float*)(self + 0x58) * 0.5f);
    Float3 low(*(float*)(self + 0x44) - half.x, *(float*)(self + 0x48) - half.y, *(float*)(self + 0x4C) - half.z);
    half.x = half.x + *(float*)(self + 0x44);
    half.y = half.y + *(float*)(self + 0x48);
    half.z = half.z + *(float*)(self + 0x4C);
    unsigned char* record = self + 0x60;
    for (int remaining = 2000; remaining != 0; --remaining, record += 0x7F0) {
        short state = *(short*)(record + 0x446);
        if (state == 0 || state == 3) continue;
        Float3* position = (Float3*)(record + 0x3B4);
        float half_w = *(float*)(record + 0x3F0) * 0.5f;
        float left = position->x - half_w;
        float half_h = *(float*)(record + 0x3F4) * 0.5f;
        float top = position->y - half_h;
        float right = half_w + position->x;
        float bottom = half_h + position->y;
        if (right > low.x && left < half.x && bottom > low.y && top < half.y) {
            *(int*)record |= 8;
            if (convert) ((RigCamera*)position)->Apply();
            AnmHandle handle;
            ext_register(0x173, *(void**)(self + 0x3E0B50), &handle, &low);
            unsigned char* vm = (unsigned char*)ext_find(g_sprt_ctrl, handle.id);
            unsigned char* shape = *(unsigned char**)(record + 0x39C);
            if (shape) *(int*)(vm + 0x2FC) = g_sound_priority[*(short*)(record + 0x7EC)];
            *(int*)(record + 0x450) = 0;
        }
    }
    return 0;
}
extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)
struct RigDisplacement : Float3 {
    RigDisplacement(float px, float py, float pz) { x = px; y = py; z = pz; }
};
struct RigRecord {
    int flags;
    int countdown;              // +0x004
    unsigned char reserved_008[0x3B4 - 8];
    Float3 position;            // +0x3B4
    unsigned char reserved_3c0[0x3F0 - 0x3C0];
    float diameter;             // +0x3F0
    unsigned char reserved_3f4[0x446 - 0x3F4];
    short state;                // +0x446
    unsigned char reserved_448[0x7F0 - 0x448];
};
int BulletManager::Check_00408100(const Float3* point, float radius, int spawn_item, int filter) {
    RigRecord* record = (RigRecord*)((unsigned char*)this + 0x60);
    int remaining = 2000;
    do {
        if (record->state != 0 && record->state != 3 && (!filter || !record->countdown)) {
            Float3 displacement = RigDisplacement(record->position.x - point->x, record->position.y - point->y,
                                                  record->position.z - point->z);
            float diameter = record->diameter;
            _ReadWriteBarrier();
            float combined = diameter * 0.5f + radius;
            float distance = displacement.x * displacement.x + displacement.y * displacement.y;
            if (!(distance > combined * combined)) {
                ((AnmHandle*)record)->Release_00449630();
                if (!ext_outside(&record->position, 0, 2.0f, 2.0f) && spawn_item)
                    ext_fc_spawn(&record->position, 8, -1, -1.5707964f, 0.6f);
            }
        }
        ++record;
    } while (--remaining);
    return 0;
}
struct LaserNode {
    virtual void unused_00() = 0;
    virtual void unused_04() = 0;
    virtual void unused_08() = 0;
    virtual void unused_0c() = 0;
    virtual void unused_10() = 0;
    virtual void Release(int value) = 0;
    virtual void unused_18() = 0;
    virtual int Evaluate(const float* vector, float value, int flag) = 0;
    unsigned char reserved_004[4];
    LaserNode* next;            // +0x08
    int kind;                   // +0x0C
    unsigned char reserved_010[0x40];
    unsigned char marked;       // +0x50
    int id;                     // +0x54
};
struct LaserList {
    unsigned char reserved_000[0x18];
    LaserNode* head;            // +0x18
    unsigned char reserved_01c[0x440 - 0x1C];
    Float3 vector;              // +0x440
    int count;                  // +0x44C
    int next_id;                // +0x450
};
int LaserManager::Cleanup_0041c850(int value) {
    LaserNode* node = ((LaserList*)this)->head;
    while (node != 0) {
        LaserNode* next = node->next;
        if (node->kind != 1) node->Release(value);
        node = next;
    }
    return 1;
}
Laser* LaserManager::FindById_0040cf90(int id) {
    LaserNode* node = ((LaserList*)this)->head;
    while (node != 0) {
        if (node->id == id) return (Laser*)node;
        node = node->next;
    }
    return 0;
}
int LaserManager::Evaluate_0041c800(const Float3* point, float radius, int flag) {
    LaserNode* record = ((LaserList*)this)->head;
    ((LaserList*)this)->vector = *point;
    int total = 0;
    while (record != 0) {
        LaserNode* next = record->next;
        if (record->kind != 1) total += record->Evaluate(&point->x, radius, flag);
        record = next;
    }
    return total;
}
int LaserManager::MarkEligible_0041c7d0() {
    LaserNode* record = ((LaserList*)this)->head;
    while (record != 0) {
        LaserNode* next = record->next;
        if (record->kind != 1 && record->marked == 0) record->marked = 1;
        record = next;
    }
    return 0;
}
void Laser::SetVector_0040cf60(const Float3& value) { f430 = value; }
// Stand-in for the laser constructors, which take the fresh memory in EBX.
__declspec(noinline) void* __stdcall Rig_LaserConstruct(void* memory) {
    ((AnmHandle*)((char*)memory + 8))->Release_00449630();
    ((RigCamera*)((char*)memory + 0x10))->Apply();
    *(int*)memory = 1;
    return memory;
}
__declspec(noinline) void* __stdcall Rig_LaserConstruct2(void* memory) {
    ((AnmHandle*)((char*)memory + 0xC))->Release_00449630();
    ((RigCamera*)((char*)memory + 0x20))->Apply();
    *(int*)memory = 2;
    return memory;
}
struct RigLaserBase { virtual void V0() = 0; virtual int Init(const void* params) = 0; };
static __forceinline void Rig_LinkLaser(int* list, int* laser) {
    laser[0x54 / 4] = list[0x43C / 4];
    int* tail = (int*)list[0x434 / 4];
    laser[1] = (int)tail;
    tail[2] = (int)laser;
    ++list[0x438 / 4];
    list[0x434 / 4] = (int)laser;
}
int LaserManager::Spawn_0041c510(const LaserParams* params, int kind) {
    int* list = (int*)this;
    if (list[0x438 / 4] >= 256) return 0;
    if (++list[0x43C / 4] == 0) list[0x43C / 4] = 1;
    switch (kind) {
    case 0: {
        void* line = ext_new(0xD58);
        int* laser = line ? (int*)Rig_LaserConstruct(line) : 0;
        Rig_LinkLaser(list, laser);
        ((RigLaserBase*)laser)->Init(params);
        break;
    }
    case 1: {
        void* beam = ext_new(0xD74);
        int* laser = beam ? (int*)Rig_LaserConstruct2(beam) : 0;
        Rig_LinkLaser(list, laser);
        ((RigLaserBase*)laser)->Init(params);
        break;
    }
    }
    return list[0x43C / 4];
}
BeamLaserParams* BeamLaserParams::Construct_0040cf40() {
    int* fields = (int*)this;
    for (int index = 0; index < 0x7E; ++index) fields[index] = 0;
    fields[0x0B] = 0x41000000;
    return this;
}

// ---- interface, sound, spell cards ----
void Gui::CreateScoreDisplay_00415db0(int stage) {
    unsigned char* self = (unsigned char*)this;
    void* memory = ext_new(0x1C);
    int* display = (int*)(memory ? ext_display(memory, *(char**)(self + 0x9EC0) + stage * 8) : 0);
    *(int**)(self + 0x9EB8) = display;
    display[1] = stage;
    int next = stage + 1;
    int previous = data_00474c84;
    data_00474c84 = next;
    if (previous != next) data_00474c8c = 0;
}
void SoundQueue::QueuePan_0043dd10(int sound, float pan) {
    int* self = (int*)this;
    int priority = g_sound_priority[sound * 4];
    int request = int(pan * (1000.0f / 192.0f));
    int slot;
    for (slot = 0; slot < 12; ++slot) {
        if (self[0x188 + slot] < 0) break;
        if (self[0x188 + slot] == sound) {
            int count = self[0x194 + slot];
            if (count < 128) {
                self[0x1A0 + slot * 128 + count] = request;
                ++self[0x194 + slot];
            }
            return;
        }
    }
    if (slot < 12) {
        self[0x188 + slot] = sound;
        self[0x102 + sound] = priority;
        self[0x1A0 + slot * 128] = request;
        ++self[0x194 + slot];
    }
}
struct RigEffect {
    unsigned int f[17];
    __declspec(noinline) void Configure(int priority, int mode, int a, int b, int c, int d);
};
void RigEffect::Configure(int priority, int mode, int a, int b, int c, int d) {
    switch (mode) {
    case 0: f[2] = (unsigned int)ext_find(this, 14); f[3] = (unsigned int)ext_find(this, priority); break;
    case 1: f[2] = (unsigned int)ext_find(this, 15); break;
    case 2: f[2] = (unsigned int)ext_find(this, 16); f[3] = (unsigned int)ext_find(this, priority); break;
    case 3: f[6] = 255; f[2] = (unsigned int)ext_find(this, 17); f[3] = (unsigned int)ext_find(this, priority); break;
    case 4: f[2] = (unsigned int)ext_find(this, 18); f[3] = (unsigned int)ext_find(this, priority); break;
    }
    f[4] = mode; f[7] = a; f[8] = b; f[9] = c; f[10] = d;
}
void* __stdcall Screen_Create(int priority, int mode, int a, int b, int c, int d) {
    RigEffect* owner = (RigEffect*)ext_new(0x44);
    if (owner) {
        owner->f[16] &= ~1u;
        memset(owner, 0, 0x44);
        owner->f[0] |= 2u;
        owner->Configure(priority, mode, a, b, c, d);
    }
    return owner;
}
void __stdcall Score_SetMode_00412ed0(ScoreState* state, int mode) {
    int* self = (int*)state;
    if (self[0x11] != mode) self[0x13] = 0;
    self[0x11] = mode;
}
__declspec(noinline) void __stdcall Rig_StopAtFrame1(AnmHandle* handle) {
    if (handle->id) {
        unsigned char* vm = (unsigned char*)ext_find(g_sprt_ctrl, handle->id);
        if (vm) { *(int*)(vm + 0x2C) = 1; *(short*)(vm + 0x30) = 1; }
        else handle->id = 0;
    }
}
void Card::End_00409c00() {
    unsigned char* self = (unsigned char*)this;
    if (flags & 1) {
        *(unsigned int*)((unsigned char*)g_background + 0x2A18) |= 1;
        Rig_StopAtFrame1((AnmHandle*)(self + 0x768));
        Rig_StopAtFrame1((AnmHandle*)(self + 0x76C));
        Rig_StopAtFrame1((AnmHandle*)(self + 0x770));
        flags &= ~1u;
        ext_set_flag(0, g_sprt_ctrl, *(int*)(self + 0x774));
        *(int*)(self + 0x774) = 0;
        if (flags & 2) {
            g_globals.fields[1] += *(int*)(self + 0x3790) / 10;
            if (g_globals.fields[1] >= 1000000000) g_globals.fields[1] = 999999999;
            ext_call(g_front, *(int*)(self + 0x3790));
            ext_call(&g_sound_manager, 0x2D);
        } else {
            AnmHandle* caption = (AnmHandle*)((unsigned char*)g_front + 0x9E14);
            ext_set_flag(0, g_sprt_ctrl, caption->id);
            caption->id = 0;
            AnmHandle out;
            caption->id = Anm_CreateBack_00448d00(*(AnmLoaded**)((unsigned char*)g_front + 0x9EC8), &out, 0x48, 0xF)->id;
        }
    }
}
void Card::StopAnimation_0040cea0() {
    flags |= 0x10;
    const int handle = *(int*)((unsigned char*)this + 0x774);
    ext_set_flag(0, g_sprt_ctrl, handle);
    *(int*)((unsigned char*)this + 0x774) = 0;
}
void __stdcall Card_Start_00409280(Card* card, int id, const char* name, int time, int unused) {
    // The arguments stay on the stack, as in the original.
    ext_call(&card, (int)&id);
    unsigned char* self = (unsigned char*)card;
    FrameTimer* timer = (FrameTimer*)(self + 0x3734);
    timer->Set_00405410(0);
    *(int*)(self + 0x3750) = id;
    *(int*)(self + 0x3754) = time;
    ext_call(self, (int)name);
    card->flags |= 1;
}

extern "C" unsigned int __security_cookie = 0xBB40E64E;
extern "C" void __fastcall __security_check_cookie(unsigned int cookie) {
    if (cookie != __security_cookie) ext_call(0, 0);
}

extern "C" int __stdcall RigEntry(Enemy** enemies, int count) {
    int total = 0;
    for (int i = 0; i < count; ++i) total += enemies[i]->Execute_0040e770();
    // These globals' addresses escape in the whole program.
    ext_call(&g_rank_00474c98, 0);
    ext_call(&g_difficulty_00474c74, 0);
    Card** cards = (Card**)enemies;
    int n = count;
    while (n--) (*cards++)->End_00409c00();
    Drops_Flush_0040c9a0((Float3*)enemies[0], (ItemDrops*)enemies[1]);
    EnemyCtrl_SweepDeaths_0040e6a0((EnemyCtrl*)enemies[3]);
    Screen_Create(43, 5, 60, 0, 0, 0);
    g_bullet_manager->Sweep_00408210(count);
    ((RigCamera*)enemies[2])->Apply();
    return total;
}
