extern "C" int (__stdcall *imp_CreateDirectoryA)(const char*, void*);
extern "C" unsigned long (__stdcall *imp_GetLastError)();
extern "C" void __cdecl crt_dosmaperr(unsigned long);

extern "C" int __cdecl crt_mkdir(const char* path) {
    unsigned long error;
    if (!imp_CreateDirectoryA(path, 0)) error = imp_GetLastError();
    else error = 0;
    if (error) {
        crt_dosmaperr(error);
        return -1;
    }
    return 0;
}
