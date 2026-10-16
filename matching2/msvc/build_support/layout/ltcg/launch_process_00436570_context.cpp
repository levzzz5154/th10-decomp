// Compiler context only; its bytes are not recovered game code.
#include "../../../src/core/main/launch_process.cpp"

#pragma code_seg(".text$03context")
int __stdcall Ctx(char** c, const char** a, int n) {
    int r = 0;
    for (int i = 0; i < n; ++i) r += LaunchProcess(c[i], a[i], i);
    return r;
}
#pragma code_seg()
