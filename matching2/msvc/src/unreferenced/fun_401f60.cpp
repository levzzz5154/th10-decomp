// 0X00401F60: clear the angular-velocity X word at +0x34 of the entity addressed through EAX.
// The object address arrives in EAX, so the function is compiled with the native
// LTCG cluster driver that reproduces the retail internal convention.

struct EntitySpin {
    char unknown[0x34];
    float angular_velocity_x;

    __declspec(noinline) void ClearAngularVelocityX();
};

#pragma code_seg(".text$01ang_vel_34")
void EntitySpin::ClearAngularVelocityX() {
    this->angular_velocity_x = 0;
}
#pragma code_seg()
