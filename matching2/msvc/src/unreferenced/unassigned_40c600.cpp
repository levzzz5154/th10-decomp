// 0x0040C600..0x0040C644: forward an integer-variable lookup to the owner's
// ECL VM.  The owner arrives in EAX and the index in ECX; the body of the
// lookup at 0x00450030 is repeated here, unlike the float forwarder at 0x0040C660.
#include "th10/script/ecl_float_destination.hpp"

struct EclOwner2 {
    void* field_000;
    EclVm3* vm;  // +0x0004

    int* ResolveIntDestination(int index);
};

#pragma code_seg(".text$01_")
__declspec(noinline) int* EclOwner2::ResolveIntDestination(int index) {
    EclVm3* vm = this->vm;
    if (vm->table->valid_mask & (1 << index)) {
        const int& offset = vm->table->offsets[index];
        if (offset >= 0) {
            EclFrame3* frame = &vm->frame;
            return (int*)((char*)frame + frame->frame_base + offset);
        }
        return vm->frame.owner->ResolveExternalInt(offset);
    }
    return 0;
}
#pragma code_seg()
