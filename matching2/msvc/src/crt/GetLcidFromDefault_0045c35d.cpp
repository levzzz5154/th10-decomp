extern "C" unsigned short data_00477628;
extern "C" unsigned int data_00477630;
extern "C" unsigned int data_0047762c;
extern "C" unsigned int (__stdcall *data_00466060)();

extern "C" void __cdecl asm_GetLcidFromDefault_0045c35d() {
    data_00477628 |= 0x104;
    data_00477630 = data_00466060();
    data_0047762c = data_00477630;
}
