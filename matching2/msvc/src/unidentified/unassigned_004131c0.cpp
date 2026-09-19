// 0x004131C0: unlink the node and clear its two links
// The register convention below is only reachable from a native LTCG link,
// so this region is compiled as a cluster.

struct Node_004131c0 {
    unsigned char pad_000[0x04];
    Node_004131c0* prev;   // +0x04
    Node_004131c0* next;   // +0x08
    __declspec(noinline) void Remove();
};
#pragma code_seg(".text$01accessor")
void Node_004131c0::Remove() {
    if (prev) {
        prev->next = next;
    }
    if (next) {
        next->prev = prev;
    }
    prev = 0;
    next = 0;
}
#pragma code_seg()
