// 0x00429B60: save the replay the manager recorded. The routine appends the
// player name (space padded to eight bytes) to the summary, stamps the stage
// count, the current score and the slow rate derived from the frame-time
// counters, measures all eight stage pools, packs the summary plus every
// stage record and input pool into one buffer, compresses it, runs both
// cipher passes over the packed stream, writes the 0x24-byte header and the
// packed stream to the shared replay file, and appends the two "USER" text
// chunks holding the run information and the comment notice.
// Built in the replay_save LTCG cluster, whose driver adds the byte cipher
// 0x0044B220 (so its key travels in AL, as retail) and a caller.
#include <stddef.h>
#include <string.h>
#include "th10/game/replay_save.hpp"
#include "th10/archive/crypt.hpp"
#include "th10/archive/lzss.hpp"
#include "th10/game/score_archive.hpp"
#include "th10/game/fps_runtime.hpp"

// The frame-time counters the slow rate is derived from; 0x004134B0 keeps
// them updated while the game runs (measured time over the interval budget).
extern "C" FPS* g_fps;
extern "C" float flt_100;  // 100.0f
// The running game's counters at 0x00474C44 (the current score first). The
// block's address escapes, so a store through any pointer may change it.
struct ReplayGameCounters {
    unsigned int score;
};
extern "C" ReplayGameCounters g_globals_score;

// Replay text pool: format strings and constants shared by the save paths.
extern "C" const char str_replay_dir[];  // "replay"
extern "C" const char str_replay_path_format[];  // "replay/%s"
extern "C" const char str_replay_info_title[];  // the replay file info line
extern "C" const char str_replay_version_format[];  // "Version %s\r\n"
extern "C" const char str_game_version[];  // "1.00a"
extern "C" const char str_replay_name_format[];  // "Name %s\r\n"
extern "C" const char str_replay_date_format[];  // "Date %.2d/%.2d/%.2d %.2d:%.2d\r\n"
extern "C" const char str_replay_chara_format[];  // "Chara %s\r\n"
extern "C" const char str_replay_rank_format[];  // "Rank %s\r\n"
extern "C" const char str_replay_extra_clear[];  // "Extra Stage Clear\r\n"
extern "C" const char str_replay_all_clear[];  // "Stage All Clear\r\n"
extern "C" const char str_replay_extra_stage[];  // "Extra Stage\r\n"
extern "C" const char str_replay_stage_format[];  // "Stage %d\r\n"
extern "C" const char str_replay_stage_range_format[];  // "Stage %d 〜 %d\r\n"
extern "C" const char str_replay_score_format[];  // "Score %d\r\n"
extern "C" const char str_replay_slow_rate_format[];  // "Slow Rate %2.2f\r\n"
extern "C" const char str_replay_comment_placeholder[];  // the comment notice line
extern "C" const char* g_shot_names[];  // "ReimuA" .. "MarisaC"
extern "C" const char* g_difficulty_names[];  // "Easy" .. "Extra"

// The CRT `tm` fields the date line reads.
struct BrokenDownTime_00429b60 {
    int second;                      // +0x00
    int minute;                      // +0x04
    int hour;                        // +0x08
    int day;                         // +0x0C
    int month;                       // +0x10
    int year;                        // +0x14
};

extern "C" int __cdecl asm_FUN_00452abc_00452abc(const char* path);  // CreateDirectoryA wrapper
extern "C" int __cdecl asm_sprintf_00452ae8(char* destination, const char* format, ...);
extern "C" BrokenDownTime_00429b60* __cdecl asm_localtime_00452baa(const int* timer);
int __stdcall asm_File_OpenSharedWrite_0044b620(const char* path);

// The kernel calls of the shared-file writer (imported, so a pair of calls in
// one path shares one loaded import pointer, as retail does).
extern "C" __declspec(dllimport) int __stdcall WriteFile(void* file, const void* data,
    unsigned int size, unsigned int* written, void* overlapped);
extern "C" __declspec(dllimport) int __stdcall CloseHandle(void* handle);

// 0x00421F80, inlined here: the share of the interval budget the frames did
// not use, in percent.
inline float Fps_SlowRate(FPS* fps) {
    return flt_100 - (float)(fps->measured / fps->budget) * flt_100;
}

// Closes the shared file and leaves the file lock.
inline void File_CloseShared() {
    CloseHandle(g_file_write_handle);
    LeaveCriticalSection(&g_file_lock);
    --g_file_lock_depth;
}

// The bytes one input pool contributes to the packed stream.
inline int ReplayPool_Size(ReplayPool* pool) {
    return (pool->input_cursor - pool->input_records) * 6 + (int)(pool->state_cursor - pool->state_records);
}

// The input records one pool holds.
inline int ReplayPool_InputCount(ReplayPool* pool) {
    return pool->input_cursor - pool->input_records;
}

// 0x0044B740's body, inlined at each site: write one block to the shared
// file; on a short write close the file and release its lock.
__forceinline int WriteShared(const void* buffer, unsigned int size) {
    unsigned int written;
    if (g_file_write_handle == (void*)-1) {
        return (int)g_file_write_handle;
    }
    WriteFile(g_file_write_handle, buffer, size, &written, 0);
    if (size != written) {
        File_CloseShared();
        return -2;
    }
    return 0;
}

#pragma code_seg(".text$rsave01")
int __fastcall ReplaySaveManager::Save(const char* file_name, const char* name) {
    ReplaySaveManager* manager = this;
    int first = 0;
    int last = 0;
    int stage;
    int count;
    int total;
    ReplayPoolLink2* link;
    char path[0x100];

    // Copy the player name into the eight-byte summary field, padded with
    // spaces when it is shorter.
    char* name_out = manager->summary->name;
    const char* name_in = name;
    char current;
    do {
        current = *name_in++;
        *name_out++ = current;
    } while (current != '\0');
    int length = strlen(name);
    for (; length < 8; length++) {
        manager->summary->name[length] = ' ';
    }

    asm_FUN_00452abc_00452abc(str_replay_dir);
    asm_sprintf_00452ae8(path, str_replay_path_format, file_name);

    // Measure every stage: the fixed record plus each pool's input and state
    // bytes. The per-stage data size gathers the same figure so the loader
    // can walk the packed stage records; each figure is computed afresh.
    count = 0;
    total = 0x64;
    for (stage = 0; stage < 8; stage++) {
        if (manager->stage_data[stage]) {
            if (first == 0) {
                first = stage;
            }
            manager->stage_data[stage]->data_size = 0;
            total += 0x1C4;
            last = stage;
            for (link = manager->pools[stage].next; link; link = link->next) {
                total += ReplayPool_Size(link->pool);
                manager->stage_data[stage]->data_size += ReplayPool_Size(link->pool);
                manager->stage_data[stage]->input_count += ReplayPool_InputCount(link->pool);
            }
            count++;
        }
    }

    manager->summary->stage_count = count;
    manager->summary->score = g_globals_score.score;
    manager->summary->slow_rate = Fps_SlowRate(g_fps);

    // Pack the summary, the stage records and the pools into one buffer.
    unsigned char* buffer = (unsigned char*)asm_malloc_00452706(total);
    memcpy(buffer, manager->summary, 0x64);
    total = 0x64;
    for (stage = 0; stage < 8; stage++) {
        if (manager->stage_data[stage]) {
            memcpy(buffer + total, manager->stage_data[stage], 0x1C4);
            total += 0x1C4;
            for (link = manager->pools[stage].next; link; link = link->next) {
                ReplayPool* pool = link->pool;
                memcpy(buffer + total, pool, (pool->input_cursor - pool->input_records) * 6);
                total += (pool->input_cursor - pool->input_records) * 6;
            }
            for (link = manager->pools[stage].next; link; link = link->next) {
                ReplayPool* pool = link->pool;
                memcpy(buffer + total, pool->state_records, pool->state_cursor - pool->state_records);
                total += pool->state_cursor - pool->state_records;
            }
        }
    }

    // Compress, then run both cipher passes; the keys and block sizes are the
    // ones the replay loader expects. The compressor's out-parameter lives
    // only for the call.
    unsigned char* packed;
    int sent;
    {
        int written;
        packed = Lzss_Compress(buffer, total, &written);
        asm_free_00452422(buffer);
        sent = written;
    }
    Dat_Encrypt(packed, sent, 0x3D, 0x7A, 0x80, sent);
    Dat_Encrypt(packed, sent, 0xAA, 0xE1, 0x400, sent);

    manager->header->size = total;
    manager->header->packed_size = sent;
    manager->header->packed_end = manager->header->packed_size + 0x24;

    asm_File_OpenSharedWrite_0044b620(path);
    WriteShared(manager->header, 0x24);
    WriteShared(packed, sent);
    if (packed) {
        asm_free_00452422(packed);
    }

    // Append the "USER" header-information chunk, padded to whole words.
    ReplayUserChunk* chunk = (ReplayUserChunk*)asm_malloc_00452706(0xFFFF);
    memset(chunk, 0, 0xFFFF);
    chunk->magic = 0x52455355;
    chunk->flag = 0;
    char* out = chunk->text;
    out += asm_sprintf_00452ae8(out, str_replay_info_title);
    out += asm_sprintf_00452ae8(out, str_replay_version_format, str_game_version);
    out += asm_sprintf_00452ae8(out, str_replay_name_format, manager->summary);
    BrokenDownTime_00429b60* time = asm_localtime_00452baa(&manager->summary->date);
    out += asm_sprintf_00452ae8(out, str_replay_date_format, time->year % 100, time->month + 1,
                       time->day, time->hour, time->minute);
    out += asm_sprintf_00452ae8(out, str_replay_chara_format,
                       g_shot_names[manager->summary->character * 3 + manager->summary->shot_type]);
    out += asm_sprintf_00452ae8(out, str_replay_rank_format, g_difficulty_names[manager->summary->difficulty]);
    if (manager->summary->stage_reached > 7) {
        if (first == 7) {
            out += asm_sprintf_00452ae8(out, str_replay_extra_clear);
        } else {
            out += asm_sprintf_00452ae8(out, str_replay_all_clear);
        }
    } else if (first == last) {
        if (first == 7) {
            out += asm_sprintf_00452ae8(out, str_replay_extra_stage);
        } else {
            out += asm_sprintf_00452ae8(out, str_replay_stage_format, first);
        }
    } else {
        out += asm_sprintf_00452ae8(out, str_replay_stage_range_format, first, last);
    }
    out += asm_sprintf_00452ae8(out, str_replay_score_format, manager->summary->score);
    out += asm_sprintf_00452ae8(out, str_replay_slow_rate_format, (double)manager->summary->slow_rate) + 1;
    if ((int)(out - (char*)chunk) % 4 != 0) {
        out += 4 - (int)(out - (char*)chunk) % 4;
    }
    chunk->size = (unsigned int)(out - (char*)chunk);
    WriteShared(chunk, (unsigned int)(out - (char*)chunk));

    // Reuse the buffer for the comment notice chunk.
    memset(chunk, 0, 0xFFFF);
    chunk->magic = 0x52455355;
    chunk->flag = 1;
    out = chunk->text;
    out += asm_sprintf_00452ae8(out, str_replay_comment_placeholder) + 1;
    if ((int)(out - (char*)chunk) % 4 != 0) {
        out += 4 - (int)(out - (char*)chunk) % 4;
    }
    chunk->size = (unsigned int)(out - (char*)chunk);
    WriteShared(chunk, (unsigned int)(out - (char*)chunk));
    asm_free_00452422(chunk);
    if (g_file_write_handle != (void*)-1) {
        File_CloseShared();
    }
    return 0;
}
#pragma code_seg()
