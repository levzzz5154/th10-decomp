// 0x0042B430: construct the effect manager and publish it at 0x00477840.
#include "th10/game/anm_vm.hpp"

// One effect slot; constructing it clears its active bit.
struct Effect_0042b430 {
    unsigned char unknown_00[0x2C];
    unsigned int active : 1;
    unsigned int other_flags : 31;
    unsigned char unknown_30[0x10];

    __forceinline Effect_0042b430() { active = 0; }
};

struct EffectManager_0042b430 {
    unsigned int flags;
    unsigned char unknown_004[0x14];
    AnmVm vm;
    Effect_0042b430 effects[0x2D3];

    EffectManager_0042b430();
};
extern "C" EffectManager_0042b430* data_00477840;

#pragma code_seg(".text$01accessor")
__declspec(noinline) EffectManager_0042b430::EffectManager_0042b430() {
    memset(this, 0, sizeof(*this));
    flags |= 2;
    data_00477840 = this;
}
#pragma code_seg()
