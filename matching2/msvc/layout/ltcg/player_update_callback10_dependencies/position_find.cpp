// Compiler-visible lookup anchor; not selected as recovered code.
#include "th10/render/position_setter_pair.hpp"
#pragma code_seg(".text$130find")
void* __fastcall PositionManager_004492f0::Find(
        PositionLookupContext_004492f0* context, PositionScriptId_004492f0 id) {
    if (!id.value)
        return 0;
    for (PositionEntry_004492f0* node = context->primary_bucket; node; node = node->next)
        if (*(int*)node->object == id.value)
            return node->object;
    for (PositionEntry_004492f0* node = context->secondary_bucket; node; node = node->next)
        if (*(int*)node->object == id.value)
            return node->object;
    return 0;
}
#pragma code_seg()
