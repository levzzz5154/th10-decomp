// 0x00441EC0..0x00441EED: look up the resource selected by an object and
// report whether the selected entry has its status field set.

struct LookupResource_00441ec0 {
    int index;
};

struct LookupObject_00441ec0 {
    unsigned char pad_000[0x394];
    LookupResource_00441ec0* resource;
};

struct LookupEntry_00441ec0 {
    unsigned char pad_000[0x120];
    int status;
};

struct LookupManager_00441ec0 {
    unsigned char pad_000[0x3AD06C];
    LookupEntry_00441ec0* entries[1];
};

#pragma code_seg(".text$01lookup")
__declspec(noinline) int ResolveLookup_00441ec0(
        LookupObject_00441ec0* object, LookupManager_00441ec0* manager) {
    LookupResource_00441ec0* resource = object->resource;
    if (resource == 0)
        return 0;

    int index = resource->index;
    if (index < 0)
        return 0;

    LookupEntry_00441ec0* entry = manager->entries[index];
    if (entry == 0)
        return 0;
    return entry->status != 0;
}
#pragma code_seg()
