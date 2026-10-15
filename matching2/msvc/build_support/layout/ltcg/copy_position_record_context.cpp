// Compiler context only; never selected as recovered game code.
// The advancing source and indexed destination keep the three arguments in
// the retail EAX/EDX/EBX registers without exposing a private ABI in C++.
#include "../../../src/core/sprtlib/animation_manager_copy_position_record_00447940.cpp"
#pragma code_seg(".text$03context")
void __stdcall CopyPositionRecordContext(AnimationPositionManager_00447940* manager, const AnimationPositionRecord_00447940* source, int count) {
    for (int index=0;index<count;++index) CopyPositionRecord_00447940(index,manager,source++);
}
#pragma code_seg()
