extern "C" int data_00499314;
extern "C" int __cdecl asm_setmbcp_0045d15c(int);

extern "C" int __cdecl asm_initmbctable_0045d2ac() {
    if (!data_00499314) {
        asm_setmbcp_0045d15c(-3);
        data_00499314 = 1;
    }
    return 0;
}
