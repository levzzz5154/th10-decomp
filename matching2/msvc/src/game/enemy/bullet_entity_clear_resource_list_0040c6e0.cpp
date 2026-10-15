// 0x0040C6E0..0x0040C70C: release every resource record attached to a bullet.
//
// This member is entered by the game's internal EAX convention rather than by
// the ordinary MSVC thiscall ABI.  The native-LTCG cluster in
// build_support/layout/ltcg/bullet_entity_clear_resource_list.json supplies that
// convention while keeping the recovered operation readable.

extern "C" void __cdecl crt_free_startup(void* memory);

struct BulletResourceRecord {
    void* resource;
    BulletResourceRecord* next;
};

struct BulletEntity_0040c6e0 {
    unsigned char reserved_000[0x1034];
    BulletResourceRecord* resource_records;

    __declspec(noinline) void ClearResourceList();
};

#pragma code_seg(".text$01clear")
void BulletEntity_0040c6e0::ClearResourceList() {
    BulletResourceRecord* record = resource_records;
    while (record != 0) {
        BulletResourceRecord* next = record->next;
        crt_free_startup(record->resource);
        crt_free_startup(record);
        record = next;
    }
}
#pragma code_seg()
