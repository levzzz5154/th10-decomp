// 0x004357D0: open the next slot of the global archive table and count it
// when the open succeeds.  Unreferenced in retail.
//
// The path is forwarded to DatArchive::Open in EAX, so the body is compiled
// in the cluster build_support/layout/ltcg/dat_archive_open.json.
#include "th10/archive/dat_archive_types.hpp"

extern DatArchive g_dat_archives[];   // 0x004923B0
extern int g_dat_archive_count;       // 0x00477850

#pragma code_seg(".text$08opennext")
__declspec(noinline) bool DatArchive_OpenNext(const char* path) {
    if (g_dat_archives[g_dat_archive_count].Open(path)) {
        ++g_dat_archive_count;
        return true;
    }
    return false;
}
#pragma code_seg()
