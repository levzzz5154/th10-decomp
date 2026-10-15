// 0x0043C870..0x0043C889: the screen effect's on_remove callback, installed on
// its update task by Configure: release the effect's task pair, return the
// object to the CRT heap and report 0. The object arrives in ECX.
#include "../../../build_support/include/asm_symbols.hpp"

typedef void (__stdcall* RawPairReleaseFn)(void* pair);
extern "C" void __cdecl crt_free_startup(void* memory);

int __fastcall ScreenEffect_OnRemove(void* effect) {
    if (effect) {
        ((RawPairReleaseFn)asm_Recovery_ReleaseRawPair_0043cb00)(effect);
        crt_free_startup(effect);
    }
    return 0;
}
