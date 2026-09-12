// 0x0044D4E0 - Install a randomized or fallback interface deadline.
extern "C" int data_00497854;

struct PlatformD4E0Entry {
    virtual void __stdcall slot_00() = 0;
    virtual void __stdcall slot_04() = 0;
    virtual void __stdcall slot_08() = 0;
    virtual void __stdcall slot_0c() = 0;
    virtual void __stdcall slot_10() = 0;
    virtual void __stdcall slot_14() = 0;
    virtual void __stdcall slot_18() = 0;
    virtual void __stdcall slot_1c() = 0;
    virtual void __stdcall slot_20() = 0;
    virtual void __stdcall slot_24() = 0;
    virtual void __stdcall slot_28() = 0;
    virtual void __stdcall slot_2c() = 0;
    virtual void __stdcall slot_30() = 0;
    virtual void __stdcall slot_34() = 0;
    virtual void __stdcall slot_38() = 0;
    virtual int __stdcall set_deadline(int) = 0;
};

struct PlatformInterfaceState_0044D4E0 {
    unsigned char unknown_000[4];
    PlatformD4E0Entry** entries_004;

    __declspec(noinline) int SetOperationDeadline(int deadline);
};

#pragma code_seg(".text$01deadline")
__declspec(noinline) int
PlatformInterfaceState_0044D4E0::SetOperationDeadline(int deadline) {
    if (data_00497854 != 0) {
        float factor = 1.0f - (float)data_00497854 * 0.01f;
        int value = (int)((1.0f - factor * factor) * (deadline + 5000));
        return entries_004[0]->set_deadline(value - 5000);
    }
    return entries_004[0]->set_deadline(-10000);
}
#pragma code_seg()
