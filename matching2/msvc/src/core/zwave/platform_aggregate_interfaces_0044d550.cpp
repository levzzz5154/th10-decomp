// 0x0044D550 - Stop and query every configured interface, combining HRESULTs.
typedef int (__stdcall *PlatformD550Unary)(void*);
typedef int (__stdcall *PlatformD550Query)(void*, unsigned int);

struct PlatformD550Vtable {
    void* before_query[0x34 / 4];
    PlatformD550Query query;
    void* between_query_and_stop[(0x48 - 0x38) / 4];
    PlatformD550Unary stop;
};

struct PlatformD550Entry {
    PlatformD550Vtable* vtable;
};

struct PlatformInterfaceState_0044D550 {
    unsigned char unknown_000[4];
    void** entries_004;
    unsigned char unknown_008[8];
    unsigned int count_010;
    unsigned char unknown_014[8];
    unsigned int active_01c;
    unsigned char unknown_020[0x10];
    unsigned int operation_030;

    __declspec(noinline) int Aggregate();
};

#pragma code_seg(".text$01aggregate")
__declspec(noinline) int PlatformInterfaceState_0044D550::Aggregate() {
    if (entries_004 == 0)
        return (int)0x800401F0u;

    int result = 0;
    operation_030 = 0;
    for (unsigned int index = 0; index < count_010; ++index) {
        PlatformD550Entry* entry =
            reinterpret_cast<PlatformD550Entry**>(entries_004)[index];
        result |= entry->vtable->stop(entry);
        entry = reinterpret_cast<PlatformD550Entry**>(entries_004)[index];
        result |= entry->vtable->query(entry, 0);
    }
    active_01c = 0;
    return result;
}
#pragma code_seg()
