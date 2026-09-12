// 0x0044D300 - Query an interface and restore it until it is ready.
extern "C" __declspec(dllimport) void __stdcall Sleep(unsigned int);

struct PlatformD300Entry {
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
    virtual void __stdcall slot_28() = 0;
    virtual void __stdcall slot_2c() = 0;
    virtual void __stdcall slot_30() = 0;
    virtual void __stdcall slot_34() = 0;
    virtual void __stdcall slot_38() = 0;
    virtual void __stdcall slot_3c() = 0;
    virtual void __stdcall slot_40() = 0;
    virtual void __stdcall slot_44() = 0;
    virtual void __stdcall slot_48() = 0;
    virtual void __stdcall slot_4c() = 0;
    virtual int __stdcall restore() = 0;

    __declspec(noinline) int Run(unsigned int* completed);
};

#pragma code_seg(".text$01run")
__declspec(noinline) int PlatformD300Entry::Run(unsigned int* completed) {
    unsigned int state;
    if (this == 0)
        return (int)0x800401F0u;
    if (completed != 0)
        *completed = 0;

    int result = read_state(&state);
    if (result < 0)
        return result;
    if ((state & 2) != 0) {
        for (;;) {
            if (restore() == (int)0x88780096u)
                Sleep(10);
            if (restore() != 0)
                continue;
            if (completed != 0)
                *completed = 1;
            return 0;
        }
    }
    return 1;
}
#pragma code_seg()
