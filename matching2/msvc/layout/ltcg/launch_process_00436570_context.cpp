// Compiler context only; its bytes are not recovered game code.
#include "../../src/platform/launch_process_00436570.cpp"

#pragma code_seg(".text$03context")
int __stdcall Ctx(char** c, const char** a, int n) {
    int r = 0;
    for (int i = 0; i < n; ++i) r += LaunchProcess_00436570(c[i], a[i], i);
    return r;
}
#pragma code_seg()
