// Full compiler-visible lookup body; ABI anchor only, not exported game code.
#include "th10/render/queued_cleanup_pair.hpp"
#pragma code_seg(".text$50find")
__declspec(noinline) void* __fastcall QueuedCleanupManager_00421070::Find(
        QueuedCleanupContext_00421070* context, QueuedCleanupScriptId_00421070 id) {
    if (!id.value)
        return 0;
    for (QueuedCleanupLookupEntry_00421070* node = context->primary_bucket; node != 0; node = node->next)
        if (*(int*)node->object == id.value)
            return node->object;
    for (QueuedCleanupLookupEntry_00421070* node = context->secondary_bucket; node != 0; node = node->next)
        if (*(int*)node->object == id.value)
            return node->object;
    return 0;
}
#pragma code_seg()
