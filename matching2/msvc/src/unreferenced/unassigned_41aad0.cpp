// 0x0041AAD0: walk the bucket selected by the global index at 0x474C7C and
// retire one count from each element's counter at +0x70.

struct Chain {
    Chain* inner;               // +0x00
    Chain* next;                // +0x04
    unsigned char pad_008[0x70 - 0x08];
    int count;                           // +0x70
};

struct Entry2 {
    Chain* head;                // +0x00
    unsigned int reserved[2];
};

struct ObjectAccessor_0041aad0 {
    unsigned char pad_000[0x7C];
    Entry2 entries[];            // +0x7C, stride 12
    __declspec(noinline) void RetireCounts();
};

extern "C" int g_globals_stage;

void ObjectAccessor_0041aad0::RetireCounts() {
    Chain* node = entries[g_globals_stage].head;
    while (node) {
        Chain* next = node->next;
        Chain* inner = node->inner;
        if (inner->count > 0) {
            --inner->count;
        }
        node = next;
    }
}
