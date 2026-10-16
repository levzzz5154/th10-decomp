struct ObjectAccessor_0040c6d0 {
    unsigned char pad_000[4];
    float* field_004;
    __declspec(noinline) void Subtract(float amount);
};

#pragma code_seg(".text$01adjust")
void ObjectAccessor_0040c6d0::Subtract(float amount) {
    *field_004 -= amount;
}
#pragma code_seg()
