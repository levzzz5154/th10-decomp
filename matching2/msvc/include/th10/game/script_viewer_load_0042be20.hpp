#pragma once
#include <stddef.h>
#include <string.h>
#include "th10/platform/archive_file.hpp"

extern "C" int __cdecl sprintf(char* buffer, const char* format, ...);
extern "C" void __cdecl free(void* block);
void* __cdecl operator new(unsigned int size);

struct ScriptEntry_0042be20 {
    const char* name;
    void* code;
};

// The parser's last two words are a member with its own constructor, which
// runs between the vtable store and the constructor body.
struct ScriptParserTail_0042be20 {
    int first;
    int second;
    ScriptParserTail_0042be20() : first(0), second(0) {}
};

// The 0x1098-byte script parser whose vtable is at 0x0046D0F0. Its
// constructor clears the whole object after the vtable has been published.
struct ScriptParser_0042be20 {
    virtual int Load(char* data);      // 0x00450220
    virtual void Slot04();             // 0x0040C810

    int reserved_004;
    int entry_count;
    unsigned char reserved_00c[0x8C - 0x0C];
    ScriptEntry_0042be20* entries;
    unsigned char reserved_090[0x1090 - 0x90];
    ScriptParserTail_0042be20 tail;

    ScriptParser_0042be20() {
        memset(this, 0, sizeof(ScriptParser_0042be20));
    }
    ~ScriptParser_0042be20() {
        if (entries) {
            free(entries);
            entries = 0;
        }
    }
};
typedef char ScriptParserSize_0042be20[sizeof(ScriptParser_0042be20) == 0x1098 ? 1 : -1];

// Only the retire entry in slot 5 of the previously loaded object is used.
struct ScriptViewerResource_0042be20 {
    virtual void Slot00() = 0;
    virtual void Slot04() = 0;
    virtual void Slot08() = 0;
    virtual void Slot0C() = 0;
    virtual void Slot10() = 0;
    virtual void Retire(int release) = 0;
};

// A menu cursor over `count` entries; the cursor is clamped to the last one.
struct ScriptSelection_0042be20 {
    int cursor;
    int previous;
    int count;

    void Clamp(int& index) const {
        if (count != 0 && index >= count)
            index = count - 1;
    }
};

struct SchedulerTask;

// The screen's loader thread: a PlatformWorker (th10/platform/worker.hpp).
// Its destructor (0x0044C130) republishes the worker dispatch table and stops
// the thread.
struct ScriptViewerWorker_0042be20 {
    const void* vtable;
    void* thread;
    unsigned int thread_id;
    unsigned int stop_requested;
    unsigned int running;
    unsigned int reserved_14;
    void* entry;

    ~ScriptViewerWorker_0042be20();
};

// The "Spt Test" debug screen: picks a script file, loads it and shows one of
// its entries.
struct ScriptViewer_0042be20 {
    unsigned char reserved_000[8];
    SchedulerTask* update_task;
    SchedulerTask* draw_task;
    ScriptViewerWorker_0042be20 worker;
    unsigned char reserved_02c[4];
    int state;                 // 1 = menu, 2 = loading, 3 = running
    const char** script_names;
    int script_count;
    int menu_row;
    unsigned char reserved_040[0x114 - 0x40];
    int script_index;
    unsigned char reserved_118[0x1EC - 0x118];
    ScriptSelection_0042be20 selection;
    unsigned char reserved_1f8[0x2C4 - 0x1F8];
    float position_x;
    float position_y;
    unsigned char reserved_2cc[0x2D8 - 0x2CC];
    ScriptParser_0042be20* parser;
    ScriptViewerResource_0042be20* resource;
    char* script_data;

    __declspec(noinline) ~ScriptViewer_0042be20();
    __declspec(noinline) void ClearScriptNames();
    __declspec(noinline) int LoadScript();
    __declspec(noinline) int Draw();
};
typedef char ScriptViewerStateOffset_0042be20[offsetof(ScriptViewer_0042be20, state) == 0x30 ? 1 : -1];
typedef char ScriptViewerCursorOffset_0042be20[offsetof(ScriptViewer_0042be20, selection) == 0x1EC ? 1 : -1];
typedef char ScriptViewerParserOffset_0042be20[offsetof(ScriptViewer_0042be20, parser) == 0x2D8 ? 1 : -1];

extern "C" ScriptViewer_0042be20* data_00477844;
