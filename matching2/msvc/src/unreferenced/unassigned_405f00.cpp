// 0x00405F00: load bullet.anm into cached resource slot 7; when it is
// missing, log that the enemy-bullet data is missing and return -1.
// Compiled inside the bullet-manager native-LTCG cluster, which co-compiles
// TextLog::Append so its variadic receiver stays in ECX with caller cleanup.
struct TextLog4 {
    char text[0x2000];
    char *cursor;
    unsigned char dirty;
    char *Append(char *format, ...);
};

extern "C" void *__fastcall Recovery_LoadCachedResource(
        int index, void *owner, const char *name);
extern "C" void *g_sprt_ctrl;

#pragma code_seg(".text$00_xload")
extern "C" __declspec(noinline) int __cdecl LoadBulletAnm() {
    if (!Recovery_LoadCachedResource(
            7, g_sprt_ctrl, (const char *)0x0046CD88)) {
        ((TextLog4 *)0x00474F70)->Append((char *)0x0046CD54);
        return -1;
    }
    return 0;
}
#pragma code_seg()
