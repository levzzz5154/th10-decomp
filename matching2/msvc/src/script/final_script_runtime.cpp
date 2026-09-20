// 0x00450470..0x004504F7: sorted script-table lookup.
//
// Native LTCG supplies the private retail convention for this member:
// the table object arrives in EAX, the label remains on the stack, and
// the integer result is returned with RET 4.
struct ScriptEntry_00450470 {
    const char* name;
    unsigned int value;
};

struct ScriptTable_00450470 {
    unsigned int reserved_00;
    unsigned int reserved_04;
    int count;
    unsigned int reserved_0C[0x20];
    const ScriptEntry_00450470* entries;

    __declspec(noinline) int Resolve(const char* name);
};

extern "C" int __cdecl strcmp(const char*, const char*);
#pragma intrinsic(strcmp)

#pragma code_seg(".text$01resolve")
__declspec(noinline) int ScriptTable_00450470::Resolve(const char* name) {
    int low = 0;
    int high = this->count;
    if (--high >= 0) {
        const ScriptEntry_00450470* entries = this->entries;
        do {
            const int middle = low + (high - low) / 2;
            const ScriptEntry_00450470* entry = &entries[middle];
            const int order = strcmp(name, entry->name);
            if (order == 0)
                return static_cast<int>(entry->value) + 16;
            if (order < 0)
                high = middle - 1;
            else
                low = middle + 1;
        } while (low <= high);
    }
    return 0;
}
#pragma code_seg()
