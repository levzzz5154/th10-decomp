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

extern "C" unsigned char data_004660b0;   // EnterCriticalSection
extern "C" unsigned char data_004660b4;   // LeaveCriticalSection
extern "C" unsigned char data_004660c4;   // CreateFileA
extern "C" unsigned char data_004660cc;   // CloseHandle
extern "C" unsigned char data_004660d4;   // WriteFile
extern "C" unsigned char data_0046610c;   // GetLastError
extern "C" unsigned char data_00466124;   // FormatMessageA
extern "C" unsigned char data_00466128;   // LocalFree
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
    (*(EnterCriticalSectionFn*)&data_004660b0)(&data_004922a4);
    ++data_0049231e;
    void* handle = (*(CreateFileFn*)&data_004660c4)(path, 0x40000000, 1, 0, 2, 0x80, 0);
    if (handle == (void*)-1) {
        char* message;
        (*(FormatMessageFn*)&data_00466124)(
            0x1300, 0, (*(GetLastErrorFn*)&data_0046610c)(), 0x400, &message, 0, 0);
        (*(LocalFreeFn*)&data_00466128)(message);
        (*(LeaveCriticalSectionFn*)&data_004660b4)(&data_004922a4);
        --data_0049231e;
        return -1;
    }
    unsigned long written;
    (*(WriteFileFn*)&data_004660d4)(handle, buffer, size, &written, 0);
    if (size != written) {
        (*(CloseHandleFn*)&data_004660cc)(handle);
        (*(LeaveCriticalSectionFn*)&data_004660b4)(&data_004922a4);
        --data_0049231e;
        return -2;
    }
    (*(CloseHandleFn*)&data_004660cc)(handle);
    (*(LeaveCriticalSectionFn*)&data_004660b4)(&data_004922a4);
    --data_0049231e;
    return 0;
}
#pragma code_seg()
