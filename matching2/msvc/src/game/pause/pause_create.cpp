// 0x00422360: allocate, initialize, and register the pause menu (Pause).
// A failed registration destroys and frees the state before returning null.
struct Pause;
void* __cdecl operator new(unsigned int);
extern "C" void __cdecl free(void*);
extern "C" void __stdcall Pause_Release(Pause*);
void* __fastcall Pause_Construct2(int, Pause*);
int __cdecl Pause_RegisterTasks(Pause*);

#pragma code_seg(".text$30factory")
__declspec(noinline) Pause* __stdcall Pause_Create() {
    void* storage = operator new(0x2C8);
    Pause* state;
    if (storage)
        state = (Pause*)Pause_Construct2(
            0, (Pause*)storage);
    else
        state = 0;
    if (Pause_RegisterTasks(state)) {
        if (state) {
            Pause_Release(state);
            free(state);
        }
        return 0;
    }
    return state;
}
#pragma code_seg()
