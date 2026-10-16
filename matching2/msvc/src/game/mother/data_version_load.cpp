// 0x00420100: open the data archive and load its version file.
//
// The archive must hold "th10_0100a.ver": the name is built from the program's
// version 1.00a. A missing archive and a missing version file each log their
// own error line.
#include "th10/app/data_version.hpp"
#include "th10/archive/dat_archive_types.hpp"
#include "th10/platform/archive_file.hpp"
#include "resource_surface_loading_log.hpp"

extern "C" int __cdecl sprintf(char* buffer, const char* format, ...);

extern "C" DatArchive g_archive;
extern "C" char str_th10_dat[];           // "th10.dat"
extern "C" char str_ver_file_format[];           // "th10_%.4x%c.ver"
extern "C" char str_data_version_mismatch[];           // "error : the data version differs"
extern "C" char str_data_file_missing[];           // "error : the data file does not exist"

#pragma code_seg(".text$00a3version")
int __cdecl DataVersion_Load2() {
    char path[128];
    int size;
    if (g_archive.Open(str_th10_dat)) {
        sprintf(path, str_ver_file_format, 0x100, 'a');
        g_data_version_buffer = Archive_LoadFile(path, &size, 0);
        g_data_version_size = size;
        if (!g_data_version_buffer) {
            g_log.AppendLine(str_data_version_mismatch);
            return -1;
        }
        return 0;
    }
    g_log.AppendLine(str_data_file_missing);
    return -1;
}
#pragma code_seg()
