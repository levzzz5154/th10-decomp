// 0x00418850: copy a string into the shared 0x00497C38 scratch buffer and return it.
#include <string.h>
extern "C" char g_recovery_script_path[];

#pragma code_seg(".text$01accessor")
__declspec(noinline) char* __stdcall CopyToScratch_00418850(const char* text) {
    g_recovery_script_path[0] = 0;
    strcat(g_recovery_script_path, text);
    return g_recovery_script_path;
}
#pragma code_seg()
