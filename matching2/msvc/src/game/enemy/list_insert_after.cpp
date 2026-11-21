// 0x00413200..0x00413216: insert a score-list node after a position.
//
// The retail routine receives the new node in EAX and the insertion position
// in ECX. Its native-LTCG cluster supplies that internal register convention
// while keeping this implementation as ordinary, named C++.
struct IntrusiveListNode {
    unsigned char reserved_000[4];
    IntrusiveListNode* next;
    IntrusiveListNode* previous;
};

typedef char ScoreListNode_00413200_size_must_be_0c[
    sizeof(IntrusiveListNode) == 0x0c ? 1 : -1];

#pragma code_seg(".text$01insert")
__declspec(noinline) void ListNode_InsertAfter(
        IntrusiveListNode* position,
        IntrusiveListNode* node) {
    if (position->next != 0) {
        node->next = position->next;
        position->next->previous = node;
    }
    position->next = node;
    node->previous = position;
}
#pragma code_seg()
