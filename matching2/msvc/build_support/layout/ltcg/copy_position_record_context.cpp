// Compiler context only; never selected as recovered game code.
// The advancing source and indexed destination keep the three arguments in
// the retail EAX/EDX/EBX registers without exposing a private ABI in C++.
#include "../../../src/core/sprtlib/animation_manager_copy_position_record.cpp"
#pragma code_seg(".text$03context")
void __stdcall CopyPositionRecordContext(AnimationPositionManager* manager, const AnimationPositionRecord* source, int count) {
    for (int index=0;index<count;++index) CopyPositionRecord2(index,manager,source++);
}
#pragma code_seg()
