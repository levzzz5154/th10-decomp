// 0x0041F850: construct the 0x3F0-byte state published at 0x00477820.
#include "th10/game/anm_vm.hpp"

struct StateTable_0041f850 {
    unsigned int flags;
    unsigned char unknown_004[0xC];
    GameTimer timer;
    unsigned char unknown_024[0xC];
    AnmVm vm;
    unsigned char unknown_3dc[0x14];

    StateTable_0041f850();
};
extern "C" StateTable_0041f850* data_00477820;

#pragma code_seg(".text$01accessor")
__declspec(noinline) StateTable_0041f850::StateTable_0041f850() {
    memset(this, 0, sizeof(*this));
    flags |= 2;
    data_00477820 = this;
}
#pragma code_seg()
