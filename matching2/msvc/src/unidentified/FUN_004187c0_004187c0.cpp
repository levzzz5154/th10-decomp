// 0x004187C0..0x004187C6 - forwarder: hands the object it was entered with to
// the routine at 0x00418190, which takes it on the stack and cleans the
// argument itself.  The caller passes the object in ECX, so this is the
// __fastcall entry point of the pair.
extern "C" void __stdcall asm_FUN_00418190_00418190(void* self);

void __fastcall FUN_004187c0(void* self) {
    asm_FUN_00418190_00418190(self);
}
