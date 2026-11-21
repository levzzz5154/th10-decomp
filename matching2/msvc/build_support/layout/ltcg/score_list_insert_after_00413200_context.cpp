// Compiler context only; never selected as recovered game code.
#include "../../../src/game/enemy/list_insert_after.cpp"

#pragma code_seg(".text$03context")
int __stdcall ScoreListInsertAfterCompilerContext(
        IntrusiveListNode** nodes, int count,
        IntrusiveListNode* position) {
    while (count--)
        ListNode_InsertAfter(position, *nodes++);
    return 0;
}
#pragma code_seg()
