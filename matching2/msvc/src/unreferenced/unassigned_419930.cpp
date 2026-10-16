
struct SearchRecord {
    int value;
    int key;
};
int __declspec(noinline) FindKey(SearchRecord* table, int count, int key);

#pragma code_seg(".text$01find")
__declspec(noinline) int FindKey(SearchRecord* table, int count, int key) {
    for (int i = 0; i < count; ++i) {
        if (table[i].key == key) return table[i].value;
    }
    return 0;
}
#pragma code_seg()
