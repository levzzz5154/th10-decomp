// 0x00462BF1..0x00462BFB: Initialize the object's virtual table pointer.
// The unused fastcall arguments retain the retail ECX input and ret 4 cleanup.
extern "C" void* __fastcall asm_FUN_00462bf1_00462bf1(
        void* object, unsigned int unused_edx, unsigned int unused_stack) {
    (void)unused_edx;
    (void)unused_stack;
    *reinterpret_cast<unsigned int*>(object) = 0x0046ca54;
    return object;
}
