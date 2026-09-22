extern "C" unsigned char data_004776d8;
extern "C" __declspec(noreturn) void __cdecl asm_terminate_00455693();
extern "C" int __cdecl asm_ValidateExecute_00463b02(const void*);
typedef int (__stdcall *ExceptionFilterFn)(void*);

extern "C" int __stdcall asm_CxxUnhandledExceptionFilter_00463a5c(void* pointers) {
    unsigned int* record = *reinterpret_cast<unsigned int**>(pointers);
    if (record[0] == 0xe06d7363 && record[4] == 3 &&
        (record[5] == 0x19930520 || record[5] == 0x19930521))
        asm_terminate_00455693();
    if (*reinterpret_cast<ExceptionFilterFn*>(&data_004776d8) &&
        asm_ValidateExecute_00463b02(*reinterpret_cast<void**>(&data_004776d8)))
        return (*reinterpret_cast<ExceptionFilterFn*>(&data_004776d8))(pointers);
    return 0;
}
