#pragma once

#include "th10/platform/windows_types.hpp"

// Retail vtable at 0x0046F230. Keeping this typed preserves the polymorphic
// calls used by archive readers while documenting every slot.
class FileInterface {
public:
    FileInterface() {}

    virtual BYTE Open(const char* path, const char* mode) = 0;
    virtual void Close() = 0;
    virtual DWORD Read(void* destination, DWORD size) = 0;
    virtual BYTE Write(const void* source, DWORD size) = 0;
    virtual DWORD Tell() const = 0;
    virtual DWORD GetSize() const = 0;
    virtual BYTE Seek(LONG distance, DWORD origin) = 0;
    virtual ~FileInterface() {}
};

// Win32-backed file owner used by the archive/file subsystem.
class FileHandle : public FileInterface {
public:
    FileHandle();
    ~FileHandle();

    HANDLE handle;
    DWORD access;

    virtual BYTE Open(const char* path, const char* mode);
    virtual void Close();
    virtual DWORD Read(void* destination, DWORD size);
    virtual BYTE Write(const void* source, DWORD size);
    virtual DWORD Tell() const;
    virtual DWORD GetSize() const;
    virtual BYTE Seek(LONG distance, DWORD origin);
    void* ReadWhole(DWORD capacity);
};

void File_ResolvePath(const char* path, char output[260]);
const char* File_AfterFirstSlash(const char* path);
bool File_ProbeExists(const char* path,
                      void* (*open_file)(const char*),
                      void (*close_file)(void*));
int File_CloseProbeHandle(void* handle, void (*close_file)(void*),
                          unsigned char* critical_depth);
int File_OpenSharedWrite(const char* path, void* (*open_file)(const char*),
                         void (*report_error)(void),
                         void** shared_handle, unsigned char* critical_depth);
int File_OpenSharedRead(const char* path, void* (*open_file)(const char*),
                        void (*report_error)(void),
                        void** shared_handle, unsigned char* critical_depth);
// enter_section/leave_section are the retail file-system critical section
// (0x004922A4); retail holds it across the whole open/write/close and drops
// it before unwinding the depth byte on every exit.
int File_WriteWholeFile(const char* path, const void* source, DWORD size,
                        void* (*open_file)(const char*),
                        DWORD (*write_file)(void*, const void*, DWORD),
                        void (*close_file)(void*),
                        void (*report_error)(void),
                        unsigned char* critical_depth,
                        void (*enter_section)(void),
                        void (*leave_section)(void));
int File_WriteShared(void* handle, const void* source, DWORD size,
                     DWORD (*write_file)(void*, const void*, DWORD),
                     void (*close_file)(void*), unsigned char* critical_depth);
void* File_ReadShared(void* handle, DWORD size,
                      void* (*allocate)(DWORD),
                      DWORD (*read_file)(void*, void*, DWORD),
                      void (*close_file)(void*));
