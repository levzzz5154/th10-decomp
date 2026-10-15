// Synthetic compiler context only; not selected as recovered game code.
#include "../../contexts/legacy/render/animation_manager_set_position_004492f0.cpp"
#include "position_setter_find_anchor.cpp"
#pragma code_seg(".text$70context")
int __stdcall PositionSetterCompilerContext_004492f0(
        PositionVector* positions, PositionLookupContext* context,
        PositionScriptId* ids, int count) {
    while (count--) {
        SetAnimationPosition_004492f0(context, positions, ids[0]);
        SetAnimationTranslatedPosition(positions, context, ids[1]);
        reinterpret_cast<AnimationPositionHandle*>(ids)->SetPosition(positions);
        reinterpret_cast<AnimationPositionHandle*>(ids + 1)->SetTranslatedPosition(positions);
        ++positions;
        ids += 2;
    }
    return 0;
}
#pragma code_seg()
