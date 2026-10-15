// Compiler context only: stand-in bodies for the private-ABI callees the
// manager-state teardown reaches, placed at their retail addresses and never
// exported as recovered code. Each keeps the receiver/argument register
// behavior of the real retail body, so the whole-program pass hands the
// callee the register retail uses (score archive in EBX, game thread in ESI,
// position record in EDI, enemy manager and score record in EAX, registrar
// in EAX with the name in EDX, side panel in EBX).
#include "th10/game/score.hpp"
#include "th10/render/resource_registrar_0043e460.hpp"

extern "C" void __cdecl SidePanelReleaseBarrier(void* value);
extern "C" void __cdecl entry_free_00452422(void* memory);
void __cdecl operator delete(void* memory);

extern "C" unsigned int data_00474ca0;
extern "C" void* g_sprt_ctrl;

// The twelve-byte position record handed to the animation manager; identical
// to the definition in the positioned-primary recovery.
struct AnimationPosition_00448d50 {
    float x;
    float y;
    float z;
};

// The animation object the positioned-primary creation fills in.
struct AnimationObject_00448d50 {
    unsigned char reserved_000[0x20];
    int render_bucket_020;                          // +0x20
    unsigned char reserved_024[0x340 - 0x24];
    AnimationPosition_00448d50 position_340;        // +0x340
    unsigned char reserved_34c[0x35C - 0x34C];
    unsigned int flags_035c;                        // +0x35C
};

extern "C" void* __cdecl asm_FUN_00449950_00449950(void* manager);
extern "C" void __cdecl asm_AnimationObject_LoadScript_0043e710(
    void* resource, void* object, int index);
extern "C" void** __cdecl asm_AnimationManager_RegisterPrimaryBack_004489d0(
    void* manager, void** out, void* entity);

// A loaded animation file.
struct PanelResource_00447810 {
    __declspec(noinline) void Release();
};

// The animation manager's stage-owned file slot.
struct PanelAnimationManager_00414570 {
    unsigned char reserved_000000[0x3AD0DC];
    PanelResource_00447810* stage_resource;         // +0x3AD0DC
};

// The side panel's stage-owned parts.
struct PanelSlot_004136c0 {
    __declspec(noinline) void Release();
};

struct FrontStagePartsView {
    unsigned char reserved_0000[0x9E80];
    int stage_state;                                // +0x9E80
    unsigned char reserved_9e84[0x9EB8 - 0x9E84];
    PanelSlot_004136c0* stage_slot;                 // +0x9EB8
    void* stage_buffer;                             // +0x9EBC
    __declspec(noinline) void ReleaseStageParts();
};

#pragma code_seg(".text$03slot")
void PanelSlot_004136c0::Release() {
    SidePanelReleaseBarrier(this);
    SidePanelReleaseBarrier(this);
}
#pragma code_seg(".text$8resource")
void PanelResource_00447810::Release() {
    void** entry = reinterpret_cast<void**>(this);
    do {
        SidePanelReleaseBarrier(*entry);
        ++entry;
    } while (*entry);
    SidePanelReleaseBarrier(this);
}
#pragma code_seg(".text$04panel")
void FrontStagePartsView::ReleaseStageParts() {
    PanelSlot_004136c0* slot = stage_slot;
    if (slot) {
        slot->Release();
        operator delete(slot);
        stage_slot = 0;
    }
    if (data_00474ca0 & 9)
        return;
    PanelResource_00447810** resource =
        &reinterpret_cast<PanelAnimationManager_00414570*>(g_sprt_ctrl)->stage_resource;
    if (*resource) {
        (*resource)->Release();
        operator delete(*resource);
        *resource = 0;
    }
    stage_state = 0;
    if (stage_buffer) {
        entry_free_00452422(stage_buffer);
        stage_buffer = 0;
    }
    stage_buffer = 0;
}
#pragma code_seg(".text$8zzincr")
void ScoreState::IncrementCappedCount() {
    ++capped_count;
    if (capped_count >= 10)
        capped_count = 9;
}
#pragma code_seg(".text$8reg")
char* AnimationManager_0043e460::RegisterResource(const char* name, int resource, int parameter) {
    int index = 0;
    for (; index < 31; ++index) {
        if (records[index].resource == 0) {
            records[index].resource = resource;
            records[index].parameter = parameter;
            char* out = records[index].name;
            const char* text = name;
            while ((*out++ = *text++) != 0) {}
            records[index].state = 0;
            return const_cast<char*>(text);
        }
    }
    return (char*)(long)index;
}
#pragma code_seg()
