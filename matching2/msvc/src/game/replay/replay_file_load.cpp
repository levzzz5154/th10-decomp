// 0x0042A200..0x0042A3C2: read a replay file into the replay manager.
//
// A replay is a 0x24-byte header followed by the packed body. Normally it is
// read from "replay/<name>" through the shared file handle; with game flag
// 0x20 it comes whole out of the data archive instead. The body is decrypted
// in two passes, unpacked, and its stage records are indexed: each record is
// followed by its 6-byte input records and then by the next stage.
//
// The manager arrives in ESI (the compiler's own convention).
#include "th10/game/replay_file_load.hpp"
#include <stdio.h>
#include <stdlib.h>

#pragma code_seg(".text$00a3load")
int ReplayManager2::LoadFile(const char* name) {
    char path[256];
    int archive_size;
    unsigned char* packed;

    strcpy(filename, name);
    if (!(g_globals_flags & 0x20)) {
        sprintf(path, "replay/%s", name);
        if (!asm_File_ProbeExists_0044b4d0(path))
            return -1;
        if (asm_File_OpenSharedRead_0044b6b0(path) != 0)
            return -1;
        header = (ReplayHeader2*)ReadShared2(sizeof(ReplayHeader2));
        if (header->magic != 0x72303174) {
            File_CloseProbeHandle();
            return -1;
        }
        if (header->version != 5) {
            File_CloseProbeHandle();
            return -1;
        }
        packed = (unsigned char*)ReadShared2(header->packed_size);
        File_CloseProbeHandle();
    } else {
        header = (ReplayHeader2*)Archive_LoadFile(name, &archive_size, 0);
        packed = (unsigned char*)(header + 1);
    }

    int size = header->size;
    data = (unsigned char*)malloc(size);
    DatDecrypt(packed, header->packed_size, 0xAA, 0xE1, 0x400, header->packed_size);
    DatDecrypt(packed, header->packed_size, 0x3D, 0x7A, 0x80, header->packed_size);
    DecompressDatLzss2(packed, header->packed_size, data, header->size);

    summary = (ReplaySummary2*)data;
    ReplayStage* stage = (ReplayStage*)(data + sizeof(ReplaySummary2));
    for (int index = 0; index < (summary->stage_count >= 8 ? 6 : summary->stage_count); ++index) {
        nodes[stage->stage].stage = stage;
        nodes[stage->stage].inputs = (unsigned char*)(stage + 1);
        nodes[stage->stage].inputs_end = nodes[stage->stage].inputs + stage->input_count * 6;
        stage = (ReplayStage*)((unsigned char*)(stage + 1) + stage->data_size);
    }

    if (!(g_globals_flags & 0x20) && packed)
        free(packed);
    return 0;
}
#pragma code_seg()
