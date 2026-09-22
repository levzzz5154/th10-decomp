extern "C" void* (__stdcall *data_0046618c)(unsigned int, unsigned int, unsigned int);
extern "C" int (__stdcall *data_00466190)(void*);
extern "C" void* data_00499340;
extern "C" int data_00499344;
extern "C" int __cdecl asm_heap_select_004539b1();
extern "C" int __cdecl asm_sbh_heap_init_00453c52(unsigned int);

extern "C" int __cdecl asm_heap_init_004539cb(int flag) {
    data_00499340 = data_0046618c(flag == 0, 0x1000, 0);
    if (!data_00499340) return 0;
    data_00499344 = asm_heap_select_004539b1();
    if (data_00499344 == 3 && !asm_sbh_heap_init_00453c52(0x3f8)) {
        data_00466190(data_00499340);
        return 0;
    }
    return 1;
}
