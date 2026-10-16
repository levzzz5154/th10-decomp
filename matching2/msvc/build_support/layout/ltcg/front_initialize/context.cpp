// Compiler-only single-call context; unselected and not recovered game code.
#include "th10/game/front_initialize.hpp"
#pragma code_seg(".text$0044bd00_context")
extern "C" int __stdcall FrontCompilerContext() {
    g_front->Initialize();
    return 1;
}
#pragma code_seg()
