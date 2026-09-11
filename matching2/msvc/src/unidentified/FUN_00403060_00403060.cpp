// 0x00403060: forward one value to the game-state helper at 0x00402850 as its
// one stack argument.
//
// Retail: 51              push ecx
//         E8 EA F7 FF FF  call 0x00402850
//         C3              ret
// The pushed register is ECX by the declared fastcall convention, so
// the forwarder is compiled as a native LTCG cluster
// (see layout/ltcg/fun_00403060.json).

extern "C" void __stdcall asm_FUN_00402850_00402850(int value);

#pragma code_seg(".text$01forward")
__declspec(noinline) void __fastcall FUN_00403060_Forward(int value) {
    asm_FUN_00402850_00402850(value);
}
#pragma code_seg()
