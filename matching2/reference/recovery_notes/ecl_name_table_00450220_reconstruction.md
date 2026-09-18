# 0x00450220 — ECL name table: full reconstruction and its measured gap

2026-09-18. The `ScriptFileLoader::Parse` model that the earlier session lost
(only its measurements survived in `ecl_name_table_00450220_allocator_residual.md`)
was rebuilt from `ida/th10.exe.c`'s pseudocode plus the maintained assembly
listing, and measured through `probe.py`'s compile path in a throwaway copy of
the project (`/tmp/w450220/msvc`, so the maintained tree is untouched).

## Structure (confirmed against the pseudocode)

`int __thiscall Parse(char* data)` — `this` in ECX, `data` on the stack, `ret 4`.
Layout: `dispatch` +0x00, `file_count` +0x04, `name_count` +0x08, `files[32]`
+0x0C, merged `entries` +0x8C (8-byte `{name, body}` records). The tail hands the
chunk table (`file + 0x24`) to slot 1 of the dispatch table through a member
pointer, and the function returns the previous `file_count`.

## Measured variants in the copy

| variant | extent | frame | differing |
| --- | ---: | --- | ---: |
| full model, `count` reloaded in the loop | 615 | `0x0C` | 500 |
| `unsigned short count` local used through the loop | 597 | `0x14` | 503 |
| the same with `kept`/`limit` merged into one local | 599 | `0x14` | 506 |

Retail is 589 bytes with frame `0x10`. The prologue matches retail instruction
for instruction apart from the immediate: retail `sub esp,10h` / `[esp+18h]`,
the closest variants `sub esp,0Ch` / `[esp+14h]` (one slot short) and
`sub esp,14h` / `[esp+1Ch]` (one slot long). So the missing piece is exactly one
4-byte stack slot — the same wall the earlier note measured across 90 variants:
only an unfaithful extra live value reproduces it. Two faithful candidates remain
untried because they cost the slot in pairs: a `char`/`bool` loop-carried flag
read in the merge body, and a `short` header counter consulted inside the loop.

## The reconstruction (verbatim, as measured)

```cpp
// 0x00450220..0x0045046C: register one SCPT script file into the loader's sorted
// name table. The file record is appended first, the header is validated as two
// separate checks, the merged table is sized, the surviving prefix of the old
// table is copied and the old table freed, every sub name is merged into sorted
// position, and the chunk table is handed to the object-chunk loader through the
// loader's dispatch table.
#include <string.h>

extern "C" void* __cdecl entry_malloc_00452706(unsigned int size);
extern "C" void __cdecl entry_free_00452422(void* block);

struct ScriptSub_00450220 {
    const char* name;   // +0x00
    int body;           // +0x04
};

struct ScriptFileLoader_00450220 {
    const int* dispatch;            // +0x00
    int file_count;                 // +0x04
    int name_count;                 // +0x08
    char* files[32];                // +0x0C
    ScriptSub_00450220* entries;    // +0x8C

    __declspec(noinline) int Parse(char* data);
};

typedef void (ScriptFileLoader_00450220::*ScriptChunkLoader_00450220)(char*);

#pragma code_seg(".text$02names")
int ScriptFileLoader_00450220::Parse(char* data) {
    files[file_count] = data;
    char** slot = &files[file_count];
    if (*(int*)files[file_count] != 0x54504353) {
        *slot = 0;
        return -1;
    }
    if (*(unsigned short*)(files[file_count] + 4) != 1) {
        *slot = 0;
        return -1;
    }
    int* offsets = (int*)(*(unsigned short*)(files[file_count] + 6) + files[file_count] + 0x24);
    unsigned short count = *(unsigned short*)(files[file_count] + 0x10);
    int total = name_count + count;
    const char* names = (const char*)(offsets + count);
    name_count = total;
    ScriptSub_00450220* old = entries;
    entries = (ScriptSub_00450220*)entry_malloc_00452706(8 * total);
    if (old != 0) {
        int kept = name_count - count;
        memcpy(entries, old, 8 * kept);
        entry_free_00452422(old);
        int merged = 0;
        if (count != 0) {
            while (1) {
                int index = 0;
                const char* name;
                if (kept <= 0) {
                    name = names;
                } else {
                    ScriptSub_00450220* walk = entries;
                    do {
                        name = names;
                        if (strcmp(names, walk->name) <= 0) {
                            break;
                        }
                        index++;
                        walk++;
                    } while (index < kept);
                }
                for (int i = name_count - 1; i > index; i--) {
                    entries[i] = entries[i - 1];
                }
                entries[index].body = *offsets + (int)files[file_count];
                entries[index].name = name;
                offsets++;
                names = name + strlen(name) + 1;
                kept++;
                if (++merged >= count) {
                    break;
                }
            }
        }
    } else {
        int index = 0;
        if (name_count > 0) {
            while (1) {
                entries[index].body = *offsets + (int)files[file_count];
                entries[index].name = names;
                const char* next = names + strlen(names) + 1;
                index++;
                offsets++;
                if (index >= name_count) {
                    break;
                }
                names = next;
            }
        }
    }
    int registered = file_count;
    file_count = registered + 1;
    if (*(unsigned short*)(files[registered] + 6) != 0) {
        ScriptChunkLoader_00450220 load =
            *(ScriptChunkLoader_00450220*)&dispatch[1];
        (this->*load)(files[registered] + 0x24);
    }
    return registered;
}
#pragma code_seg()
```
