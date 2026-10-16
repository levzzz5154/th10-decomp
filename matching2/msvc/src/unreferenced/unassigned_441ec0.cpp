// 0x00441EC0..0x00441EED: look up the resource selected by an object and
// report whether the selected entry has its status field set.

struct LookupResource {
    int index;
};

struct LookupObject {
    unsigned char pad_000[0x394];
    LookupResource* resource;
};

struct LookupEntry {
    unsigned char pad_000[0x120];
    int status;
};

struct LookupManager {
    unsigned char pad_000[0x3AD06C];
    LookupEntry* entries[1];
};

#pragma code_seg(".text$01lookup")
__declspec(noinline) int ResolveLookup(
        LookupObject* object, LookupManager* manager) {
    LookupResource* resource = object->resource;
    if (resource == 0)
        return 0;

    int index = resource->index;
    if (index < 0)
        return 0;

    LookupEntry* entry = manager->entries[index];
    if (entry == 0)
        return 0;
    return entry->status != 0;
}
#pragma code_seg()
