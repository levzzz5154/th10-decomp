extern "C" void* data_00473080[];
extern "C" void (__stdcall *imp_LeaveCriticalSection)(void*);

extern "C" void __cdecl asm_FUN_00453b3f_00453b3f(int index) {
    imp_LeaveCriticalSection(data_00473080[index * 2]);
}
