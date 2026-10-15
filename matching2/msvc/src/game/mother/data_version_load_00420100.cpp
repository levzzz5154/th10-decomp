// 0x00420100: open the data archive and load its version file.
//
// The archive must hold "th10_0100a.ver": the name is built from the program's
// version 1.00a. A missing archive and a missing version file each log their
// own error line.
#include "th10/app/data_version_00420100.hpp"
#include "th10/archive/dat_archive_types.hpp"
#include "th10/platform/archive_file.hpp"
#include "resource_surface_loading_log.hpp"

extern "C" int __cdecl sprintf(char* buffer, const char* format, ...);

extern "C" DatArchive g_archive;
extern "C" char data_0046e000[];           // "th10.dat"
extern "C" char data_0046dff0[];           // "th10_%.4x%c.ver"
extern "C" char data_0046dfc8[];           // "error : the data version differs"
extern "C" char data_0046dfa0[];           // "error : the data file does not exist"

#pragma code_seg(".text$00a3version")
int __cdecl DataVersion_Load_00420100() {
    char path[128];
    int size;
    if (g_archive.Open(data_0046e000)) {
        sprintf(path, data_0046dff0, 0x100, 'a');
        data_0049238c = Archive_LoadFile(path, &size, 0);
        data_00492388 = size;
        if (!data_0049238c) {
            g_log.AppendLine(data_0046dfc8);
            return -1;
        }
        return 0;
    }
    g_log.AppendLine(data_0046dfa0);
    return -1;
}
#pragma code_seg()
