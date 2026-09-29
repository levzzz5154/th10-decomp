// 0x00418850: copy a string into the shared 0x00497C38 scratch buffer and return it.
#include <string.h>
extern "C" char data_00497c38[];

#pragma code_seg(".text$01accessor")
__declspec(noinline) char* __stdcall CopyToScratch_00418850(const char* text) {
    data_00497c38[0] = 0;
    strcat(data_00497c38, text);
    return data_00497c38;
}
#pragma code_seg()
