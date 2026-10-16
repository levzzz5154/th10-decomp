// 0x004067A0..0x004067CB (44 bytes): the bullet manager's draw task
// (registered by 0x00405E20 at priority 0x1D): the per-frame slot advance.
//
// Retail enters with the owner in ECX (a plain __thiscall receiver), keeps it in
// EDI across the calls and leaves with a plain RET after returning 1.  The
// per-slot advance it reaches through a bare `call` takes the owner in EAX and
// the slot number in ECX - a register pair no declaration names - which the
// whole-program pass derives from that body at the bottom of this file.
extern "C" {
// 0x0044BC10: the signed-angle normaliser (stdcall, two floats, result in ST0).
float __stdcall Angle_NormalizeSum2(float value, float limit);
// 0x00491C10: the loaded animation manager pointer.
extern struct AnimationManager* g_sprt_ctrl;
}

struct Sprite2;
// 0x004451C0: the draw dispatcher (sprite in EAX, animation manager in ECX).
extern "C" __declspec(noinline) int __cdecl asm_FUN_004451c0_004451c0(
        Sprite2* sprite, AnimationManager* manager);

struct Enemy2;

struct SlotOwner {
    unsigned char pad_000[0x0014];
    Enemy2* slots[6];                 // +0x0014, indexed by the slot number
    __declspec(noinline) int AdvanceSlot(int index);
    __declspec(noinline) int OnDraw();
};

struct Vec310 {
    float x;
    float y;
    float z;
};

// Only the fields the slot walk touches; every offset is the retail one. The
// sprite the entity draws starts at +0x0008 and runs up to its own position.
struct Enemy2 {
    unsigned char pad_000[0x0034];
    float sprite_angle;                       // +0x0034
    unsigned char pad_038[0x033C - 0x0038];
    Vec310 sprite_position;            // +0x033C
    unsigned char pad_348[0x0364 - 0x0348];
    unsigned int sprite_flags;                // +0x0364
    unsigned char pad_368[0x03B4 - 0x0368];
    Vec310 position;                   // +0x03B4
    unsigned char pad_3C0[0x03E4 - 0x03C0];
    float heading;                            // +0x03E4
    unsigned char pad_3E8[0x044C - 0x03E8];
    Enemy2* next;                     // +0x044C
};

struct SlotState {
    unsigned char pad_000[0x0058];
    unsigned int flags;                       // +0x0058
};
extern "C" SlotState* g_game;

#pragma code_seg(".text$03run")
__declspec(noinline) int SlotOwner::OnDraw() {
    SlotState* state = g_game;
    if (!state || !(state->flags & 4)) {
        for (int index = 0; index < 6; ++index) AdvanceSlot(index);
    }
    return 1;
}
#pragma code_seg()

// 0x004066E0 (134 bytes): advance one slot's chain of entities.
//
// Each entity's sprite is moved to the entity position plus the playfield
// origin, turned to face along its heading when it asks for that, and handed
// to the draw dispatcher. The owner arrives in EAX and the slot number in ECX.
// The position is copied through pointers, which keeps the three stores in
// source order ahead of the flag test as retail has them.
#pragma code_seg(".text$01anchor")
__declspec(noinline) int SlotOwner::AdvanceSlot(int index) {
    Enemy2* entity = slots[index];
    while (entity) {
        Vec310* drawn = &entity->sprite_position;
        const Vec310* position = &entity->position;
        drawn->x = position->x + 224.0f;
        drawn->y = position->y + 16.0f;
        drawn->z = position->z;
        if (entity->sprite_flags & 0x08000000u) {
            entity->sprite_angle = Angle_NormalizeSum2(entity->heading, 1.5707964f);
            entity->sprite_flags |= 4;
        }
        asm_FUN_004451c0_004451c0((Sprite2*)((char*)entity + 8), g_sprt_ctrl);
        entity = entity->next;
    }
    return 1;
}
#pragma code_seg()
