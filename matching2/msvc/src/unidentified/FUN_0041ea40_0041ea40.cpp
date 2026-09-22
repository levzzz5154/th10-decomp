// 0x0041EA40: synchronize and draw the boss's embedded overlay VMs.
// Public ECX scheduler receiver. The render dispatcher is the real definition
// co-compiled in anm_batch_flush_00442f50, giving it ECX manager / EAX entity.
// Explicit subobject views preserve the retail load/store ordering; the
// offsetof checks below tie every view to the actual embedded field layout.
#include "th10/render/quad_batch.hpp"
#include "th10/math/angle.hpp"
#include <stddef.h>
extern "C" __declspec(noinline) int __cdecl asm_FUN_004451c0_004451c0(
    AnimationManager_00442F50* manager, RenderEntity* entity);
struct BossOverlay_0041EA40 {
    unsigned char reserved_000[0x24];
    RenderVec3 position;
    unsigned char reserved_030[0x3C - 0x30];
    float angle;
    unsigned char reserved_040[0x4C - 0x40];
    float secondary_visibility;
    unsigned char reserved_050[0x61C - 0x50];
    RenderEntity primary;
    unsigned char reserved_between[0x3AC - sizeof(RenderEntity)];
    RenderEntity secondary;
    __declspec(noinline) int Draw();
};
typedef char BossOverlay_0041EA40_PrimaryOffset[(offsetof(BossOverlay_0041EA40, primary) == 0x61C) ? 1 : -1];
typedef char BossOverlay_0041EA40_SecondaryOffset[(offsetof(BossOverlay_0041EA40, secondary) == 0x9C8) ? 1 : -1];
typedef char BossOverlay_0041EA40_PrimaryPositionOffset[(offsetof(BossOverlay_0041EA40, primary) + offsetof(RenderEntity, base_position) == 0x950) ? 1 : -1];
typedef char BossOverlay_0041EA40_SecondaryPositionOffset[(offsetof(BossOverlay_0041EA40, secondary) + offsetof(RenderEntity, base_position) == 0xCFC) ? 1 : -1];
#pragma code_seg(".text$001z2boss")
int BossOverlay_0041EA40::Draw() {
    RenderEntity* vm = (RenderEntity*)((unsigned char*)this + 0x61C);
    RenderVec3& primary_position = *(RenderVec3*)((unsigned char*)this + 0x950);
    primary_position.x = position.x + 224.0f;
    primary_position.y = position.y + 16.0f;
    primary_position.z = position.z;
    vm->rotation.z = Angle_NormalizeSum(angle, 1.57079632679489661923f);
    vm->flags |= 4;
    asm_FUN_004451c0_004451c0(data_00491c10, vm);
    if (secondary_visibility == 0.0f) {
        RenderVec3& secondary_position = *(RenderVec3*)((unsigned char*)this + 0xCFC);
        secondary_position.x = position.x + 224.0f;
        secondary_position.y = position.y + 16.0f;
        secondary_position.z = position.z;
        asm_FUN_004451c0_004451c0(data_00491c10, &secondary);
    }
    return 0;
}
#pragma code_seg()
