// 0x0044B540. Write a whole buffer to a file inside the file subsystem's
// critical section, reporting -1 when the file cannot be opened and -2 when
// the platform write comes up short.
//
// Retail keeps the byte count in EDI while the path and the buffer stay on the
// stack, so the body is compiled in the native LTCG cluster of
// build_support/layout/ltcg/file_write_whole_file_0044b540.json, whose synthetic caller
// forces that convention.
//
// The KERNEL32 slots at 0x004660B0..0x00466128 are addressed through their
// stored pointers exactly as the retail import thunks do, and the critical
// section object and its nesting counter are the retail globals at 0x004922A4
// and 0x0049231E.

extern "C" unsigned char imp_EnterCriticalSection;   // EnterCriticalSection
extern "C" unsigned char imp_LeaveCriticalSection;   // LeaveCriticalSection
extern "C" unsigned char imp_CreateFileA;   // CreateFileA
extern "C" unsigned char imp_CloseHandle;   // CloseHandle
extern "C" unsigned char imp_WriteFile;   // WriteFile
extern "C" unsigned char imp_GetLastError;   // GetLastError
extern "C" unsigned char imp_FormatMessageA;   // FormatMessageA
extern "C" unsigned char imp_LocalFree;   // LocalFree
extern "C" unsigned char data_004922a4;   // the file subsystem lock object
extern "C" unsigned char data_0049231e;   // the lock's nesting counter

typedef void (__stdcall* EnterCriticalSectionFn)(void* section);
typedef void (__stdcall* LeaveCriticalSectionFn)(void* section);
typedef void* (__stdcall* CreateFileFn)(const char* path, unsigned long access,
                                        unsigned long share, void* attributes,
                                        unsigned long creation, unsigned long flags,
                                        void* template_file);
typedef int (__stdcall* CloseHandleFn)(void* handle);
typedef int (__stdcall* WriteFileFn)(void* handle, const void* buffer,
                                     unsigned long size, unsigned long* written,
                                     void* overlapped);
typedef unsigned long (__stdcall* GetLastErrorFn)(void);
typedef unsigned long (__stdcall* FormatMessageFn)(unsigned long flags, void* source,
                                                   unsigned long message_id,
                                                   unsigned long language_id,
                                                   char** buffer, unsigned long buffer_size,
                                                   void* arguments);
typedef void* (__stdcall* LocalFreeFn)(void* memory);

__declspec(noinline) int File_WriteWholeFile(const char* path, const void* buffer,
                                             unsigned long size);

#pragma code_seg(".text$01write")
int File_WriteWholeFile(const char* path, const void* buffer, unsigned long size) {
    (*(EnterCriticalSectionFn*)&imp_EnterCriticalSection)(&data_004922a4);
    ++data_0049231e;
    void* handle = (*(CreateFileFn*)&imp_CreateFileA)(path, 0x40000000, 1, 0, 2, 0x80, 0);
    if (handle == (void*)-1) {
        char* message;
        (*(FormatMessageFn*)&imp_FormatMessageA)(
            0x1300, 0, (*(GetLastErrorFn*)&imp_GetLastError)(), 0x400, &message, 0, 0);
        (*(LocalFreeFn*)&imp_LocalFree)(message);
        (*(LeaveCriticalSectionFn*)&imp_LeaveCriticalSection)(&data_004922a4);
        --data_0049231e;
        return -1;
    }
    unsigned long written;
    (*(WriteFileFn*)&imp_WriteFile)(handle, buffer, size, &written, 0);
    if (size != written) {
        (*(CloseHandleFn*)&imp_CloseHandle)(handle);
        (*(LeaveCriticalSectionFn*)&imp_LeaveCriticalSection)(&data_004922a4);
        --data_0049231e;
        return -2;
    }
    (*(CloseHandleFn*)&imp_CloseHandle)(handle);
    (*(LeaveCriticalSectionFn*)&imp_LeaveCriticalSection)(&data_004922a4);
    --data_0049231e;
    return 0;
}
#pragma code_seg()
