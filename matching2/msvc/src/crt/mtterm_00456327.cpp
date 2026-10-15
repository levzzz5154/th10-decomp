extern "C" int data_00473390;
extern "C" void (__stdcall *data_00477380)(int);
extern "C" void __cdecl asm_mtdeletelocks_00453aea();

extern "C" void __cdecl asm_mtterm_00456327() {
    if (data_00473390 != -1) {
        data_00477380(data_00473390);
        data_00473390 = -1;
    }
    asm_mtdeletelocks_00453aea();
}
