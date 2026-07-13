/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x00447050
 * Tracking name: FUN_00447050
 * Ghidra name: FUN_00447050
 * Tracked span: 112 bytes
 */


undefined4 __fastcall FUN_00447050(undefined4 param_1,undefined4 param_2)

{
  int unaff_ESI;
  int unaff_EDI;
  
  D3DXCreateTexture(g_pD3DDevice,param_2,param_1,1,0,*(undefined4 *)(&DAT_0046f288 + unaff_ESI * 4),
                    1);
  *(undefined4 *)(unaff_EDI + 0xc) = *(undefined4 *)(&DAT_0046f2a0 + unaff_ESI * 4);
  return 0;
}

