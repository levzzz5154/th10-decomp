// 0x0040B480: replace a loaded asset through the shared filename buffer.
#include <string.h>
#include "../../../include/contexts/game/right_aligned_text_context/archive_callers.hpp"
extern "C" char g_recovery_script_path[];
extern "C" void __cdecl entry_free_00452422(void*);
#pragma code_seg(".text$0040b480_fn")
char* __stdcall LoadAsset(const char* name, AssetBuffer* buffer) {
    g_recovery_script_path[0] = 0;
    strcat(g_recovery_script_path, name);
    char* data = Archive_LoadFile(g_recovery_script_path, 0, 0);
    if (buffer->data) {
        entry_free_00452422(buffer->data);
        buffer->data = 0;
    }
    buffer->data = data;
    return data;
}
#pragma code_seg()
