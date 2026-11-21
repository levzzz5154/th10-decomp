// 0x00403070: the stage background's second draw task; forwards the stage
// objects to BackGround_Draw (0x00402CA0) as its stack argument.
//
// Retail: 51              push ecx
//         E8 2A FC FF FF  call 0x00402CA0
//         C3              ret
// The pushed register is ECX by the declared fastcall convention, so
// the forwarder is compiled as a native LTCG cluster
// (see build_support/layout/ltcg/fun_403070.json).

extern "C" void __stdcall BackGround_DrawForeground(int value);

#pragma code_seg(".text$01forward")
__declspec(noinline) void __fastcall BackGround_OnDraw(int value) {
    BackGround_DrawForeground(value);
}
#pragma code_seg()
