// 0x004198A0 - scheduler callback of the floating text manager. The task's
// context (the manager) arrives in ECX and is handed to the update at
// 0x00419650, whose whole-program convention takes it in EBX.
#include "../../../build_support/include/contexts/game/marktext_dispatcher_context/recovery_script_executor_caller.hpp"

#pragma code_seg(".text$004198a0_fn")
int __fastcall Hint_OnUpdate(HintUpdateView* manager) {
    return manager->Update();
}
#pragma code_seg()
