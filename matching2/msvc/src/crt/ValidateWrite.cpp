extern "C" int (__stdcall *imp_IsBadWritePtr)(void*, unsigned int);
extern "C" int __cdecl crt_ValidateWrite(void* ptr, unsigned int size) {
    int valid = 1;
    if (imp_IsBadWritePtr(ptr, size)) valid = 0;
    return valid;
}
