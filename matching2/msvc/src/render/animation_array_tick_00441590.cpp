// Tick each animation whose signed script index is nonnegative.
// Native LTCG passes the array in ECX and count in EAX, with plain RET.
#include <stddef.h>

struct BatchAnimation {
    unsigned char reserved_000[0x38A];
    short script_index;
    unsigned char reserved_38c[0x20];
};
typedef char BatchAnimationExtent[sizeof(BatchAnimation) == 0x3AC ? 1 : -1];
typedef char BatchAnimationIndexOffset[offsetof(BatchAnimation, script_index) == 0x38A ? 1 : -1];

// The real animation VM takes a stack object pointer and returns with RET4.
extern "C" void __stdcall RunBatchAnimation(BatchAnimation* animation);
#pragma code_seg(".text$01tick")
extern "C" __declspec(noinline) void __cdecl TickAnimationArray(
        BatchAnimation* animations, unsigned int count) {
    while (count) {
        if (animations->script_index >= 0)
            RunBatchAnimation(animations);
        ++animations;
        --count;
    }
}
#pragma code_seg()
