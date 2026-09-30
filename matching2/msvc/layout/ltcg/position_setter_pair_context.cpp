// Synthetic compiler context only; not selected as recovered game code.
#include "../../src/render/animation_manager_set_position_004492f0.cpp"
#include "position_setter_find_anchor.cpp"
#pragma code_seg(".text$70context")
int __stdcall PositionSetterCompilerContext_004492f0(
        PositionVector_004492f0* positions, PositionLookupContext_004492f0* context,
        PositionScriptId_004492f0* ids, int count) {
    while (count--) {
        SetAnimationPosition_004492f0(positions, context, ids[0]);
        SetAnimationTranslatedPosition_00449350(positions, context, ids[1]);
        ++positions;
        ids += 2;
    }
    return 0;
}
#pragma code_seg()
