// 0x00401440: allocate and construct the game thread object, then load its
// resources and register its tasks. A failed load destroys and frees the
// object and returns null.
#include "th10/game/game_thread.hpp"

// The resource loader's view of the same object.
struct AsciiManager_00401110 {
    __declspec(noinline) int LoadResources();
};

extern "C" {
void __stdcall DestroyGameThread_00401260(GameThread *thread);
void __cdecl entry_free_004524a1(void *memory);
}
void *__cdecl operator new(unsigned int size);

#pragma code_seg(".text$00_c_create")
extern "C" __declspec(noinline) GameThread *__stdcall GameThread_Create_00401440() {
    GameThread *thread = new GameThread;
    if (reinterpret_cast<AsciiManager_00401110 *>(thread)->LoadResources()) {
        if (thread) {
            DestroyGameThread_00401260(thread);
            entry_free_004524a1(thread);
        }
        return 0;
    }
    return thread;
}
#pragma code_seg()
