#pragma once
#include <stddef.h>
#include <string.h>
#include "th10/platform/archive_file.hpp"
#include "th10/game/menu_cursor.hpp"

extern "C" int __cdecl sprintf(char* buffer, const char* format, ...);
extern "C" void __cdecl free(void* block);
void* __cdecl operator new(unsigned int size);

struct ScriptEntry2 {
    const char* name;
    void* code;
};

// The parser's last two words are a member with its own constructor, which
// runs between the vtable store and the constructor body.
struct ScriptParserTail {
    int first;
    int second;
    ScriptParserTail() : first(0), second(0) {}
};

// The 0x1098-byte script parser whose vtable is at 0x0046D0F0. Its
// constructor clears the whole object after the vtable has been published.
struct ScriptParser {
    virtual int Load(char* data);      // 0x00450220
    virtual void Slot04();             // 0x0040C810

    int reserved_004;
    int entry_count;
    unsigned char reserved_00c[0x8C - 0x0C];
    ScriptEntry2* entries;
    unsigned char reserved_090[0x1090 - 0x90];
    ScriptParserTail tail;

    ScriptParser() {
        memset(this, 0, sizeof(ScriptParser));
    }
    // 0x00450500: create an interpreter positioned at the named entry.
    __declspec(noinline) struct SptTestResource* CreateVm(const char* name);
    ~ScriptParser() {
        if (entries) {
            free(entries);
            entries = 0;
        }
    }
};
typedef char ScriptParserSize[sizeof(ScriptParser) == 0x1098 ? 1 : -1];

// The interpreter state the running script is in; `running` stays nonzero
// until the script ends.
struct SptTestVmState {
    int time;
    int running;
};

// The script interpreter the screen runs an entry with. Only its retire entry
// in slot 5 is called.
struct SptTestResource {
    virtual void Slot00() = 0;
    virtual void Slot04() = 0;
    virtual void Slot08() = 0;
    virtual void Slot0C() = 0;
    virtual void Slot10() = 0;
    virtual void Retire(int release) = 0;

    SptTestVmState* active;
};

// Clamp a wanted selection to a cursor's last item.
inline void SptTest_ClampSelection(const MenuCursor& cursor, int& index) {
    if (cursor.item_count != 0 && index >= cursor.item_count)
        index = cursor.item_count - 1;
}

struct SchedulerTask;

// The screen's loader thread: a PlatformWorker (th10/platform/worker.hpp).
// Its destructor (0x0044C130) republishes the worker dispatch table and stops
// the thread.
struct SptTestWorker {
    const void* vtable;
    void* thread;
    unsigned int thread_id;
    unsigned int stop_requested;
    unsigned int running;
    unsigned int reserved_14;
    void* entry;

    ~SptTestWorker();
};

// The "Spt Test" debug screen: picks a script file, loads it and shows one of
// its entries.
struct SptTest2 {
    unsigned char reserved_000[8];
    SchedulerTask* update_task;
    SchedulerTask* draw_task;
    SptTestWorker worker;
    unsigned char reserved_02c[4];
    int state;                 // 1 = menu, 2 = loading, 3 = running
    const char** script_names;
    int script_count;
    MenuCursor menu;           // File / Ecl / Quit
    MenuCursor file_cursor;    // which script file
    MenuCursor entry_cursor;   // which entry of the loaded script
    float position_x;
    float position_y;
    float position_z;
    int field_2d0;
    unsigned int flags;
    ScriptParser* parser;
    SptTestResource* resource;
    char* script_data;

    __declspec(noinline) ~SptTest2();
    __declspec(noinline) void ClearScriptNames();
    __declspec(noinline) int Update();
    __declspec(noinline) int LoadScript();
    __declspec(noinline) int Draw();
};
typedef char SptTestStateOffset[offsetof(SptTest2, state) == 0x30 ? 1 : -1];
typedef char SptTestCursorOffset[offsetof(SptTest2, entry_cursor) == 0x1EC ? 1 : -1];
typedef char SptTestParserOffset[offsetof(SptTest2, parser) == 0x2D8 ? 1 : -1];

extern "C" SptTest2* g_spt_test;
