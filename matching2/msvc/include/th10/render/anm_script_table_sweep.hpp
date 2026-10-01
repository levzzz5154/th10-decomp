#pragma once
#include <stddef.h>

#pragma pack(push, 1)
struct ScriptInstruction {
    short opcode;
    short length;
    short reserved_004;
    short animation_index;
};
struct ScriptEntry {
    unsigned char reserved_000[3];
    unsigned char flags;
    unsigned char reserved_004[0x18];
    ScriptInstruction first;
};
#pragma pack(pop)

struct SweepAnimation {
    unsigned char reserved_000[0x390];
    void* script_cursor;
    unsigned char reserved_394[0x18];
};
struct ScriptTableHeader {
    short count;
};
struct ScriptTableSweep {
    unsigned char reserved_000[0x10];
    ScriptTableHeader* header;
    ScriptEntry** entries;
    unsigned char reserved_018[0x164];
    SweepAnimation* animations;
    __declspec(noinline) int Sweep();
};

// Genuine animation interpreter: a stack object pointer, returning with RET4.
extern "C" int __stdcall RunAnimationVm(SweepAnimation* vm);
typedef char SweepAnimationStride[sizeof(SweepAnimation) == 0x3AC ? 1 : -1];
typedef char SweepAnimationCursorOffset[offsetof(SweepAnimation, script_cursor) == 0x390 ? 1 : -1];
typedef char ScriptInstructionExtent[sizeof(ScriptInstruction) == 8 ? 1 : -1];
typedef char ScriptInstructionIndexOffset[offsetof(ScriptInstruction, animation_index) == 6 ? 1 : -1];
typedef char ScriptEntryFlagsOffset[offsetof(ScriptEntry, flags) == 3 ? 1 : -1];
typedef char ScriptEntryFirstOffset[offsetof(ScriptEntry, first) == 0x1C ? 1 : -1];
typedef char ScriptSweepHeaderOffset[offsetof(ScriptTableSweep, header) == 0x10 ? 1 : -1];
typedef char ScriptSweepEntriesOffset[offsetof(ScriptTableSweep, entries) == 0x14 ? 1 : -1];
typedef char ScriptSweepPoolOffset[offsetof(ScriptTableSweep, animations) == 0x17C ? 1 : -1];
