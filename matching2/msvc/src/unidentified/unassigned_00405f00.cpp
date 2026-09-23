// 0x00405F00..0x00405F31: load one cached resource and report a missing entry.
// Keep the existing C-linkage name while regions.json still maps this address
// to _asm_unassigned_00405f00; the body below is ordinary C++.

struct TextLog_0044b810 {
    char text[0x2000];
    char *cursor;
    unsigned char dirty;
    char *Append(char *format, ...);
};

extern "C" void * __fastcall Recovery_LoadCachedResource_00447280(
        int id, void *cache, const char *name);
extern "C" void *data_00491c10;

extern "C" __declspec(noinline) int __cdecl asm_unassigned_00405f00() {
    void *resource = Recovery_LoadCachedResource_00447280(
            7, data_00491c10, (const char *)0x0046CD88);
    if (!resource) {
        ((TextLog_0044b810 *)0x00474F70)->Append((char *)0x0046CD54);
        return -1;
    }

    return 0;
}
