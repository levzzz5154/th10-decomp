// Compiler context only; never selected as recovered game code.
#include "../../../src/game/hint/hint_save.cpp"

#pragma code_seg(".text$03context")
// A direct caller of the rooted entry, so the whole-program link sees the
// hint writer's real uses; its bytes are not recovered game code.
extern "C" __declspec(noinline) int __stdcall HintSaveCtx(Manager3** managers,
                                                          const char* path,
                                                          int count) {
    int result = 0;
    for (int i = 0; i < count; ++i) {
        result += SaveHints(managers[i], path);
    }
    return result;
}
#pragma code_seg()
