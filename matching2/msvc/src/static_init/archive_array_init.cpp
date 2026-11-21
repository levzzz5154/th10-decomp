// 0x00465910: construct the global array of twenty 16-byte objects and
// register its destructor with the runtime.
//
// The constructor iterator is the runtime's own __stdcall helper: it takes the
// array, the element size, the count and the constructor and destructor
// addresses, and cleans the five arguments itself.

extern "C" void __stdcall crt_eh_vector_ctor(
        void* array, unsigned int size, int count,
        void (__cdecl*)(void), void (__cdecl*)(void));
extern "C" void __cdecl DatArchive_Reset(void);
extern "C" void __cdecl StaticExit_ArchiveArray(void);
extern "C" int __cdecl crt_atexit(void (__cdecl*)(void));
extern "C" char g_archive_entries[];
int* __fastcall ArchiveRecord_Construct(int* element);

extern "C" void __cdecl StaticInit_ArchiveArray(void) {
    crt_eh_vector_ctor(
        g_archive_entries, 16, 20,
        (void (__cdecl*)(void))ArchiveRecord_Construct,
        DatArchive_Reset);
    crt_atexit(StaticExit_ArchiveArray);
}
