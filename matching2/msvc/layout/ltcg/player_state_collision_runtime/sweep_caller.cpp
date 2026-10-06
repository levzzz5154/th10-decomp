#include "runtime.hpp"

// The enemy update is the sweep's only caller; it passes no result record.
struct SweepCallerEnemy {
    unsigned char reserved_00[0x2c];
    PickupPoint position;
    unsigned char reserved_34[0xb0 - 0x34];
    PickupPoint size;
};
extern "C" PlayerState* data_00477834;
#pragma code_seg(".text$f0040dc80F")
extern "C" __declspec(noinline) int __stdcall PickupSweepCaller(SweepCallerEnemy* enemy) {
    return static_cast<PickupSweepResult*>(0)->Sweep(data_00477834, &enemy->position, &enemy->size);
}
#pragma code_seg()
