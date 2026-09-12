// Compiler context only; never selected as recovered game code.
#include "../../src/game/platform_run_interface_0044d300.cpp"

#pragma code_seg(".text$03context")
int __stdcall PlatformRunInterface0044D300CompilerContext(
        PlatformD300Entry** entries, unsigned int** completed, int count) {
    int result = 0;
    while (count-- > 0)
        result |= (*entries++)->Run(*completed++);
    return result;
}
#pragma code_seg()
