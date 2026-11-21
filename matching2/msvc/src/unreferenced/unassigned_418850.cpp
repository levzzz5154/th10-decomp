// 0x00418850: copy a string into the shared 0x00497C38 scratch buffer and return it.
#include <string.h>
extern "C" char g_archive_load_path[];

#pragma code_seg(".text$01accessor")
__declspec(noinline) char* __stdcall CopyToScratch(const char* text) {
    g_archive_load_path[0] = 0;
    strcat(g_archive_load_path, text);
    return g_archive_load_path;
}
#pragma code_seg()
