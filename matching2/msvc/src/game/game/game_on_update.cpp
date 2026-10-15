// 0x004187C0: the stage's update task: hands the object it was entered with to
// the routine at 0x00418190, which takes it on the stack and cleans the
// argument itself.  The caller passes the object in ECX, so this is the
// __fastcall entry point of the pair.
extern "C" void __stdcall asm_FUN_00418190_00418190(void* self);

void __fastcall Game_OnUpdate(void* self) {
    asm_FUN_00418190_00418190(self);
}
