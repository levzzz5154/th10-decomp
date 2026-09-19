// 0x00447790: answer 1 when every slot of the table at this+0x3AD06C is either
// null or holds a node whose +0x124 and +0x128 fields are both zero.
struct Node_00447790 {
    unsigned char pad_000[0x124];
    void* field_124;
    void* field_128;
};
struct Table_00447790 {
    unsigned char pad_000[0x3AD06C];
    Node_00447790* slots[0x21];
    __declspec(noinline) int AllEmpty() const;
};
int Table_00447790::AllEmpty() const {
    for (unsigned index = 0; index < 0x21; ++index) {
        Node_00447790* node = slots[index];
        if (node != 0 && (node->field_128 != 0 || node->field_124 != 0)) {
            return 0;
        }
    }
    return 1;
}
