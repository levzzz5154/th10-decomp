// 0x00403070: forward one value to the game-state helper at 0x00402CA0 as its
// one stack argument.
//
// Retail: 51              push ecx
//         E8 2A FC FF FF  call 0x00402CA0
//         C3              ret
// The pushed register is ECX by the declared fastcall convention, so
// the forwarder is compiled as a native LTCG cluster
// (see layout/ltcg/fun_00403070.json).

extern "C" void __stdcall asm_FUN_00402ca0_00402ca0(int value);

#pragma code_seg(".text$01forward")
__declspec(noinline) void __fastcall FUN_00403070_Forward(int value) {
    asm_FUN_00402ca0_00402ca0(value);
}
#pragma code_seg()
