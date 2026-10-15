// 0x0041FD00: create the loading screen (Loading, loading.cpp, LoadingInf): construct it and start its worker; on failure release and free it.
#include "th10/game/loading.hpp"
#include "th10/game/loading_view.hpp"
void* __cdecl operator new(unsigned int);
extern "C" void __stdcall Loading_Release(Loading*);
extern "C" void __cdecl crt_free_startup(void*);
#pragma code_seg(".text$04factory")
extern "C" __declspec(noinline) Loading* __cdecl
Loading_Create() {
    Loading* state = new Loading;
    if (reinterpret_cast<LoadingView*>(state)->StartWorker()) {
        if (state) {
            Loading_Release(state);
            crt_free_startup(state);
        }
        return 0;
    }
    return state;
}
#pragma code_seg()
