// 0X00401F70: clear the scale-velocity X word at +0x44 of the entity addressed through EAX (second entry).
// The object address arrives in EAX, so the function is compiled with the native
// LTCG cluster driver that reproduces the retail internal convention.

struct EntityScaleAlternate {
    char unknown[0x44];
    float scale_velocity_x;

    __declspec(noinline) void ClearScaleVelocityXAlternate();
};

#pragma code_seg(".text$01scale_vel_44b")
void EntityScaleAlternate::ClearScaleVelocityXAlternate() {
    this->scale_velocity_x = 0;
}
#pragma code_seg()
