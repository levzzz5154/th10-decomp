// Local call-convention anchors for the recovery script executor region
// (0x0040BD80) only. The shared marktext cluster keeps its byte-pinned
// member-SetFlag and original-order LoadAsset bodies untouched; this region's
// retail call shapes need two differently spelled stand-ins, provided here:
//
//  - AnmHandle_SetFlag is a free function whose first parameter is never read,
//    so the pass drops it and callers push only the id (retail's one-push
//    shape, see 0x00449630). The id slot is forwarded to Find without an
//    entry-block copy, which reproduces retail's `mov eax,[esp+4]; push eax`
//    and keeps the id a stack parameter instead of promoting it to a register.
//
//  - LoadAsset with (buffer, name) parameter order: in an LTCG cluster the
//    declared parameter order sets the order callers load the arguments, and
//    retail's caller loads the name first.
#include <string.h>
#include "th10/game/ending_script/script_executor.hpp"
#include "th10/platform/archive_callers.hpp"

extern "C" void* g_sprt_ctrl;
extern "C" char g_archive_load_path[];
extern "C" void __cdecl crt_free(void*);

#pragma code_seg(".text$004492a0_fn")
__declspec(noinline) void* __fastcall AnmHandle_SetFlag(AnmLookupContext* context, int id) {
    AnmLookupNode* node = static_cast<AnmLookupNode*>(
        reinterpret_cast<AnmLookup*>(g_sprt_ctrl)->Find(
            context,
            *reinterpret_cast<const AnimationScriptId*>(&id)));
    if (node) {
        node->flags |= 0x04000000u;
        if (!node->children_flagged)
            for (node = node->children; node != 0; node = node->next)
                node->object->flags |= 0x04000000u;
    }
    return node;
}
#pragma code_seg(".text$0040b480_fn")
__declspec(noinline) char* __stdcall LoadAsset(AssetBuffer* buffer, const char* name) {
    g_archive_load_path[0] = 0;
    strcat(g_archive_load_path, name);
    char* data = Archive_LoadFile(g_archive_load_path, 0, 0);
    if (buffer->data) {
        crt_free(buffer->data);
        buffer->data = 0;
    }
    buffer->data = data;
    return data;
}
#pragma code_seg()
