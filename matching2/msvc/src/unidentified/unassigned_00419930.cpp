
struct SearchRecord_00419930 {
    int value;
    int key;
};
int __declspec(noinline) FindKey_00419930(SearchRecord_00419930* table, int count, int key);

#pragma code_seg(".text$01find")
__declspec(noinline) int FindKey_00419930(SearchRecord_00419930* table, int count, int key) {
    for (int i = 0; i < count; ++i) {
        if (table[i].key == key) return table[i].value;
    }
    return 0;
}
#pragma code_seg()
