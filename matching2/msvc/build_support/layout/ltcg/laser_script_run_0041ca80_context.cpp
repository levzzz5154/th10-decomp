// Compiler context only; never recovered game code. The member-pointer
// indirection keeps the caller edge opaque, as the retail vtable caller is.
#include "../../../src/game/laser/laser_script_run_0041ca80.cpp"
#include "th10/platform/sound_queue.hpp"

#pragma code_seg(".text$0044e100_context")
extern "C" int __stdcall LaserScriptRunCompilerContext(
        LaserScriptRun_0041ca80** lasers, int count) {
    void (LaserScriptRun_0041ca80::*const run)() = &LaserScriptRun_0041ca80::Run;
    for (int index = 0; index < count; ++index)
        (lasers[index]->*run)();
    return count;
}
#pragma code_seg()
