// Tick the animation VMs referenced by each active script-table entry.
// Clear the entry's active bit when all of its referenced VMs have stopped.
#include "th10/render/anm_script_table_sweep.hpp"

// Native LTCG keeps the receiver in EBX, with plain RET. Both the table count
// and record lengths are signed 16-bit values in the original format.
#pragma code_seg(".text$01sweep")
int ScriptTableSweep::Sweep() {
    for (int index = 0; index < header->count; ++index) {
        ScriptEntry* entry = entries[index];
        if (entry->flags & 1) {
            int running = 0;
            for (ScriptInstruction* instruction = &entry->first;
                 instruction->opcode >= 0;
                 instruction = reinterpret_cast<ScriptInstruction*>(
                     reinterpret_cast<unsigned char*>(instruction) + instruction->length)) {
                SweepAnimation* vm = &animations[instruction->animation_index];
                RunAnimationVm(vm);
                if (vm->script_cursor)
                    ++running;
            }
            if (!running)
                entry->flags &= 0xFE;
        }
    }
    return 0;
}
#pragma code_seg()
