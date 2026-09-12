// Semantic reconstruction of retail 0x00450700: bind a named ECL subroutine
// into the VM's current function record.  The retail body is three lines:
//
//   *(*(a2 + 4) + 4) = sub_450470(*(a2 + 4140), a1);
//   **(_DWORD **)(a2 + 4) = 0;
//
// with the name in ecx and the VM in esi.  This file is also the canonical
// host of the resolver it calls, retail 0x00450470 (ResolveScriptLabel
// below): a binary search over the sorted script-name table whose match
// value is a code offset; the entry point is 16 bytes past it, past the ECL
// record header.  The other host implementations (ECL_FindScriptLabel in
// ecl_vm.cpp, EclCore_ResolveScriptLabel in ecl_core_interpreter.cpp)
// delegate to the shared search helper in th10/script/script_label_search.hpp.

#include "th10/script/final_script_runtime.hpp"
#include "th10/script/script_label_search.hpp"

#include <cstring>

namespace th10::script_final {
namespace {

// 0x00450470 - ResolveScriptLabel: binary search over the sorted
// {name, value} table; returns value + 16, or 0 when the name is absent.
// The search is th10::script_label_search::FindScriptLabelEntry; this
// wrapper applies the canonical +16 entry-point convention.
int ResolveScriptLabel(const EclScriptTable* table, const char* name) {
    const EclScriptEntry* entry =
        th10::script_label_search::FindScriptLabelEntry<EclScriptTable,
                                                         EclScriptEntry>(
            table, name);
    return entry == nullptr ? 0 : static_cast<int>(entry->value) + 16;
}

}  // namespace

// 0x00450700 - EclVm_BindSubroutine: resolve the named subroutine from the
// VM's script table and publish it into the current function record, then
// clear the record's name slot.  The caller (retail 0x0040DC80) inlines the
// same sequence: record->resolved = ResolveScriptLabel(vm->script_table,
// name); record->name = 0.
int EclVm_BindSubroutine(EclVm* vm, const char* name) {
    EclFunctionRecord* record = vm->current_record;
    record->resolved = ResolveScriptLabel(vm->script_table, name);
    record->name = 0;
    return 0;
}

}  // namespace th10::script_final
