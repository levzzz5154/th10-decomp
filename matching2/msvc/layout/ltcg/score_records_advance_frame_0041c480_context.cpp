// Compiler context and ABI anchor only; none of these bytes enter the image.
#include "../../src/unidentified/FUN_0041c480_0041c480.cpp"

extern "C" void __cdecl entry_free_004524a1(void* memory);

// 0x0041C330 takes its records object in EDI - its only caller (the callback
// modelled here) sets it there and no declaration names that register.  Only a
// native /LTCG link assigns it, and only to a callee whose body it can see, so
// the driver carries this anchor body: the records object stays live across a
// loop that calls out, the shape measured to earn the callee-saved EDI.  The
// layout's gaps place the section at the retail address, so the region's own
// call bakes retail's displacement and no byte is patched.  None of these bytes
// are selected as recovered code.
#pragma code_seg(".text$01callee")
extern "C" __declspec(noinline) int __cdecl asm_FUN_0041c330_0041c330(
        ScoreRecords_0041c480* records) {
    ScoreLinkedRecord_0041c480* node = records->head;
    while (node != 0) {
        ScoreLinkedRecord_0041c480* next = node->next;
        entry_free_004524a1(node);
        node = next;
    }
    records->head = 0;
    return 1;
}
#pragma code_seg()

// Synthetic entry: the primary scheduler task only ever reaches this callback
// with the object the score manager published at 0x0047781C, so the context
// materialises that global's link-time address and calls the modelled member.
extern "C" ScoreRecords_0041c480 data_0047781c;

#pragma code_seg(".text$05context")
int __stdcall ScoreRecordsAdvanceFrameCompilerContext() {
    return data_0047781c.AdvanceFrame();
}
#pragma code_seg()
