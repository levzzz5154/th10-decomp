extern "C" unsigned char g_crt_exception_filter;
extern "C" unsigned char imp_SetUnhandledExceptionFilter;
extern "C" int __stdcall crt_CxxUnhandledExceptionFilter(void*);
typedef void* (__stdcall *SetUnhandledExceptionFilterFn)(void*);

extern "C" int __cdecl crt_unassigned_463aaa() {
    *reinterpret_cast<void**>(&g_crt_exception_filter) =
        (*reinterpret_cast<SetUnhandledExceptionFilterFn*>(&imp_SetUnhandledExceptionFilter))(
            reinterpret_cast<void*>(&crt_CxxUnhandledExceptionFilter));
    return 0;
}

extern "C" void* __cdecl crt_unassigned_463abd() {
    return (*reinterpret_cast<SetUnhandledExceptionFilterFn*>(&imp_SetUnhandledExceptionFilter))(
        *reinterpret_cast<void**>(&g_crt_exception_filter));
}
