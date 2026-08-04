#include "th10/render/render_stage_select.hpp"

#ifdef _MSC_VER
extern "C" void sub_4215A0(void);
#endif

// 0x00401D20 - Select the active render stage. Retail points the active
// stage slot (+0x384) at the indexed 0x118-byte stage record (base +0x154),
// reapplies the camera (retail 0x004215A0), submits the stage's viewport
// block (+0xCC) through the device's SetViewport entry (vtable +0xBC), and
// records the active stage index (+0x388).
#ifdef _MSC_VER
__declspec(naked) void GameThread_SelectRenderStageRetail() {
    __asm {
        mov eax, ebx
        imul eax, 118h
        push edi
        lea edi, [eax+esi+154h]
        mov [esi+384h], edi
        call sub_4215A0
        mov edx, [esi+384h]
        mov eax, [esi+8]
        mov ecx, [eax]
        add edx, 0CCh
        push edx
        push eax
        call dword ptr [ecx+0BCh]
        mov [esi+388h], ebx
        pop edi
        ret
    }
}
#endif

void GameThread_SelectRenderStage(RenderStage* stages, int stage_index,
                                  RenderStage** active_stage_out,
                                  int* active_index_out,
                                  void (*apply_camera)(void),
                                  void (*set_viewport)(const void* viewport)) {
    RenderStage* stage = stages + stage_index;
    *active_stage_out = stage;
    if (apply_camera != 0) apply_camera();
    if (set_viewport != 0) set_viewport(stage->viewport);
    *active_index_out = stage_index;
}
