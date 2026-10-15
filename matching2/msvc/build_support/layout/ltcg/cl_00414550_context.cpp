// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/unassigned_00414550.cpp"

extern "C" void __cdecl opaque_release_004492a0(void* item);

#pragma code_seg(".text$01anchor")
__declspec(noinline) void AnimationSlot_00414550::ReleaseRetail() {
    opaque_release_004492a0(field_40);
    field_40 = 0;
    opaque_release_004492a0(field_44);
    field_44 = 0;
    opaque_release_004492a0(field_48);
    field_48 = 0;
    opaque_release_004492a0(field_4c);
    field_4c = 0;
    opaque_release_004492a0(field_50);
    field_50 = 0;
}
#pragma code_seg()

#pragma code_seg(".text$05context")
int __stdcall DestroyContext_00414550(AnimationSlot_00414550** items, int count) {
    int total = 0;
    for (int i = 0; i < count; ++i) {
        AnimationSlot_00414550* one = items[i];
        total += (int)DestroySlot(one, (unsigned int)i);
    }
    return total;
}
#pragma code_seg()
