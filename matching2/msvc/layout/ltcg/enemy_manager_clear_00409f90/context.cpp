// Compiler context only; never selected as recovered game code.
#include "../../../src/game/eclview/enemy_manager_clear_00409f90.cpp"
#include "../../../src/core/sprtlib/animation_manager_mark_resource_for_removal_004493e0.cpp"

#pragma code_seg(".text$15context")
void __stdcall EnemyManagerClearCompilerContext(EnemyCtrlClearView** managers, int count) {
    while (count--) (*managers++)->Clear();
}
#pragma code_seg()
