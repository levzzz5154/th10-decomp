// 0x0040CD20: load a script through the shared filename buffer and parse it.
#include <string.h>
extern "C" char data_00497c38[];
#include "th10/platform/archive_file.hpp"
struct ScriptFileLoader {
    int Parse(char* data);
    __declspec(noinline) int Load(const char* name);
};
#pragma code_seg(".text$01script")
int ScriptFileLoader::Load(const char* name) {
    data_00497c38[0] = 0;
    strcat(data_00497c38, name);
    return (Parse(Archive_LoadFile(data_00497c38, 0, 0)) >= 0) - 1;
}
#pragma code_seg()
