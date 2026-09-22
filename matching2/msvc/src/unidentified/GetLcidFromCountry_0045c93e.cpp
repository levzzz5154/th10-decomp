extern "C" char* data_0047763c;
extern "C" unsigned int data_00477638;
extern "C" unsigned int data_00477628;
extern "C" unsigned int __cdecl asm_strlen_00456720(const char*);
extern "C" int (__stdcall *data_00466058)(void*, unsigned int);
extern "C" int __stdcall asm_FUN_0045c544_0045c544(char*);

extern "C" void __cdecl asm_GetLcidFromCountry_0045c93e() {
    data_00477638 = asm_strlen_00456720(data_0047763c) == 3;
    data_00466058(reinterpret_cast<void*>(&asm_FUN_0045c544_0045c544), 1);
    if (!(data_00477628 & 4)) data_00477628 = 0;
}
