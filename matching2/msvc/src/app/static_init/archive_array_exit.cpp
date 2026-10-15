// 0x00465A00: atexit destructor of the twenty 16-byte archive records at
// 0x004923B0 (constructed by StaticInit_ArchiveArray).
extern "C" void __stdcall asm_eh_vector_destructor_iterator_004525ff(void* base, unsigned int size, unsigned int count, void* destructor);
extern "C" unsigned char data_004923b0;
extern "C" void __cdecl asm_DatArchive_Reset_00434c20();

extern "C" void __cdecl StaticExit_ArchiveArray() {
    asm_eh_vector_destructor_iterator_004525ff(&data_004923b0, 0x10, 0x14, reinterpret_cast<void*>(&asm_DatArchive_Reset_00434c20));
}
