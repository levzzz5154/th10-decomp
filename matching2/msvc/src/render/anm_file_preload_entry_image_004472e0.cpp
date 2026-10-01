// 0x004472E0 (214 bytes): validate one ANM entry and, when its image lives in
// a separate archive file (no embedded THTX block and a name that does not
// start with '@'), load that file and keep it on the entry's texture record.
// Returns 1, or -1 after logging.
//
// Native LTCG passes the entry index in ECX and the file in EDX; the entry
// stays on the stack. The declared order (file, entry, index) is what makes
// the caller evaluate index, entry, file in that order.
#include "th10/render/anm_file_004470c0.hpp"
#include "th10/platform/archive_file.hpp"

#pragma code_seg(".text$05preload")
int __stdcall AnmFile_PreloadEntryImage_004472e0(AnmFile_004470c0* file,
                                                 const AnmEntryHeader_00446c70* entry, int index) {
    char path[260];
    int size;
    if (!entry) {
        data_00474f70.AppendLine(data_00470274);
        return -1;
    }
    if (entry->version != 4) {
        data_00474f70.AppendLine(data_00470254);
        return -1;
    }
    if (!entry->has_data) {
        const char* name = entry->Name();
        if (name[0] != '@') {
            sprintf(path, data_0046e1c8, name);
            char* data = Archive_LoadFile(path, &size, 1);
            if (!data) {
                data_00474f70.AppendLine(data_00470210, name);
                return -1;
            }
            file->textures[index].data_size = size;
            file->textures[index].file_data = data;
        }
    }
    return 1;
}
#pragma code_seg()
