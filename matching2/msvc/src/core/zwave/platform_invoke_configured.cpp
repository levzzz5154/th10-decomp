// 0x0044D5D0 - Invoke the configured interface operation.
typedef int (__stdcall *PlatformD5D0Invoke)(
        void*, unsigned int, unsigned int, unsigned int);

struct PlatformD5D0Vtable {
    void* before_invoke[0x30 / 4];
    PlatformD5D0Invoke invoke;
};

struct PlatformD5D0Entry {
    PlatformD5D0Vtable* vtable;
};

struct PlatformInterfaceState4 {
    unsigned char unknown_000[4];
    PlatformD5D0Entry** entries_004;
    unsigned char unknown_008[0x18];
    unsigned int first_020;
    unsigned int second_024;
    unsigned char unknown_028[8];
    unsigned int operation_030;

    __declspec(noinline) int InvokeConfigured();
};

#pragma code_seg(".text$01invoke")
__declspec(noinline) int PlatformInterfaceState4::InvokeConfigured() {
    PlatformD5D0Entry** entries = entries_004;
    if (entries == 0)
        return (int)0x800401F0u;

    PlatformD5D0Entry* entry = entries[0];
    operation_030 = 1;
    return entry->vtable->invoke(entry, 0, first_020, second_024);
}
#pragma code_seg()
