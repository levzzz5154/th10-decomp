struct NameEntry { const char* name; const char* value; };
extern "C" int __cdecl asm_stricmp_0046054e(const char*, const char*);

extern "C" int __cdecl asm_TranslateName_0045c2fd(NameEntry* entries, int high, const char** key) {
    int low = 0;
    int comparison = 1;
    if (high >= 0) {
        do {
            if (comparison == 0) break;
            int middle = (high + low) / 2;
            NameEntry* entry = entries + middle;
            comparison = asm_stricmp_0046054e(*key, entry->name);
            if (comparison == 0) *key = reinterpret_cast<const char*>(&entry->value);
            else if (comparison < 0) high = middle - 1;
            else low = middle + 1;
        } while (low <= high);
    }
    return comparison == 0;
}
