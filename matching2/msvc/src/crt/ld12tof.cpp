extern "C" int __cdecl crt_ld12cvt(const void*, void*, const void*);
extern "C" int g_crt_ld12tof_fmt;

extern "C" int __cdecl crt_ld12tod_45d5e4(const void* source, void* destination) {
    return crt_ld12cvt(source, destination, &g_crt_ld12tof_fmt);
}
