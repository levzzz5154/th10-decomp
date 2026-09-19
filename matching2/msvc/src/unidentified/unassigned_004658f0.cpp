
extern "C" void __stdcall Init_00421f00(void* object);
extern "C" void __cdecl Register_00452e0a(void* entry);
extern "C" char data_00491c28;
#pragma code_seg(".text$03start")
__declspec(noinline) void StartThread_004658f0() {
    Init_00421f00(&data_00491c28);
    Register_00452e0a((void*)0x4659F0);
}
#pragma code_seg()
