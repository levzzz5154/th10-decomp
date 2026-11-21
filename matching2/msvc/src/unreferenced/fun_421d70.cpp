// 0x00421D70: store a 16-bit value through the object pointer.
// Native LTCG keeps the object in EAX and the short argument in CX.
struct WordStore {
    unsigned short value;
    __declspec(noinline) void Store(short value);
};
typedef char WordStore_00421d70_size_must_fit[sizeof(WordStore) == 2 ? 1 : -1];

#pragma code_seg(".text$01store00421d70")
void WordStore::Store(short value) {
    this->value = (unsigned short)value;
}
#pragma code_seg()
