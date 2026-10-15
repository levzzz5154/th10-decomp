// 0x00426500..0x00426506: thunk that forwards its ECX argument to the
// scheduler routine at 0x00425730 and returns that call's result unchanged.
// The callee is entered through a __stdcall pointer type: retail consumes the
// pushed argument inside the callee, so no caller-side cleanup is emitted.
extern "C" int __cdecl asm_FUN_00425730_00425730(void*);

int __fastcall Player_OnUpdate(void* a1, int a2) {
    return ((int (__stdcall*)(void*))asm_FUN_00425730_00425730)(a1);
}
