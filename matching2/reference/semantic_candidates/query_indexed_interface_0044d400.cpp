#include <stdint.h>

struct PlatformInterface_0044d400;

struct PlatformInterfaceVTable_0044d400 {
    int (__stdcall *query_interface)(PlatformInterface_0044d400* self,
                                     const void* interface_id, void** result);
};

struct PlatformInterface_0044d400 {
    PlatformInterfaceVTable_0044d400* vtable;
};

struct PlatformInterfaceState_0044d400 {
    uint32_t unknown_000;
    PlatformInterface_0044d400** entries;
    uint32_t unknown_008;
    uint32_t unknown_00c;
    uint32_t count;
};

extern "C" const unsigned char data_0046747c[16];

// Retail 0x0044D400..0x0044D433 receives state, index, and output in
// EAX, EDX, and ECX respectively. The output is cleared only for valid slots.
extern "C" int __cdecl QueryIndexedPlatformInterface_0044d400(
    const PlatformInterfaceState_0044d400* state, unsigned int index,
    void** result) {
    if (state->entries == 0)
        return static_cast<int>(0x800401F0u);
    if (index >= state->count)
        return static_cast<int>(0x80070057u);

    *result = 0;
    PlatformInterface_0044d400* entry = state->entries[index];
    return entry->vtable->query_interface(entry, data_0046747c, result);
}
