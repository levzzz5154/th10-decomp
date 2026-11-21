// 0x0041C7D0..0x0041C7FB: LaserManager::MarkEligible — mark linked lasers
// (LaserManager::first at +0x18) eligible for removal.
//
// The retail caller supplies the laser manager in EAX. Native LTCG context
// (build_support/layout/ltcg/score_records_mark_eligible.json) preserves that
// internal convention for this ordinary member function.
#include <stddef.h>

struct LaserLinkNode {
    unsigned char reserved_000[8];
    LaserLinkNode* next; // +0x08
    int type;                          // +0x0C
    unsigned char reserved_010[0x40];
    unsigned char marked;              // +0x50
};

struct LaserListView {
    unsigned char reserved_000[0x18];
    LaserLinkNode* linked_head; // +0x18

    __declspec(noinline) int MarkEligible();
};

typedef char ScoreRecords_0041c7d0_head_offset_must_be_18[
    (offsetof(LaserListView, linked_head) == 0x18) ? 1 : -1];
typedef char ScoreLinkedRecord_0041c7d0_marked_offset_must_be_50[
    (offsetof(LaserLinkNode, marked) == 0x50) ? 1 : -1];

#pragma code_seg(".text$01mark")
int LaserListView::MarkEligible() {
    LaserLinkNode* record = linked_head;
    while (record != 0) {
        LaserLinkNode* next = record->next;
        if (record->type != 1 && record->marked == 0)
            record->marked = 1;
        record = next;
    }
    return 0;
}
#pragma code_seg()
