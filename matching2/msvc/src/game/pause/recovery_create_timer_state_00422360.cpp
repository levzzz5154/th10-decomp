// 0x00422360: allocate, initialize, and register the menu timer state.
// A failed registration destroys and frees the state before returning null.
struct TimerState_00422360;
void* __cdecl operator new(unsigned int);
extern "C" void __cdecl free(void*);
extern "C" void __stdcall DestroyTimerState_00422220(TimerState_00422360*);
void* __fastcall InitializeTimerState_004220e0(int, TimerState_00422360*);
int __cdecl RegisterTimerState_00422150(TimerState_00422360*);

#pragma code_seg(".text$30factory")
__declspec(noinline) TimerState_00422360* __stdcall CreateTimerState_00422360() {
    void* storage = operator new(0x2C8);
    TimerState_00422360* state;
    if (storage)
        state = (TimerState_00422360*)InitializeTimerState_004220e0(
            0, (TimerState_00422360*)storage);
    else
        state = 0;
    if (RegisterTimerState_00422150(state)) {
        if (state) {
            DestroyTimerState_00422220(state);
            free(state);
        }
        return 0;
    }
    return state;
}
#pragma code_seg()
