// 0x00417750: unlink the node from its doubly-linked neighbours.
// The object pointer arrives in EAX, which only a native LTCG link chooses, so
// this region is compiled as a cluster.

struct ObjectAccessor_00417750 {
    unsigned char pad_000[0x04];
    ObjectAccessor_00417750* prev;
    ObjectAccessor_00417750* next;
    __declspec(noinline) void Unlink();
};

#pragma code_seg(".text$01accessor")
void ObjectAccessor_00417750::Unlink() {
    prev->next = next;
    if (next) {
        next->prev = prev;
    }
}
#pragma code_seg()
