#include "th10/render/anm_handle_release.hpp"

extern uint32_t DAT_00477824;  // tracked overlay handle 1
extern uint32_t DAT_00477828;  // tracked overlay handle 2
extern uint32_t DAT_0047782c;  // tracked overlay handle 3
extern uint32_t DAT_00491bec;  // frame latch, cleared every call

namespace {

// Mark one resolved object (and, unless solo, its children) with
// sprite word 2.
void MarkReleased(uint32_t handle, AnmResolveFn resolve) {
    AnmObject* object = resolve != 0 ? resolve(handle) : (AnmObject*)0;
    if (object == 0) {
        return;
    }
    object->sprite_word = 2;
    if (object->solo != 0) {
        return;
    }
    for (AnmChildNode* child = object->children; child != 0;
         child = child->next) {
        child->object->sprite_word = 2;
    }
}

}  // namespace

// 0x00421300 - Release the three tracked overlay animation handles.
// Retail resolves each global through FUN_004491C0 and reuses the
// mark-and-propagate pattern of 0x00409E50 with sprite word 2; the
// phase word gates the sweep so it runs exactly once.
void Anm_ReleaseTrackedHandles(uint32_t* phase, AnmResolveFn resolve) {
    if (*phase == 1) {
        MarkReleased(DAT_00477824, resolve);
        MarkReleased(DAT_00477828, resolve);
        MarkReleased(DAT_0047782c, resolve);
        DAT_00477824 = 0;
        DAT_00477828 = 0;
        DAT_0047782c = 0;
        *phase = 2;
    }
    if (DAT_00491bec != 0) {
        DAT_00491bec = 0;
    }
}
