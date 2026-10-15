// Full compiler-visible lookup body; ABI anchor only, not exported game code.
#include "th10/render/queued_cleanup_pair.hpp"
#pragma code_seg(".text$50find")
__declspec(noinline) void* __fastcall QueuedCleanupManager::Find(
        QueuedCleanupContext* context, QueuedCleanupScriptId id) {
    if (!id.value)
        return 0;
    for (QueuedCleanupLookupEntry* node = context->primary_bucket; node != 0; node = node->next)
        if (*(int*)node->object == id.value)
            return node->object;
    for (QueuedCleanupLookupEntry* node = context->secondary_bucket; node != 0; node = node->next)
        if (*(int*)node->object == id.value)
            return node->object;
    return 0;
}
#pragma code_seg()
