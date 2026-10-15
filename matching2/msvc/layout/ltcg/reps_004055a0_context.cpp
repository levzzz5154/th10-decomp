#include "../../src/unreferenced/bomb_construct.cpp"

#pragma code_seg(".text$03context")
int __stdcall RepsContext_004055a0(Rec_004055a0** items, int count) {
    while (count--) { Bomb_Construct(0, *items++); }
    return 0;
}
#pragma code_seg()
