// 0x0040AE20: mark every animation using the resource loaded in a slot for
// removal.
#include "th10/render/animation_resource_removal.hpp"

#pragma code_seg(".text$01accessor")
__declspec(noinline) void SprtCtrl::MarkSlotForRemoval(int slot) {
    void** resources = reinterpret_cast<void**>(reinterpret_cast<unsigned char*>(this) + 0x3ad06c);
    MarkResourceForRemoval(resources[slot]);
}
#pragma code_seg()
