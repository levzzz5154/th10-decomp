// Compiler-only call context. This 19-byte body is not recovered game code.
#include "th10/game/score_hud.hpp"
#pragma code_seg(".text$0044bd00_context")
extern "C" int __stdcall HudCompilerContext() {
    g_front->Update();
    return 1;
}
#pragma code_seg()
