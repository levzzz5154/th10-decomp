extern "C" unsigned char g_crt_exception_filter;
extern "C" __declspec(noreturn) void __cdecl crt_terminate();
extern "C" int __cdecl crt_ValidateExecute(const void*);
typedef int (__stdcall *ExceptionFilterFn)(void*);

extern "C" int __stdcall crt_CxxUnhandledExceptionFilter(void* pointers) {
    unsigned int* record = *reinterpret_cast<unsigned int**>(pointers);
    if (record[0] == 0xe06d7363 && record[4] == 3 &&
        (record[5] == 0x19930520 || record[5] == 0x19930521))
        crt_terminate();
    if (*reinterpret_cast<ExceptionFilterFn*>(&g_crt_exception_filter) &&
        crt_ValidateExecute(*reinterpret_cast<void**>(&g_crt_exception_filter)))
        return (*reinterpret_cast<ExceptionFilterFn*>(&g_crt_exception_filter))(pointers);
    return 0;
}
