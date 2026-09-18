// Compiler context and ABI anchor only; none of these bytes enter the image.
#include "../../src/game/fun_00405300_00405300.cpp"

extern "C" void __cdecl entry_free_004524a1(void* memory);

// 0x00421480 takes its camera record in EDI - all six retail call sites set it -
// and no declaration can name that register. Only a native /LTCG link can, and
// only for a callee whose body it can see, so the driver carries this anchor
// body. Its shape is the one measured to earn EDI: the record stays live across
// a loop that calls out (the same rule the 0x004477D0 note records); a body
// without such a loop put the record in ESI, EBX or EAX instead. The layout's
// gaps place the section at the retail address, so the region's own call bakes
// retail's displacement. None of these bytes are selected as recovered code.
#pragma code_seg(".text$03camera")
extern "C" __declspec(noinline) void __cdecl asm_Camera_ApplyRetail_00421480(RenderCamera* camera) {
    unsigned int* words = (unsigned int*)camera;
    for (int word = 0; word < 0x118 / 4; word += 4) {
        entry_free_004524a1((void*)words[word]);
    }
    words[0] = 0;
}
#pragma code_seg()

// Synthetic caller: it materialises the state object's link-time address and a
// literal index, exactly the `mov esi,0x491c28 / xor ebx,ebx` pair retail's only
// call site at 0x00402AEC uses, which is what makes the whole-program pass give
// the region ESI for the state and EBX for the index.
extern "C" RenderStageState_00405300 data_00491c28;

#pragma code_seg(".text$05context")
int __stdcall RenderStageSelectCompilerContext(int count) {
    while (count--) {
        data_00491c28.SelectDefaultStage(0);
    }
    return count;
}
#pragma code_seg()
