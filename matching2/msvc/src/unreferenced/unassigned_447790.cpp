// 0x00447790: answer 1 when every slot of the table at this+0x3AD06C is either
// null or holds a node whose +0x124 and +0x128 fields are both zero.
struct Node5 {
    unsigned char pad_000[0x124];
    void* field_124;
    void* field_128;
};
struct Table2 {
    unsigned char pad_000[0x3AD06C];
    Node5* slots[0x21];
    __declspec(noinline) int AllEmpty() const;
};
int Table2::AllEmpty() const {
    for (unsigned index = 0; index < 0x21; ++index) {
        Node5* node = slots[index];
        if (node != 0 && (node->field_128 != 0 || node->field_124 != 0)) {
            return 0;
        }
    }
    return 1;
}
