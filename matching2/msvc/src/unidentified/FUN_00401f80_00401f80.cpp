// 0X00401F80: clear the rotation X word at +0x24 of the entity addressed through EAX.
// The object address arrives in EAX, so the function is compiled with the native
// LTCG cluster driver that reproduces the retail internal convention.

struct EntityOrientation {
    char unknown[0x24];
    float rotation_x;

    __declspec(noinline) void ClearRotationX();
};

#pragma code_seg(".text$01rot_24")
void EntityOrientation::ClearRotationX() {
    this->rotation_x = 0;
}
#pragma code_seg()
