// 0x0044D370 - Select the first idle interface, or a random fallback.
extern "C" int __cdecl asm_rand_0045371b();

struct PlatformD370Entry {
    virtual void __stdcall slot_00() = 0;
    virtual void __stdcall slot_04() = 0;
    virtual void __stdcall slot_08() = 0;
    virtual void __stdcall slot_0c() = 0;
    virtual void __stdcall slot_10() = 0;
    virtual void __stdcall slot_14() = 0;
    virtual void __stdcall slot_18() = 0;
    virtual void __stdcall slot_1c() = 0;
    virtual void __stdcall slot_20() = 0;
    virtual int __stdcall read_state(unsigned int*) = 0;
};

struct PlatformInterfaceState_0044D370 {
    unsigned char unknown_000[4];
    void** entries_004;
    unsigned char unknown_008[8];
    unsigned int count_010;

    __declspec(noinline) PlatformD370Entry* FindAvailable();
};

#pragma code_seg(".text$01find")
__declspec(noinline) PlatformD370Entry*
PlatformInterfaceState_0044D370::FindAvailable() {
    if (entries_004 == 0)
        return 0;

    unsigned int index = 0;
    for (; index < count_010; ++index) {
        if (entries_004[index] != 0) {
            unsigned int state = 0;
            reinterpret_cast<PlatformD370Entry*>(entries_004[index])
                ->read_state(&state);
            if ((state & 1) == 0)
                break;
        }
    }
    if (index != count_010)
        return reinterpret_cast<PlatformD370Entry*>(entries_004[index]);
    return reinterpret_cast<PlatformD370Entry*>(
        entries_004[(unsigned int)asm_rand_0045371b() % count_010]);
}
#pragma code_seg()
