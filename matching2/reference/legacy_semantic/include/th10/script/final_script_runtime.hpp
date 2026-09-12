#pragma once

#include <cstdint>

// Retail 0x00450700: bind a named ECL subroutine into the VM's current
// function record.  The retail calling convention is __usercall (name in ecx,
// vm in esi); the readable form is a plain two-argument call.

namespace th10 { namespace script_final {

// The current function record, pointed to from vm+0x04.
struct EclFunctionRecord {
    uint32_t name;      // +0x00, cleared to 0 by the binder
    uint32_t resolved;  // +0x04, subroutine entry = table value + 16
};

// One sorted script-name table record (retail 8-byte stride).
struct EclScriptEntry {
    const char* name;   // +0x00
    uint32_t value;     // +0x04, code offset resolved to value + 16
};

// The script table object stored at vm+0x102C (retail 0x00450470's owner).
struct EclScriptTable {
    uint32_t reserved_00;               // +0x00
    uint32_t reserved_04;               // +0x04
    int32_t count;                      // +0x08, sorted entry count
    uint32_t reserved_0C[0x20];         // +0x0C .. +0x8B
    const EclScriptEntry* entries;      // +0x8C (140)
};

// The ECL VM view used by the binder: only +0x04 and +0x102C are read.
struct EclVm {
    uint32_t reserved_00;               // +0x00
    EclFunctionRecord* current_record;  // +0x04
    uint32_t reserved_08[0x409];        // +0x08 .. +0x102B
    EclScriptTable* script_table;       // +0x102C (4140)
};

// 0x00450700 - Resolve `name` in the VM's script table and publish the entry
// point into the current function record, clearing the record's name slot.
int EclVm_BindSubroutine(EclVm* vm, const char* name);

} }  // namespace th10::script_final
