extern "C" void* __cdecl asm_malloc_00452706(unsigned int);
extern "C" void** data_00499310;
extern "C" void** data_0049930c;

extern "C" int __cdecl asm_onexitinit_00452daa() {
    data_00499310 = static_cast<void**>(asm_malloc_00452706(0x80));
    if (!data_00499310) return 0x18;
    *data_00499310 = 0;
    data_0049930c = data_00499310;
    return 0;
}
