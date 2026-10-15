typedef int (__cdecl *NewHandler)(unsigned int);
extern "C" NewHandler data_00477360;
extern "C" void __cdecl asm_lock_00453c0c(int lock);
extern "C" void __cdecl asm_FUN_00453b3f_00453b3f(int lock);

extern "C" NewHandler __cdecl asm_unassigned_0045570d(NewHandler handler) {
    asm_lock_00453c0c(4);
    NewHandler previous = data_00477360;
    data_00477360 = handler;
    asm_FUN_00453b3f_00453b3f(4);
    return previous;
}
