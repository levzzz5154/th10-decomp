// 0x0042BF30: create the script tester (SptTest): allocate, construct, register its tasks. Nothing calls it.
#include "th10/game/spt_test_state.hpp"
#include "th10/game/spt_test_tasks.hpp"
void* __cdecl operator new(unsigned int);
extern "C" SptTestState* __fastcall SptTest_Construct(int, SptTestState*);
extern "C" void __stdcall asm_FUN_0042bc30_0042bc30(SptTestState*);
extern "C" void __cdecl crt_free_startup(void*);

#pragma code_seg(".text$02factory")
extern "C" __declspec(noinline) SptTestState* __cdecl
asm_FUN_0042bf30_0042bf30() {
    SptTestState* state = new SptTestState;
    if (state)
        state = SptTest_Construct(0, state);
    else
        state = 0;
    if (reinterpret_cast<SptTestTaskView*>(state)->InstallTasks()) {
        if (state) {
            asm_FUN_0042bc30_0042bc30(state);
            crt_free_startup(state);
        }
        return 0;
    }
    return state;
}
#pragma code_seg()
