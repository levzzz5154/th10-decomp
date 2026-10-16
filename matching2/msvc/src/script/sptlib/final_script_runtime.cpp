#include "script_resolver.hpp"

extern "C" int __cdecl strcmp(const char*, const char*);
#pragma intrinsic(strcmp)

#pragma code_seg(".text$01resolve")
__declspec(noinline) int ScriptTable2::Resolve(const char* name) {
    int low = 0;
    int high = this->count;
    if (--high >= 0) {
        const ScriptEntry3* entries = this->entries;
        do {
            const int middle = low + (high - low) / 2;
            const ScriptEntry3* entry = &entries[middle];
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
