// 0x00401440: allocate and construct the game thread, then bind its resources.
//
// Retail takes no stack arguments and returns the resulting pointer in EAX.
// The constructor and resource loader use private register conventions at
// their entries; the ordinary C++ calls below model their behavior, while the
// exact caller-side register transfers remain documented in the recovery note.

struct GameThread {
    unsigned char bytes[0x89AC];

    __declspec(noinline) GameThread();
};

void* __cdecl operator new(unsigned int size);

// Retail's loader receives its object pointer in EAX. This typed declaration
// lets the source express the object argument; it does not describe retail's
// private entry ABI (see matching2/reference/recovery_notes/
// create_game_thread_00401440.md).
extern "C" int __fastcall LoadGameThreadResources_00401110(GameThread* thread);
extern "C" void __stdcall DestroyGameThread_00401260(GameThread* thread);
extern "C" void __cdecl Free_004524a1(void* memory);

// Keep the error path first: this is the branch layout used by the retail
// function and measured in the earlier candidate model.
__declspec(noinline) GameThread* CreateGameThread_00401440() {
    GameThread* thread = new GameThread;
    if (LoadGameThreadResources_00401110(thread) != 0) {
        if (thread) {
            DestroyGameThread_00401260(thread);
            Free_004524a1(thread);
        }
        return 0;
    }
    return thread;
}
