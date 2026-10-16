// Compiler context only; its bytes are not recovered game code.
#include "../../../src/core/sprtlib/animation_manager_find.cpp"
#include "../../../src/core/sprtanim/animation_object_configure_from_resource.cpp"
#include "../../../src/core/sprtlib/animation_manager_select_sprite_from_resource.cpp"

#pragma code_seg(".text$zzcontext")
void __stdcall Ctx(AnimationHandle14** p, int n, Resource2* r) {
    for (int i = 0; i < n; ++i) p[i]->ConfigureFromResource(r, i);
}
#pragma code_seg()
