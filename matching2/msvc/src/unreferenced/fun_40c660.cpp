// 0x0040C660: forward a float-variable lookup to the owner's ECL VM.
#include "th10/script/ecl_float_destination.hpp"

struct EclOwner3 {
    void* field_000;
    EclVm3* vm;  // +0x0004

    float* ResolveFloatDestination(int index);
};

#pragma code_seg(".text$01_")
__declspec(noinline) float* EclOwner3::ResolveFloatDestination(int index) {
    return vm->ResolveFloatDestination(index);
}
#pragma code_seg()
