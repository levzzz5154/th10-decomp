// 0x00421D20: release the cached COM interface, then clear its slot.
// The surrounding DirectInput state reaches this member through the native
// LTCG cluster in build_support/layout/ltcg/cached_com_slot_release_retail.json;
// that cluster preserves the retail ESI this-pointer convention.

struct CachedComInterfaceVtable {
    void* query_interface;
    void* add_reference;
    unsigned long (__stdcall *release)(void* interface_pointer);
};

struct CachedComInterface {
    CachedComInterfaceVtable* vtable;
};

struct CachedComSlot {
    unsigned char reserved_000[0x0C];
    CachedComInterface* cached_interface;

    __declspec(noinline) void Release();
};

#pragma code_seg(".text$01release")
void CachedComSlot::Release() {
    CachedComInterface* interface_pointer = cached_interface;
    if (interface_pointer != 0) {
        interface_pointer->vtable->release(interface_pointer);
        cached_interface = 0;
    }
}
#pragma code_seg()
