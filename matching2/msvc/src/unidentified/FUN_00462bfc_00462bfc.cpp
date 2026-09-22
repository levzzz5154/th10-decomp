// 0x00462BFC..0x00462C00: Return the object pointer after consuming one argument.
// The unused fastcall arguments retain the retail ECX input and ret 4 cleanup.
extern "C" void* __fastcall asm_FUN_00462bfc_00462bfc(
        void* object, unsigned int unused_edx, unsigned int unused_stack) {
    (void)unused_edx;
    (void)unused_stack;
    return object;
}
