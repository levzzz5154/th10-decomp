// Handle validation at 0x00449450 as the executor sees it: a free function
// with the handle in ESI. Retail pushes no receiver for this call, so the
// manager-member spelling of the shared context does not fit here.
#include "th10/game/marktext_dispatcher_context/recovery_script_executor_0040bd80.hpp"

extern "C" void* g_sprt_ctrl;

#pragma code_seg(".text$00449450_validate")
__declspec(noinline) void* __cdecl RecoveryValidateHandle_00449450(RecoveryHandle_0040bd80* handle) {
    RecoveryScriptId_0040bd80 id = { static_cast<int>(handle->value) };
    void* object = reinterpret_cast<RecoveryLookup_0040bd80*>(g_sprt_ctrl)->Find(
        reinterpret_cast<RecoveryLookupContext_0040bd80*>(g_sprt_ctrl), id);
    if (object == 0)
        handle->value = 0;
    return object;
}
#pragma code_seg()
