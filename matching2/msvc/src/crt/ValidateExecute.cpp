extern "C" int (__stdcall *imp_IsBadCodePtr)(const void*);
extern "C" int __cdecl crt_ValidateExecute(const void* ptr) {
    int valid = 1;
    if (imp_IsBadCodePtr(ptr)) valid = 0;
    return valid;
}
