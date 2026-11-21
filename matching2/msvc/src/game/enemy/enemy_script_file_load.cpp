// 0x0040CD20: load a script through the shared filename buffer and parse it.
#include <string.h>
extern "C" char g_recovery_script_path[];
#include "th10/platform/archive_file.hpp"
struct ScriptFileLoader {
    int Parse(char* data);
    __declspec(noinline) int Load(const char* name);
};
#pragma code_seg(".text$02script")
int ScriptFileLoader::Load(const char* name) {
    g_recovery_script_path[0] = 0;
    strcat(g_recovery_script_path, name);
    return (Parse(Archive_LoadFile(g_recovery_script_path, 0, 0)) >= 0) - 1;
}
#pragma code_seg()
