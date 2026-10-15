// 0x00443F80..0x00443FA0 (33 bytes): project the entity's billboard quad and
// submit it as a plain sprite when the projection succeeds.
//
// The guard is the same one 0x00443FB0 opens with: 0x00443B60 builds the
// projected quad from the entity and returns non-zero when the centre fell
// outside the normalized depth range, in which case the dispatcher's case 4
// sees -1.  On success the shared quad 0x00443B60 wrote is submitted through
// the sprite pipeline with mode 0.
//
// Retail enters this body with the entity in ESI and the manager on the stack
// (the callee pops it) - the dispatcher 0x004451C0 marshals `push ecx; mov
// esi,eax; call 0x00443F80` - so it is modelled as a member of the entity,
// with 0x00443B60 reached through a body the cluster compiles at its retail
// address (the projection takes the entity in EAX and no other argument, which
// no declaration names).
#include "th10/render/quad_batch.hpp"

struct BillboardSource_00443B60 {
    unsigned char reserved_0000[0x35C];
    __declspec(noinline) int BuildProjectedQuad();
};

#pragma code_seg(".text$06b05z00projected")
int RenderEntity::SubmitProjectedQuad(AnimationManager_00442F50* manager) {
    if (((BillboardSource_00443B60*)this)->BuildProjectedQuad() != 0) {
        return -1;
    }
    return manager->SubmitSpriteQuad(this, 0);
}
#pragma code_seg()
