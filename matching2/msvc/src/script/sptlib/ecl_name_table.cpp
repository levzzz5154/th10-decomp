// Script name table loader at 0x00450220.
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

// Vtable at 0x0046D0F0: Parse, then LoadChunks.
struct ScriptFileLoader {
    virtual int Parse(int* data);
    virtual void LoadChunks(char* chunks);
    int file_count;
    int name_count;
    ScriptHeader* files[32];
    ScriptSub* entries;
};
typedef char ScriptFileLoader_entries_offset[offsetof(ScriptFileLoader, entries) == 0x8c ? 1 : -1];
typedef char ScriptHeader_sub_count_offset[offsetof(ScriptHeader, sub_count) == 0x10 ? 1 : -1];

// The count is grown through a reference, so the allocation size reads the
// stored count back (retail's `shl` on a fresh copy) instead of reusing the sum.
static __forceinline void AddCount(int& count, int n) { count += n; }

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
    // Both locals hold the table being replaced. Retail tests it again before
    // freeing it; the compiler keeps that second test only when it reads a
    // second variable.
    ScriptSub* old = entries;
    ScriptSub* previous = entries;
    AddCount(name_count, files[file_count]->sub_count);
    unsigned int size = name_count * sizeof(ScriptSub);
    entries = (ScriptSub*)entry_malloc(size);
    if (old == 0) {
        for (int i = 0; i < name_count; i++, data++) {
            entries[i].body = (int)files[file_count] + *data;
            entries[i].name = names;
            names += strlen(names) + 1;
        }
    } else {
        int sub = files[file_count]->sub_count;
        int kept = name_count - sub;
        memcpy(entries, old, sizeof(ScriptSub) * kept);
        // Frees the old table (old == previous). Naming both pointers in the
        // call is what leaves `old`, not `names`, in EBP as in retail.
        if (previous) crt_free((old == previous) ? old : previous);
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
