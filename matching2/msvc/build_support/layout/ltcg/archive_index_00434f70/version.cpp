#include "archive.hpp"
#include "log.hpp"
extern "C" int __cdecl archive_sprintf(char*,const char*,...);
extern "C" DatArchive g_archive;
extern "C" TextLog_0044b8e0 g_log;
extern "C" char* g_data_version_buffer;
extern "C" int g_data_version_size;
extern "C" char version_archive_name[],version_filename_format[];
extern "C" char version_missing_message[],archive_missing_message[];
extern "C" char* __stdcall Archive_LoadFile(const char*,int*,int);
#pragma code_seg(".text$a00version")
__declspec(noinline) int CheckVersion() {
    int size;
    char name[128];
    if (g_archive.Open(version_archive_name)) {
        archive_sprintf(name,version_filename_format,0x100,0x61);
        char* buffer=Archive_LoadFile(name,&size,0);
        g_data_version_buffer=buffer;
        g_data_version_size=size;
        if(buffer) return 0;
        g_log.AppendLine(version_missing_message);
    } else {
        g_log.AppendLine(archive_missing_message);
    }
    return -1;
}
#pragma code_seg()
