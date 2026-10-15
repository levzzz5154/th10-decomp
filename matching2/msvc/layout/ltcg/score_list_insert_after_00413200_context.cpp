// Compiler context only; never selected as recovered game code.
#include "../../src/game/enemy/score_list_insert_after_00413200.cpp"

#pragma code_seg(".text$03context")
int __stdcall ScoreListInsertAfterCompilerContext(
        ScoreListNode_00413200** nodes, int count,
        ScoreListNode_00413200* position) {
    while (count--)
        ScoreList_InsertAfter(position, *nodes++);
    return 0;
}
#pragma code_seg()
