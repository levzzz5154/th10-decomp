// 0x0040B480: replace a loaded asset through the shared filename buffer.
#include <string.h>
#include "th10/game/right_aligned_text_context/archive_callers.hpp"
extern "C" char data_00497c38[];
extern "C" void __cdecl entry_free_00452422(void*);
#pragma code_seg(".text$0040b480_fn")
char* __stdcall LoadAsset(const char* name, AssetBuffer* buffer) {
    data_00497c38[0] = 0;
    strcat(data_00497c38, name);
    char* data = Archive_LoadFile(data_00497c38, 0, 0);
    if (buffer->data) {
        entry_free_00452422(buffer->data);
        buffer->data = 0;
    }
    buffer->data = data;
    return data;
}
#pragma code_seg()
