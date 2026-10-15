// 0x00412A70: forward a float-variable lookup to the ECL VM of the object
// referenced at +0x14D8.
#include "th10/script/ecl_float_destination.hpp"

struct EclOwner_00412a70 {
    void* field_000;
    EclVm_00450070* vm;  // +0x0004
};

struct EclHolder_00412a70 {
    unsigned char unknown_0000[0x14D8];
    EclOwner_00412a70* owner;  // +0x14D8

    float* ResolveFloatDestination(int index);
};

#pragma code_seg(".text$01_")
__declspec(noinline) float* EclHolder_00412a70::ResolveFloatDestination(int index) {
    EclOwner_00412a70* target = owner;
    return target->vm->ResolveFloatDestination(index);
}
#pragma code_seg()
