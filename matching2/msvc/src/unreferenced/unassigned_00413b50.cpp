// 0x00413B50: load front.anm into cached resource slot 6; when it is
// missing, log that the data is corrupt and return -1.
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
extern "C" void *g_sprt_ctrl;

#pragma code_seg(".text$00d_clload")
extern "C" __declspec(noinline) int __cdecl LoadFrontAnm_00413b50() {
    if (!Recovery_LoadCachedResource_00447280(
            6, g_sprt_ctrl, (const char *)0x0046D254)) {
        ((TextLog_0044b810 *)0x00474F70)->Append((char *)0x0046CB68);
        return -1;
    }
    return 0;
}
#pragma code_seg()
