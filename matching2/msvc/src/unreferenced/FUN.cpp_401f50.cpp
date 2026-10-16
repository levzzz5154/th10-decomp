// 0X00401F50: clear the scale-velocity X word at +0x44 of the entity addressed through EAX.
// The object address arrives in EAX, so the function is compiled with the native
// LTCG cluster driver that reproduces the retail internal convention.

struct EntityMotion {
    char unknown[0x44];
    float scale_velocity_x;

    __declspec(noinline) void ClearScaleVelocityX();
};

#pragma code_seg(".text$01scale_vel_44")
void EntityMotion::ClearScaleVelocityX() {
    this->scale_velocity_x = 0;
}
#pragma code_seg()
