// Unselected native ABI anchor from layout/ltcg/resource_surface_loading_clear.cpp.
// Only the placement section differs.
// Release one indexed animation resource set at 0x00447F70.
// Native LTCG supplies the retail EDI manager and ESI index convention.
extern "C" void __cdecl ReleaseHeapMemory_00452422(void* memory);
extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)
#include "th10/render/resource_surface_loading.hpp"
#pragma code_seg(".text$02clear")
void AnimationManagerIndexed_00447f70::Clear(int index) {
    if (primary[index]) { primary[index]->Release(); primary[index] = 0; }
    if (secondary[index]) { secondary[index]->Release(); secondary[index] = 0; }
    if (memory[index]) {
        ReleaseHeapMemory_00452422(memory[index]);
        memory[index] = 0;
        // Preserve the retail conditional clear followed by the final clear.
        _ReadWriteBarrier();
    }
    memory[index] = 0;
}
#pragma code_seg()
