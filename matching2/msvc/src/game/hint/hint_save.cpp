// 0x0041A200 (_SaveHints@8): regenerate hint/hint_auto.txt, the auto-generated
// stage-tip file. The eight stage lists of the resource manager are written
// out one after another as "Stage : N ... StageEnd" blocks, and every tip that
// the run actually showed (selection != 0) contributes one "Tips" record with
// its text, position, counters and display attributes. The header carries a
// time stamp; the whole text goes through the shared-file writer opened on
// the caller's path. Always returns 0, even when the open failed.
//
// The writes before the tip loop call the real WriteShared helper; inside the
// loop the WriteFile/CloseHandle/LeaveCriticalSection body of that helper is
// spelled out at every site, each with its own written-count slot, exactly as
// retail lays them out.
#include "th10/archive/hint_save_0041a200.hpp"
#include <string.h>

#pragma intrinsic(strlen)

// The inline retail write: WriteFile through the kernel slot, and on a short
// write close the shared file, leave the file critical section and unwind the
// lock depth. The handle is read once for the guarded call and re-read after
// WriteFile, as retail does across the call boundary.
__forceinline int WriteHintLine(const char* buffer, unsigned int length) {
    unsigned int written;
    if (data_00474c38 == (void*)-1)
        return (int)data_00474c38;
    imp_WriteFile(data_00474c38, buffer, length, &written, 0);
    if (length != written) {
        imp_CloseHandle(data_00474c38);
        imp_LeaveCriticalSection((void*)0x004922A4);
        --data_0049231e;
    }
    return 0;
}

// "\tBase\t" names: the tip display mode, one row per stage script position.
__forceinline const char* HintBaseName(int id) {
    for (int index = 0; index < 0x3d; ++index)
        if (data_004744b0[index].id == id)
            return data_004744b0[index].name;
    return 0;
}

// "\tAlign\t" names: center, left, right.
__forceinline const char* HintAlignName(int id) {
    for (int index = 0; index < 3; ++index)
        if (data_00474494[index].id == id)
            return data_00474494[index].name;
    return 0;
}

#pragma code_seg(".text$00zhint")
extern "C" __declspec(noinline) int __stdcall SaveHints(Manager_00419040* manager,
                                                        const char* path) {
    int stage;
    int rows;
    Bucket_00419040* slot;
    ChainNode_00419040* next = 0;
    char* buffer = (char*)asm_malloc_00452706(0x1000);
    asm_FUN_00452abc_00452abc(data_0046d574);            // make sure "hint" exists
    if (asm_File_OpenSharedWrite_0044b620(path) == 0) {
        asm_sprintf_00452ae8(buffer, data_0046d534);
        WriteShared_0044b740(buffer, strlen(buffer));
        asm_sprintf_00452ae8(buffer, data_0046d510);
        WriteShared_0044b740(buffer, strlen(buffer));
        asm_sprintf_00452ae8(buffer, data_0046d50c);
        WriteShared_0044b740(buffer, strlen(buffer));
        asm_sprintf_00452ae8(buffer, data_0046d4d8);
        WriteShared_0044b740(buffer, strlen(buffer));
        asm_sprintf_00452ae8(buffer, data_0046d490);
        WriteShared_0044b740(buffer, strlen(buffer));
        asm_sprintf_00452ae8(buffer, data_0046d50c);
        WriteShared_0044b740(buffer, strlen(buffer));
        {
            time_t aclock;
            time_00452b71(reinterpret_cast<int*>(&aclock));
            tm* stamp = localtime(&aclock);
            asm_sprintf_00452ae8(buffer, data_0046d440,
                                 stamp->tm_year + 1900, stamp->tm_mon + 1,
                                 stamp->tm_mday, stamp->tm_hour, stamp->tm_min);
        }
        WriteShared_0044b740(buffer, strlen(buffer));
        asm_sprintf_00452ae8(buffer, data_0046d434);
        WriteShared_0044b740(buffer, strlen(buffer));
        asm_sprintf_00452ae8(buffer, data_0046d420, data_0046d654);
        WriteShared_0044b740(buffer, strlen(buffer));

        stage = 0;
        slot = manager->secondary;
        do {
            ChainNode_00419040* entry = slot->head;
            rows = 0;
            if (entry != 0) {
                do {
                    next = entry->next;
                    HintData* tip = static_cast<HintData*>(entry->block);
                    if (tip->selection != 0) {
                        if (rows == 0)
                            asm_sprintf_00452ae8(buffer, data_0046d3f8);
                        WriteHintLine(buffer, strlen(buffer));
                        asm_sprintf_00452ae8(buffer, data_0046d3e8, stage);
                        WriteHintLine(buffer, strlen(buffer));
                        asm_sprintf_00452ae8(buffer, data_0046d3e0, stage);
                        WriteHintLine(buffer, strlen(buffer));
                        if (tip->selection > 0)
                            asm_sprintf_00452ae8(buffer, data_0046d3d0, tip->selection);
                        WriteHintLine(buffer, strlen(buffer));
                        asm_sprintf_00452ae8(buffer, data_0046d3c0, tip->name);
                        WriteHintLine(buffer, strlen(buffer));
                        asm_sprintf_00452ae8(buffer, data_0046d3ac,
                                             (int)tip->x, (int)tip->y);
                        WriteHintLine(buffer, strlen(buffer));
                        asm_sprintf_00452ae8(buffer, data_0046d39c, tip->display_value);
                        WriteHintLine(buffer, strlen(buffer));
                        asm_sprintf_00452ae8(buffer, data_0046d38c,
                                             HintBaseName(tip->display_mode));
                        WriteHintLine(buffer, strlen(buffer));
                        asm_sprintf_00452ae8(buffer, data_0046d37c,
                                             HintAlignName(tip->display_zero));
                        WriteHintLine(buffer, strlen(buffer));
                        asm_sprintf_00452ae8(buffer, data_0046d36c, tip->duration);
                        WriteHintLine(buffer, strlen(buffer));
                        asm_sprintf_00452ae8(buffer, data_0046d35c,
                                             reinterpret_cast<const unsigned char*>(&tip->state)[3]);
                        WriteHintLine(buffer, strlen(buffer));
                        asm_sprintf_00452ae8(buffer, data_0046d344,
                                             reinterpret_cast<const unsigned char*>(&tip->state)[2],
                                             reinterpret_cast<const unsigned char*>(&tip->state)[1],
                                             reinterpret_cast<const unsigned char*>(&tip->state)[0]);
                        WriteHintLine(buffer, strlen(buffer));
                        asm_sprintf_00452ae8(buffer, data_0046d334, (double)tip->scale);
                        WriteHintLine(buffer, strlen(buffer));
                        asm_sprintf_00452ae8(buffer, data_0046d32c, stage);
                        WriteHintLine(buffer, strlen(buffer));
                        if (++rows >= 0xff)
                            break;
                    }
                    entry = next;
                } while (entry != 0);
                if (rows != 0) {
                    asm_sprintf_00452ae8(buffer, data_0046d320);
                    WriteHintLine(buffer, strlen(buffer));
                }
            }
            ++stage;
            ++slot;
        } while (stage < 8);
    }
    if (data_00474c38 != (void*)-1) {
        imp_CloseHandle(data_00474c38);
        imp_LeaveCriticalSection((void*)0x004922A4);
        --data_0049231e;
    }
    asm_free_00452422(buffer);
    return 0;
}
#pragma code_seg()
