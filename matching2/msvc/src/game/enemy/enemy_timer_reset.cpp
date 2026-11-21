// 0x00412DB0: lazily initialize, then reset, an embedded timer record.
struct RecoveryTimer3 {
    unsigned char pad_000[0x20];
    int value;
    int current;
    int previous;
    void* speed;
    unsigned int initialized;

    __declspec(noinline) void Reset();
};

#pragma code_seg(".text$01timerreset00412db0")
void RecoveryTimer3::Reset() {
    if ((initialized & 1) == 0) {
        current = 0;
        value = -999999;
        previous = 0;
        speed = (void*)0x00476F78;
        initialized |= 1;
    }
    current = 0;
    previous = 0;
    value = -1;
}
#pragma code_seg()
