// 0x0041C7D0..0x0041C7FB: mark linked lasers eligible for removal.
//
// The retail caller supplies the score-record owner in EAX. Native LTCG
// context (build_support/layout/ltcg/score_records_mark_eligible.json) preserves
// that internal convention for this ordinary member function.
#include <stddef.h>

struct ScoreLinkedRecord {
    unsigned char reserved_000[8];
    ScoreLinkedRecord* next; // +0x08
    int type;                          // +0x0C
    unsigned char reserved_010[0x40];
    unsigned char marked;              // +0x50
};

struct ScoreRecords {
    unsigned char reserved_000[0x18];
    ScoreLinkedRecord* linked_head; // +0x18

    __declspec(noinline) int MarkEligible();
};

typedef char ScoreRecords_0041c7d0_head_offset_must_be_18[
    (offsetof(ScoreRecords, linked_head) == 0x18) ? 1 : -1];
typedef char ScoreLinkedRecord_0041c7d0_marked_offset_must_be_50[
    (offsetof(ScoreLinkedRecord, marked) == 0x50) ? 1 : -1];

#pragma code_seg(".text$01mark")
int ScoreRecords::MarkEligible() {
    ScoreLinkedRecord* record = linked_head;
    while (record != 0) {
        ScoreLinkedRecord* next = record->next;
        if (record->type != 1 && record->marked == 0)
            record->marked = 1;
        record = next;
    }
    return 0;
}
#pragma code_seg()
