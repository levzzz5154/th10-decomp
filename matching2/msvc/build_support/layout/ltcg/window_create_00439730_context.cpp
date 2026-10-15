// Compiler context only; never selected as recovered game code.
#include "../../../src/core/main/window_create_00439730.cpp"

extern "C" int __cdecl WindowCreateEscape(void* pointer, int value);

// A caller that keeps the instance live across calls, as the entry point does.
#pragma inline_depth(0)
#pragma code_seg(".text$0040a000_context")
extern "C" int __stdcall WindowCreateContext(HINSTANCE* instances, int count) {
    int total = 0;
    for (int index = 0; index < count; ++index) {
        HINSTANCE instance = instances[index];
        total += WindowCreateEscape(instance, index);
        if (CreateGameWindow_00439730(instance) != 0)
            total += WindowCreateEscape(instance, total);
        total += WindowCreateEscape(g_main_window.window, index);
    }
    return total;
}
#pragma code_seg()
#pragma inline_depth()
