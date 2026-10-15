// 0x00421D20: release the cached COM interface, then clear its slot.
// The surrounding DirectInput state reaches this member through the native
// LTCG cluster in build_support/layout/ltcg/cached_com_slot_release_retail_00421d20.json;
// that cluster preserves the retail ESI this-pointer convention.

struct CachedComInterfaceVtable_00421d20 {
    void* query_interface;
    void* add_reference;
    unsigned long (__stdcall *release)(void* interface_pointer);
};

struct CachedComInterface_00421d20 {
    CachedComInterfaceVtable_00421d20* vtable;
};

struct CachedComSlot_00421d20 {
    unsigned char reserved_000[0x0C];
    CachedComInterface_00421d20* cached_interface;

    __declspec(noinline) void Release();
};

#pragma code_seg(".text$01release")
void CachedComSlot_00421d20::Release() {
    CachedComInterface_00421d20* interface_pointer = cached_interface;
    if (interface_pointer != 0) {
        interface_pointer->vtable->release(interface_pointer);
        cached_interface = 0;
    }
}
#pragma code_seg()
