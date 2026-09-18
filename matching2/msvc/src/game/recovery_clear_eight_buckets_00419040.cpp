// 0x00419040..0x0041908E: release every chain a manager holds in its two
// eight-way bucket arrays.
//
// The region is entered by the game's internal EAX convention rather than by
// the ordinary MSVC thiscall ABI.  The native-LTCG cluster in
// layout/ltcg/recovery_clear_eight_buckets_00419040.json supplies that
// convention while keeping the recovered operation readable.

extern "C" void __cdecl entry_free_004524a1(void* memory);   // 0x004524A1

// One releasing chain node: the block to release, then the link to the next.
struct ChainNode_00419040 {
    void* block;
    ChainNode_00419040* next;
};

// One bucket: a chain head.  The rest of the element lies outside this region.
struct Bucket_00419040 {
    ChainNode_00419040* head;
    unsigned reserved_004[2];
};

struct Manager_00419040 {
    unsigned char reserved_000[0x1C];
    Bucket_00419040 primary[8];
    Bucket_00419040 secondary[8];

    __declspec(noinline) void ClearBuckets();
};

#pragma code_seg(".text$01accessor")
void Manager_00419040::ClearBuckets() {
    for (int index = 0; index < 8; ++index) {
        for (ChainNode_00419040* node = primary[index].head; node != 0; ) {
            ChainNode_00419040* next = node->next;
            entry_free_004524a1(node->block);
            node = next;
        }
        for (ChainNode_00419040* node = secondary[index].head; node != 0; ) {
            ChainNode_00419040* next = node->next;
            entry_free_004524a1(node->block);
            node = next;
        }
    }
}
#pragma code_seg()
