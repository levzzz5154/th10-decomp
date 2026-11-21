struct NameEntry { const char* name; const char* value; };
extern "C" int __cdecl crt_stricmp(const char*, const char*);

extern "C" int __cdecl crt_libcmt_getqloc_TranslateName(NameEntry* entries, int high, const char** key) {
    int low = 0;
    int comparison = 1;
    if (high >= 0) {
        do {
            if (comparison == 0) break;
            int middle = (high + low) / 2;
            NameEntry* entry = entries + middle;
            comparison = crt_stricmp(*key, entry->name);
            if (comparison == 0) *key = reinterpret_cast<const char*>(&entry->value);
            else if (comparison < 0) high = middle - 1;
            else low = middle + 1;
        } while (low <= high);
    }
    return comparison == 0;
}
