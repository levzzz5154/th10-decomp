// 0x0041C330..0x0041C441: per-frame tick of the score display's records.
//
// Walks the list at +0x18. A record is removed (destroyed, unlinked and freed)
// when its retirement count, once started, reaches 2; when its state is 1; or
// when its update step reports that it is finished. A surviving record
// advances its timer: by one whole step while its speed lies strictly between
// the two bounds, otherwise by the fractional speed. Always returns 1.
//
// The loop is a `for` whose three removals each `continue`, and the removal is
// one inline helper used three times. Retail keeps the third copy whole and
// joins the first two late (the first keeps its own dispatch setup and jumps
// into the second); `else if` chains or a shared `goto` label merge them early
// and come out two bytes short.
#include "th10/game/score_record_list.hpp"

extern "C" void __cdecl entry_free_004524a1(void* memory);
extern "C" float data_00470b68, data_00470b64;

static __forceinline void RemoveRecord(ScoreRecords_0041c480* records,
                                       ScoreLinkedRecord_0041c480* node) {
    node->Destroy();
    --records->live_count;
    node->prev->next = node->next;
    if (node->next != 0)
        node->next->prev = node->prev;
    if (records->cursor == node)
        records->cursor = node->prev;
    entry_free_004524a1(node);
}

static __forceinline void AdvanceTimer(ScoreLinkedRecord_0041c480* node) {
    node->previous = node->current;
    if (*node->speed > data_00470b68 && *node->speed < data_00470b64) {
        ++node->current;
        node->elapsed += 1.0f;
    } else {
        // The double keeps the speed-first x87 order and the unrounded sum
        // for the conversion.
        double step = *node->speed;
        node->current = (int)(node->elapsed = step + node->elapsed);
    }
}

#pragma code_seg(".text$01callee")
extern "C" __declspec(noinline) int __cdecl ScoreRecords_Tick_0041c330(
        ScoreRecords_0041c480* records) {
    for (ScoreLinkedRecord_0041c480* node = records->head, *next; node != 0; node = next) {
        next = node->next;
        if (node->retire_count != 0) {
            ++node->retire_count;
            if (node->retire_count >= 2) {
                RemoveRecord(records, node);
                continue;
            }
        }
        if (node->state == 1) {
            RemoveRecord(records, node);
            continue;
        }
        if (node->Update() != 0) {
            RemoveRecord(records, node);
            continue;
        }
        AdvanceTimer(node);
    }
    return 1;
}
#pragma code_seg()
