extern "C" int (__stdcall *imp_IsBadReadPtr)(const void*, unsigned int);
extern "C" int __cdecl crt_ValidateRead(const void* ptr, unsigned int size) {
    int valid = 1;
    if (imp_IsBadReadPtr(ptr, size)) valid = 0;
    return valid;
}
