// 0x0040ABE0..0x0040ABE6 - forwarder: the object arrives in ECX and is pushed
// as the single stack argument of the routine at 0x0040A450, which cleans it.
extern "C" void __stdcall asm_FUN_0040a450_0040a450(void* self);

void __fastcall FUN_0040abe0(void* self) {
    asm_FUN_0040a450_0040a450(self);
}
