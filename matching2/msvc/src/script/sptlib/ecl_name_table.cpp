// Equivalent recovery of the script name table loader at 0x00450220. The
// default build compiles this into the executable once
// tools/matching/equivalence.py has checked that it differs from the exact
// bytes only as recorded in build_support/layout/equivalent/ecl_name_table_00450220.json.
// The inline assembly in build_support/exact/script/sptlib/ecl_name_table.cpp supplies those exact
// bytes and `make EXACT=1`.
//
// Registers one script file: checks its header, grows the table of named
// subroutines and inserts the file's names so the table stays sorted.
#include <stddef.h>
#include <string.h>

extern "C" void* __cdecl entry_malloc(unsigned int size);
extern "C" void __cdecl crt_free(void* block);

struct ScriptSub {
    const char* name;
    int body;
};

struct ScriptHeader {
    int magic;                  // 'SCPT'
    unsigned short version;
    unsigned short chunk_size;  // bytes of chunk data after the 0x24 byte header
    int header_size;
    int reserved;
    unsigned short sub_count;
};

struct ScriptFileLoader {
    virtual void Reserved();
    virtual void LoadChunks(char* chunks);
    int file_count;
    int name_count;
    ScriptHeader* files[32];
    ScriptSub* entries;
    __declspec(noinline) int Parse(int* data);
};
typedef char ScriptFileLoader_entries_offset[offsetof(ScriptFileLoader, entries) == 0x8c ? 1 : -1];
typedef char ScriptHeader_sub_count_offset[offsetof(ScriptHeader, sub_count) == 0x10 ? 1 : -1];

// The parameter arrives as the file and is then reused as the cursor over the
// file's table of subroutine offsets, as its stack home shows.
int ScriptFileLoader::Parse(int* data) {
    files[file_count] = (ScriptHeader*)data;
    ScriptHeader** slot = &files[file_count];
    if (files[file_count]->magic != 0x54504353) {
        *slot = 0;
        return -1;
    }
    if (files[file_count]->version != 1) {
        *slot = 0;
        return -1;
    }
    data = (int*)((char*)files[file_count] + files[file_count]->chunk_size + 0x24);
    const char* names = (const char*)(data + files[file_count]->sub_count);
    // Retail tests the old table twice; one variable makes the compiler drop
    // the second test.
    ScriptSub* old = entries;
    ScriptSub* previous = entries;
    name_count += files[file_count]->sub_count;
    unsigned int size = name_count * sizeof(ScriptSub);
    entries = (ScriptSub*)entry_malloc(size);
    if (old == 0) {
        for (int i = 0; i < name_count; i++, data++) {
            entries[i].body = (int)files[file_count] + *data;
            entries[i].name = names;
            names += strlen(names) + 1;
        }
    } else {
        int kept = name_count - files[file_count]->sub_count;
        memcpy(entries, old, sizeof(ScriptSub) * (name_count - files[file_count]->sub_count));
        if (previous) crt_free(previous);
        for (int merged = 0; merged < files[file_count]->sub_count; merged++, data++) {
            int index;
            for (index = 0; index < kept; index++) {
                if (strcmp(names, entries[index].name) <= 0) break;
            }
            for (int i = name_count - 1; i > index; i--) {
                entries[i] = entries[i - 1];
            }
            entries[index].body = (int)files[file_count] + *data;
            entries[index].name = names;
            names += strlen(names) + 1;
            kept++;
        }
    }
    int registered = file_count++;
    if (files[registered]->chunk_size != 0) {
        LoadChunks((char*)files[registered] + 0x24);
    }
    return registered;
}
