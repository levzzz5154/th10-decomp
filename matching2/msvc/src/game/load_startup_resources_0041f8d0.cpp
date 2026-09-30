// 0x0041F8D0: load front and bullet animation resources, logging the first failure.
// Co-compiled with TextLog::Append so its receiver uses ECX and its format
// remains a caller-cleaned stack argument.
struct TextLog_0044b810 {
    char text[0x2000];
    char *cursor;
    unsigned char dirty;
    char *Append(char *format, ...);
};
extern "C" void *__fastcall Recovery_LoadCachedResource_00447280(
        int index, void *owner, const char *name);
extern "C" void *data_00491c10;

#pragma code_seg(".text$00hbstartup")
extern "C" __declspec(noinline) int __cdecl LoadStartupResources_0041f8d0() {
    if (!Recovery_LoadCachedResource_00447280(
            6, data_00491c10, (const char *)0x0046D254)) {
        ((TextLog_0044b810 *)0x00474F70)->Append((char *)0x0046CB68);
        return -1;
    }
    if (!Recovery_LoadCachedResource_00447280(
            7, data_00491c10, (const char *)0x0046CD88)) {
        ((TextLog_0044b810 *)0x00474F70)->Append((char *)0x0046CD54);
        return -1;
    }
    return 0;
}
#pragma code_seg()
