// 0x00412A70: forward a float-variable lookup to the ECL VM of the object
// referenced at +0x14D8.
#include "th10/script/ecl_float_destination.hpp"

struct EclOwner4 {
    void* field_000;
    EclVm3* vm;  // +0x0004
};

struct EclHolder {
    unsigned char unknown_0000[0x14D8];
    EclOwner4* owner;  // +0x14D8

    float* ResolveFloatDestination(int index);
};

#pragma code_seg(".text$01_")
__declspec(noinline) float* EclHolder::ResolveFloatDestination(int index) {
    EclOwner4* target = owner;
    return target->vm->ResolveFloatDestination(index);
}
#pragma code_seg()
