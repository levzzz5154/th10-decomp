#include "asm_symbols.hpp"

// 0x00453B60 calls the CRT process-exit helper with status 0xFF.
extern "C" __declspec(noinline) __declspec(noreturn) void __cdecl
asm_FUN_00453b60_00453b60() {
    asm_crtExitProcess_00457547(0xff);
}
