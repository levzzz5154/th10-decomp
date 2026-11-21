extern "C" int __cdecl crt_XcptFilter(unsigned int code, void* exception);

extern "C" int __cdecl crt_unassigned_457932(unsigned int code, void* exception) {
    if (code == 0xE06D7363) return crt_XcptFilter(code, exception);
    return 0;
}
