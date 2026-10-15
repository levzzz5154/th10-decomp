// Compiler context only; never selected as recovered game code.
#include "../../../src/game/bomb/bomb_delete.cpp"

#pragma code_seg(".text$03context")
int __stdcall FUN00405730CompilerContext(void** pairs, int count) {
    void** cursor = pairs;
    while (count--) {
        void* pair = *cursor++;
        Bomb_Delete(pair);
        Bomb_Delete(pair);
    }
    return 0;
}
#pragma code_seg()
