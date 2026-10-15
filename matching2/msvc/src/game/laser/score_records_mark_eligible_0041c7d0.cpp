// 0x0041C7D0..0x0041C7FB: mark linked lasers eligible for removal.
//
// The retail caller supplies the score-record owner in EAX. Native LTCG
// context (build_support/layout/ltcg/score_records_mark_eligible.json) preserves
// that internal convention for this ordinary member function.
#include <stddef.h>

struct ScoreLinkedRecord_0041c7d0 {
    unsigned char reserved_000[8];
    ScoreLinkedRecord_0041c7d0* next; // +0x08
    int type;                          // +0x0C
    unsigned char reserved_010[0x40];
    unsigned char marked;              // +0x50
};

struct ScoreRecords_0041c7d0 {
    unsigned char reserved_000[0x18];
    ScoreLinkedRecord_0041c7d0* linked_head; // +0x18

    __declspec(noinline) int MarkEligible();
};

typedef char ScoreRecords_0041c7d0_head_offset_must_be_18[
    (offsetof(ScoreRecords_0041c7d0, linked_head) == 0x18) ? 1 : -1];
typedef char ScoreLinkedRecord_0041c7d0_marked_offset_must_be_50[
    (offsetof(ScoreLinkedRecord_0041c7d0, marked) == 0x50) ? 1 : -1];

#pragma code_seg(".text$01mark")
int ScoreRecords_0041c7d0::MarkEligible() {
    ScoreLinkedRecord_0041c7d0* record = linked_head;
    while (record != 0) {
        ScoreLinkedRecord_0041c7d0* next = record->next;
        if (record->type != 1 && record->marked == 0)
            record->marked = 1;
        record = next;
    }
    return 0;
}
#pragma code_seg()
