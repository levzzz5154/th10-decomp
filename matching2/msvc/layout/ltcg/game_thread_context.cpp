// Compiler context only; never selected as recovered game code.
#pragma code_seg(".text$01thread")
#include "../../src/game/game_thread.cpp"
#pragma code_seg()

#pragma code_seg(".text$03context")
inline void* __cdecl operator new(unsigned int, void* memory) {
    return memory;
}

inline void __cdecl operator delete(void*, void*) {
}

int __stdcall GameThreadCompilerContext(GameThread* threads, int count) {
    for (int index = 0; index < count; ++index)
        new (&threads[index]) GameThread;
    return 0;
}
#pragma code_seg()
