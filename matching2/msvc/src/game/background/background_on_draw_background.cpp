// 0x00403060: the stage background's first draw task; forwards the stage
// objects to BackGround_DrawBackground (0x00402850) as its stack argument.
//
// Retail: 51              push ecx
//         E8 EA F7 FF FF  call 0x00402850
//         C3              ret
// The pushed register is ECX by the declared fastcall convention, so
// the forwarder is compiled as a native LTCG cluster
// (see build_support/layout/ltcg/fun_403060.json).

extern "C" void __stdcall asm_FUN_00402850_00402850(int value);

#pragma code_seg(".text$01forward")
__declspec(noinline) void __fastcall BackGround_OnDrawBackground(int value) {
    asm_FUN_00402850_00402850(value);
}
#pragma code_seg()
