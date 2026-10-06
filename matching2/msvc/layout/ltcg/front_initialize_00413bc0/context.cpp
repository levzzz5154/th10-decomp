// Compiler-only single-call context; unselected and not recovered game code.
#include "th10/game/front_initialize_00413bc0.hpp"
#pragma code_seg(".text$0044bd00_context")
extern "C" int __stdcall FrontCompilerContext() {
    data_0047770c->Initialize();
    return 1;
}
#pragma code_seg()
