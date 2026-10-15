// Compiler context only; never selected as recovered game code.
#include "../../src/game/eclview/player_suspend.cpp"

#pragma code_seg(".text$03context")
int __stdcall f40a010CompilerContext(PlayerTaskPair** pairs, int count) {
    for (int index = 0; index < count; ++index)
        pairs[index]->Suspend();
    return 0;
}
#pragma code_seg()
