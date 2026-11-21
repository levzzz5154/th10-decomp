// Handle validation at 0x00449450 as the executor sees it: a free function
// with the handle in ESI. Retail pushes no receiver for this call, so the
// manager-member spelling of the shared context does not fit here.
#include "th10/game/ending_script/script_executor.hpp"

extern "C" void* g_sprt_ctrl;

#pragma code_seg(".text$00449450_validate")
__declspec(noinline) AnmTextVm* __cdecl AnmHandle_Validate(AnmScriptHandle* handle) {
    AnimationScriptId id = { static_cast<int>(handle->value) };
    void* object = reinterpret_cast<AnmLookup*>(g_sprt_ctrl)->Find(
        reinterpret_cast<AnmLookupContext*>(g_sprt_ctrl), id);
    if (object == 0)
        handle->value = 0;
    return static_cast<AnmTextVm*>(object);
}
#pragma code_seg()
