// 0x0045FE75: the per-thread mode block, one field inside the per-thread data.

extern "C" char* __cdecl asm_getptd_00456357(void);

extern "C" char* __cdecl unassigned8(void) {
    return asm_getptd_00456357() + 0x5C;
}
