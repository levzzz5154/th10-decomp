// 0x00465A00: atexit destructor of the twenty 16-byte archive records at
// 0x004923B0 (constructed by StaticInit_ArchiveArray).
extern "C" void __stdcall crt_eh_vector_dtor(void* base, unsigned int size, unsigned int count, void* destructor);
extern "C" unsigned char g_archive_entries;
extern "C" void __cdecl DatArchive_Reset();

extern "C" void __cdecl StaticExit_ArchiveArray() {
    crt_eh_vector_dtor(&g_archive_entries, 0x10, 0x14, reinterpret_cast<void*>(&DatArchive_Reset));
}
