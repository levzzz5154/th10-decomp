// 0x0042B660: create the score popups (SmollScore): construct, initialize, publish in g_smoll_score.
#include "th10/game/smoll_score.hpp"
#include "th10/game/smoll_score_view.hpp"
void* __cdecl operator new(unsigned int);
extern "C" void __stdcall asm_FUN_0042b570_0042b570(SmollScore*);
extern "C" void __cdecl crt_free_startup(void*);
#pragma code_seg(".text$00zbfactory")
extern "C" __declspec(noinline) SmollScore* __cdecl
SmollScore_Create() {
    SmollScore* state = new SmollScore;
    if (reinterpret_cast<SmollScoreView*>(state)->Initialize()) {
        if (state) {
            asm_FUN_0042b570_0042b570(state);
            crt_free_startup(state);
        }
        return 0;
    }
    return state;
}
#pragma code_seg()
