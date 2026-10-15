#include "th10/render/animation_script_change.hpp"
#pragma code_seg(".text$03find")
Entity* __fastcall ScriptChangeManager::Find(ScriptChangeContext* context, ScriptChangeId id) {
    if (!id.value) return 0;
    for (ScriptChangeLink* node = context->primary; node; node = node->next)
        if (node->object->animation_handle == id.value) return node->object;
    for (ScriptChangeLink* node = context->secondary; node; node = node->next)
        if (node->object->animation_handle == id.value) return node->object;
    return 0;
}
#pragma code_seg()
