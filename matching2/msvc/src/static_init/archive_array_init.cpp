// 0x00465910: construct the global array of twenty 16-byte objects and
// register its destructor with the runtime.
//
// The constructor iterator is the runtime's own __stdcall helper: it takes the
// array, the element size, the count and the constructor and destructor
// addresses, and cleans the five arguments itself.

extern "C" void __stdcall asm_eh_vector_constructor_iterator_0045252d(
        void* array, unsigned int size, int count,
        void (__cdecl*)(void), void (__cdecl*)(void));
extern "C" void __cdecl asm_DatArchive_Reset_00434c20(void);
extern "C" void __cdecl StaticExit_ArchiveArray(void);
extern "C" int __cdecl asm_atexit_00452e0a(void (__cdecl*)(void));
extern "C" char g_archive_entries[];
int* __fastcall ArchiveRecord_Construct(int* element);

extern "C" void __cdecl StaticInit_ArchiveArray(void) {
    asm_eh_vector_constructor_iterator_0045252d(
        g_archive_entries, 16, 20,
        (void (__cdecl*)(void))ArchiveRecord_Construct,
        asm_DatArchive_Reset_00434c20);
    asm_atexit_00452e0a(StaticExit_ArchiveArray);
}
