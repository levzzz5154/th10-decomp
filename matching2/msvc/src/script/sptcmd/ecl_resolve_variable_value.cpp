// 0x00450030..0x00450069: hand back where the integer variable selected by the
// index in CL lives: a non-negative slot is an offset into the pooled frame, a
// negative one is resolved by the value owner's third virtual.  The integer
// counterpart of 0x00450070; the VM arrives in ESI, a convention only a native
// LTCG link chooses, so this region is compiled in that cluster.
#include "th10/script/ecl_float_destination.hpp"

#pragma code_seg(".text$00layoutb")
int* EclVm3::ResolveIntDestination(int index) {
    if (table->valid_mask & (1 << index)) {
        const int& offset = table->offsets[index];
        if (offset >= 0) {
            EclFrame3* frame = &this->frame;
            return (int*)((char*)frame + frame->frame_base + offset);
        }
        return this->frame.owner->ResolveExternalInt(offset);
    }
    return 0;
}
#pragma code_seg()
