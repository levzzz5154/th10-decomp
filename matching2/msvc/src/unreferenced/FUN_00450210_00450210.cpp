// 0x00450210: store a float through the destination pointer at +0x04.
// The object arrives in EAX and the float on the stack (RET 4).
struct FloatSlot {
    int reserved_000;
    float* target;                  // +0x04
    __declspec(noinline) void Store(float value);
};

#pragma code_seg(".text$01accessor")
void FloatSlot::Store(float value) {
    *target = value;
}
#pragma code_seg()
