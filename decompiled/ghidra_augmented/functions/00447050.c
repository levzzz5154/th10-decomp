/* Raw Ghidra reference; not compilable reconstruction. Address: 00447050 */

undefined4 __fastcall FUN_00447050(undefined4 param_1,undefined4 param_2)

{
  int unaff_ESI;
  int unaff_EDI;
  
  D3DXCreateTexture(g_pD3DDevice,param_2,param_1,1,0,*(undefined4 *)(&DAT_0046f288 + unaff_ESI * 4),
                    1);
  *(undefined4 *)(unaff_EDI + 0xc) = *(undefined4 *)(&DAT_0046f2a0 + unaff_ESI * 4);
  return 0;
}

