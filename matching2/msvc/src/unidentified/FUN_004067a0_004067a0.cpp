// 0x004067A0..0x004067CB (44 bytes): the per-frame animation-slot advance.
//
// Retail enters with the owner in ECX (a plain __thiscall receiver), keeps it in
// EDI across the calls and leaves with a plain RET after returning 1.  The
// per-slot advance it reaches through a bare `call` takes the owner in EAX and
// the slot number in ECX - a register pair no declaration names - so that
// callee is compiled into this same link as an ABI anchor (bottom of this file)
// and the whole-program pass derives the pair from that body, and the caller's
// own home from the registers that body clobbers.
extern "C" {
// 0x0044BC10: the signed-angle normaliser (stdcall, two floats, result in ST0).
float __stdcall Angle_NormalizeSum_0044bc10(float value, float limit);
// 0x004451C0: the per-entity animation dispatch.
void __fastcall DispatchAnm_004451c0(void* manager, void* object);
// 0x00491C10: the loaded animation manager pointer.
extern void* data_00491c10;
}

struct Enemy_004067a0;

struct SlotOwner_004067a0 {
    unsigned char pad_000[0x0014];
    Enemy_004067a0* slots[6];                 // +0x0014, indexed by the slot number
    __declspec(noinline) int AdvanceSlot(int index);
    __declspec(noinline) int AdvanceAllSlots();
};

// Only the fields the slot walk touches; every offset is the retail one.
struct Enemy_004067a0 {
    unsigned char pad_000[0x0034];
    float angle;                              // +0x0034
    unsigned char pad_038[0x033C - 0x0038];
    float motion_x;                           // +0x033C
    float motion_y;                           // +0x0340
    int motion_z;                             // +0x0344
    unsigned char pad_348[0x0364 - 0x0348];
    unsigned int flags;                       // +0x0364
    unsigned char pad_368[0x03B4 - 0x0368];
    float source_x;                           // +0x03B4
    float source_y;                           // +0x03B8
    int source_z;                             // +0x03BC
    unsigned char pad_3C0[0x03E4 - 0x03C0];
    float spin;                               // +0x03E4
    unsigned char pad_3E8[0x044C - 0x03E8];
    Enemy_004067a0* next;                     // +0x044C
};

struct SlotState_004067a0 {
    unsigned char pad_000[0x0058];
    unsigned int flags;                       // +0x0058
};
extern "C" SlotState_004067a0* data_00477810;

#pragma code_seg(".text$03run")
__declspec(noinline) int SlotOwner_004067a0::AdvanceAllSlots() {
    SlotState_004067a0* state = data_00477810;
    if (!state || !(state->flags & 4)) {
        for (int index = 0; index < 6; ++index) AdvanceSlot(index);
    }
    return 1;
}
#pragma code_seg()

// ABI anchor for 0x004066E0.  This body is not recovered game code: the layout
// places it at the retail address so the bare `call` above bakes retail's own
// displacement, and export_bodies never selects it.  What it earns is the
// argument pair the caller above must use, and - through the registers it
// clobbers in the loop - the caller's own live-across-call homes.
#pragma code_seg(".text$01anchor")
__declspec(noinline) int SlotOwner_004067a0::AdvanceSlot(int index) {
    Enemy_004067a0* entity = slots[index];
    while (entity) {
        entity->motion_x = entity->source_x + 224.0f;
        entity->motion_y = entity->source_y + 16.0f;
        entity->motion_z = entity->source_z;
        if (entity->flags & 0x08000000u) {
            entity->angle = Angle_NormalizeSum_0044bc10(entity->spin, 1.5707963f);
            entity->flags |= 4;
        }
        DispatchAnm_004451c0(data_00491c10, (char*)entity + 8);
        entity = entity->next;
    }
    return 1;
}
#pragma code_seg()
