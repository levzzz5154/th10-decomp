// The size routine at 0x00415800 is still an assembly region: it takes its one
// argument on the stack and pops it (`ret 4`), so the call is issued through a
// __stdcall pointer while the bound symbol keeps its __cdecl spelling.
extern "C" int __cdecl asm_FUN_00415800_00415800(int arg);
typedef int (__stdcall* SizeFromCtx8Fn)(int object);

// 0x00415AF0..0x00415AF6: FUN_00415af0
// Recovered: forwarding stub - hands the object to the 0x00415800 size routine.
int __fastcall FUN_00415af0(void* self) {
    return ((SizeFromCtx8Fn)asm_FUN_00415800_00415800)((int)self);
}
