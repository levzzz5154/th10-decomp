#pragma once

// Retail 0x00450470 - the shared script-label lookup.  Retail performs an
// ANSI strcmp binary search over the sorted script-name table: entry count
// at +8, entries pointer at +0x8C, 8-byte {name,value} stride on 32-bit
// retail.  The matched record's value is a code offset and callers enter
// 16 bytes past it (past the ECL record header); a missing name yields 0.
//
// The three host implementations route through this helper:
//   src/script/final_script_runtime.cpp   ResolveScriptLabel (canonical)
//   src/script/ecl_vm.cpp                 ECL_FindScriptLabel
//   src/script/ecl_core_interpreter.cpp   EclCore_ResolveScriptLabel
// The search is typed on the caller's own table/record structs: only the
// name field at +0 is touched, so each implementation keeps the stride of
// its own layout (host structs pad the entries pointer past +0x8C to +0x90;
// the 32-bit builds collapse to the retail 8-byte records and +0x8C).

#include <cstring>

namespace th10 { namespace script_label_search {

// Binary-search `name` over `table` using ANSI strcmp ordering.  Returns
// the matching entry, or nullptr when the name is absent.
template <typename Table, typename Entry>
inline const Entry* FindScriptLabelEntry(const Table* table,
                                         const char* name) {
    int low = 0;
    int high = table->count - 1;
    if (high < 0)
        return nullptr;
    const Entry* entries = table->entries;
    while (low <= high) {
        const int middle = low + (high - low) / 2;
        const int order = std::strcmp(name, entries[middle].name);
        if (order == 0)
            return &entries[middle];
        if (order > 0)
            low = middle + 1;
        else
            high = middle - 1;
    }
    return nullptr;
}

} }  // namespace th10::script_label_search
