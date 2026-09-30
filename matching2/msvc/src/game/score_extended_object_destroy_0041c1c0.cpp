// 0x0041C1C0..0x0041C282: tear down the extended score object: remove its
// scheduler task pair, finalize, unlink and free every entry of its entry
// list, and clear the global pointer at 0x0047781C.  Compiled in the
// scheduler's native-LTCG cluster so that its calls to 0x00449F60 load the
// task register first.
#include "th10/game/scheduler_remove_locked.hpp"

struct ScoreEntry_0041c1c0 {
    virtual void Reserved0();
    virtual void Reserved1();
    virtual void Reserved2();
    virtual void Reserved3();
    virtual void Finalize();
    ScoreEntry_0041c1c0* prev;  // +0x04
    ScoreEntry_0041c1c0* next;  // +0x08
};

struct ScoreExtendedObject_0041c1c0 {
    SchedulerTaskPair tasks;              // +0x00 (tasks at +0x08, +0x0C)
    unsigned char unknown_010[8];
    ScoreEntry_0041c1c0* entries;         // +0x18
};

extern "C" void* data_0047781c;

#pragma code_seg(".text$00gascoredisplayzd")
extern "C" __declspec(noinline) void __stdcall ScoreExtendedObject_DestroyRetail(
        ScoreExtendedObject_0041c1c0* object) {
    RemoveScheduledTaskPair(&object->tasks);
    ScoreEntry_0041c1c0* entry = object->entries;
    while (entry) {
        ScoreEntry_0041c1c0* next = entry->next;
        entry->Finalize();
        entry->prev->next = entry->next;
        if (entry->next)
            entry->next->prev = entry->prev;
        operator delete(entry);
        entry = next;
    }
    data_0047781c = 0;
}
#pragma code_seg()
