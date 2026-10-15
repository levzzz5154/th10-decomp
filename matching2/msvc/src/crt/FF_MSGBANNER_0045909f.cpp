extern "C" int data_0047720c;
extern "C" int data_00473074;
extern "C" void (__cdecl *data_004774b4)();
extern "C" void __cdecl asm_FUN_00458efd_00458efd(int);

extern "C" void __cdecl asm_FF_MSGBANNER_0045909f() {
    if (data_0047720c == 1 || (data_0047720c == 0 && data_00473074 == 1)) {
        asm_FUN_00458efd_00458efd(0xfc);
        if (data_004774b4) data_004774b4();
        asm_FUN_00458efd_00458efd(0xff);
    }
}
