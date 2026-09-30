// Compiler context only; its bytes are not recovered game code.
#include "../../src/render/animation_manager_find_004491c0.cpp"
#include "../../src/game/animation_object_configure_from_resource_0043e5a0.cpp"
#include "../../src/render/animation_manager_select_sprite_from_resource_004496a0.cpp"

#pragma code_seg(".text$zzcontext")
void __stdcall Ctx(AnimationHandle_004496a0** p, int n, Resource_0043e5a0* r) {
    for (int i = 0; i < n; ++i) p[i]->ConfigureFromResource(r, i);
}
#pragma code_seg()
