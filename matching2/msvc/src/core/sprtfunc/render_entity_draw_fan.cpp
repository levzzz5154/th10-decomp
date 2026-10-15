// 0x00445880: draw callback installed at 0x00445337 for entities whose strip
// vertices form a 33-point triangle fan.  Compiled in the anm_batch_flush
// native-LTCG cluster so the call into 0x004450E0 uses its private entry
// (manager in ECX, entity in EAX).
#include "th10/render/quad_batch.hpp"

#pragma code_seg(".text$07contextzb")
__declspec(noinline) int RenderEntity::DrawFan33() {
    g_sprt_ctrl->DrawFan(this, strip_vertices, 0x21);
    return 0;
}
#pragma code_seg()
