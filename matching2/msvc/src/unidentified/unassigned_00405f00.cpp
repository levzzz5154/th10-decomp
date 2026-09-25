// 0x00405F00: load bullet.anm into cached resource slot 7; when it is
// missing, log that the enemy-bullet data is missing and return -1.
// Compiled inside the bullet-manager native-LTCG cluster, which co-compiles
// TextLog::Append so its variadic receiver stays in ECX with caller cleanup.
struct TextLog_0044b810 {
    char text[0x2000];
    char *cursor;
    unsigned char dirty;
    char *Append(char *format, ...);
};

extern "C" void *__fastcall Recovery_LoadCachedResource_00447280(
        int index, void *owner, const char *name);
extern "C" void *data_00491c10;

#pragma code_seg(".text$00_xload")
extern "C" __declspec(noinline) int __cdecl LoadBulletAnm_00405f00() {
    if (!Recovery_LoadCachedResource_00447280(
            7, data_00491c10, (const char *)0x0046CD88)) {
        ((TextLog_0044b810 *)0x00474F70)->Append((char *)0x0046CD54);
        return -1;
    }
    return 0;
}
#pragma code_seg()
