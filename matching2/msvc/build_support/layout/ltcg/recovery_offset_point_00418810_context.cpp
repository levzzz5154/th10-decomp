// Compiler context only; never selected as recovered game code.
// The array-walking caller is what makes the whole-program pass pick the
// observed retail convention: the source point in EAX, with ECX and EDX left
// live at the call so the receiver cannot take either of them.
#include "../../../src/game/game/recovery_offset_point_00418810.cpp"

#pragma code_seg(".text$03context")
Vector3_00418810* __stdcall OffsetPointCompilerContext(Vector3_00418810** points, int count) {
    Vector3_00418810* last = 0;
    while (count--) {
        last = (*points++)->OffsetPoint();
    }
    return last;
}
#pragma code_seg()
