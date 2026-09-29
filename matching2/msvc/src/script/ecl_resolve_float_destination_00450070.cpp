// 0x00450070..0x004500CC: hand back where the float variable selected by the
// index in CL lives. The variable table marks the live slots with a 16-bit
// mask; a slot's displacement is stored as a float and is either a
// non-negative offset into the pooled frame or a negative one the value owner
// resolves through its fourth virtual. The VM arrives in EAX and the index in
// ECX, a convention only a native LTCG link chooses, so this region is
// compiled as a cluster.

#include "th10/script/ecl_float_destination.hpp"

#pragma code_seg(".text$01accessor")
float* EclVm_00450070::ResolveFloatDestination(int index) {
    if (table->valid_mask & (1 << index)) {
        const float& displacement = table->displacements[index];
        if (displacement >= 0.0f) {
            EclFrame_00450070* frame = &this->frame;
            return (float*)((char*)frame + frame->frame_base + (int)displacement);
        }
        return this->frame.owner->ResolveExternalFloat((int)displacement);
    }
    return 0;
}
#pragma code_seg()
