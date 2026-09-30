#include <string.h>
#include "th10/render/resource_registrar_0043e460.hpp"
extern AnimationManager_0043e460 g_music_requests;
extern unsigned char* g_music_state;
// Queue a WAV file and mark the indexed track as requested. Retail assumes
// a three-character extension and deliberately retains its existing terminator.
#pragma code_seg(".text$00c_file")
__declspec(noinline) int __cdecl Music_RequestFile(unsigned music_index, const char* file_name) {
    char path[256];
    strcpy(path, file_name);
    char* extension = strrchr(path, '.');
    extension[1] = 'w';
    extension[2] = 'a';
    extension[3] = 'v';
    g_music_state[0x1D892 + music_index] = 1;
    g_music_requests.RegisterResource(path, 2, -1);
    return 0;
}
#pragma code_seg()
