// Handle validation at 0x00449450 as the executor sees it: a free function
// with the handle in ESI. Retail pushes no receiver for this call, so the
// manager-member spelling of the shared context does not fit here.
#include "../../../../include/contexts/game/marktext_dispatcher_context/recovery_script_executor.hpp"

extern "C" void* g_sprt_ctrl;

#pragma code_seg(".text$00449450_validate")
__declspec(noinline) RecoveryTextVm* __cdecl RecoveryValidateHandle(RecoveryHandle* handle) {
    RecoveryScriptId id = { static_cast<int>(handle->value) };
    void* object = reinterpret_cast<RecoveryLookup*>(g_sprt_ctrl)->Find(
        reinterpret_cast<RecoveryLookupContext*>(g_sprt_ctrl), id);
    if (object == 0)
        handle->value = 0;
    return static_cast<RecoveryTextVm*>(object);
}
#pragma code_seg()
