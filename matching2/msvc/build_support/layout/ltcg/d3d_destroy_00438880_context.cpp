// The original scalar deleting destructor is the complete unselected caller.
#include "../../../src/core/main/func_ctrl_destroy.cpp"
#include "destroy_release_adapter.cpp"
#include "../../../src/core/zunlib/platform_stop_worker_0044c150.cpp"
extern "C" void __cdecl entry_free_004524a1(void* memory);
#pragma code_seg(".text$30context")
void* Object_00439040::Destroy(unsigned int flags) {
    static_cast<FuncCtrlDestroyView*>(this)->~FuncCtrlDestroyView();
    if (flags & 1) entry_free_004524a1(this);
    return this;
}
#pragma code_seg()
#pragma section(".rdata$00config", read)
extern "C" __declspec(allocate(".rdata$00config"))
const unsigned int _load_config_used[18] = {72};
