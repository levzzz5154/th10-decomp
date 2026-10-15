// Compiler context and ABI anchors only; none of these bytes enter the image.
// The script starter, its loader and their own context come from the
// 0x00404F30 cluster driver so the starter keeps its ESI/EAX entry here.
#include "entity_start_script_00404f30_context.cpp"
#include "../../../src/game/item/item_enter_state_2_0041be40.cpp"

#pragma code_seg(".text$04context")
extern "C" int __stdcall ItemEnterState2Context_0041be40(Item_0041b8e0* items, int count) {
    int total = 0;
    for (int i = 0; i < count; ++i)
        total += items[i].EnterState2();
    return total;
}
#pragma code_seg()
