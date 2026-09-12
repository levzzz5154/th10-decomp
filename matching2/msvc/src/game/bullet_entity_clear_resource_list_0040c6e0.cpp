// 0x0040C6E0..0x0040C70C: release every resource record attached to a bullet.
//
// This member is entered by the game's internal EAX convention rather than by
// the ordinary MSVC thiscall ABI.  The native-LTCG cluster in
// layout/ltcg/bullet_entity_clear_resource_list_0040c6e0.json supplies that
// convention while keeping the recovered operation readable.

extern "C" void __cdecl entry_free_004524a1(void* memory);

struct BulletResourceRecord_0040c6e0 {
    void* resource;
    BulletResourceRecord_0040c6e0* next;
};

struct BulletEntity_0040c6e0 {
    unsigned char reserved_000[0x1034];
    BulletResourceRecord_0040c6e0* resource_records;

    __declspec(noinline) void ClearResourceList();
};

#pragma code_seg(".text$01clear")
void BulletEntity_0040c6e0::ClearResourceList() {
    BulletResourceRecord_0040c6e0* record = resource_records;
    while (record != 0) {
        BulletResourceRecord_0040c6e0* next = record->next;
        entry_free_004524a1(record->resource);
        entry_free_004524a1(record);
        record = next;
    }
}
#pragma code_seg()
