extern "C" unsigned char data_004776d8;
extern "C" unsigned char imp_SetUnhandledExceptionFilter;
extern "C" int __stdcall asm_CxxUnhandledExceptionFilter_00463a5c(void*);
typedef void* (__stdcall *SetUnhandledExceptionFilterFn)(void*);

extern "C" int __cdecl asm_unassigned_00463aaa() {
    *reinterpret_cast<void**>(&data_004776d8) =
        (*reinterpret_cast<SetUnhandledExceptionFilterFn*>(&imp_SetUnhandledExceptionFilter))(
            reinterpret_cast<void*>(&asm_CxxUnhandledExceptionFilter_00463a5c));
    return 0;
}

extern "C" void* __cdecl asm_unassigned_00463abd() {
    return (*reinterpret_cast<SetUnhandledExceptionFilterFn*>(&imp_SetUnhandledExceptionFilter))(
        *reinterpret_cast<void**>(&data_004776d8));
}
