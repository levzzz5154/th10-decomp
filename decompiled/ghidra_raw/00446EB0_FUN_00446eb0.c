/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x00446EB0
 * Tracking name: FUN_00446eb0
 * Ghidra name: FUN_00446eb0
 * Tracked span: 144 bytes
 */


undefined4 __fastcall
FUN_00446eb0(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
            undefined4 param_5)

{
  int in_EAX;
  int iVar1;
  int unaff_ESI;
  
  if (((byte)DAT_00491d78 & 1) != 0) {
    iVar1 = *(int *)(&DAT_0046f288 + in_EAX * 4);
    if ((iVar1 == 0x15) || (iVar1 == 0)) {
      in_EAX = 5;
    }
    else if (iVar1 == 0x14) {
      in_EAX = 3;
    }
  }
  iVar1 = D3DXCreateTextureFromFileInMemoryEx
                    (g_pD3DDevice,*(undefined4 *)(unaff_ESI + 4),*(undefined4 *)(unaff_ESI + 8),
                     param_5,param_2,0,0,*(undefined4 *)(&DAT_0046f288 + in_EAX * 4),1,1,0xffffffff,
                     param_4,0,0);
  if (iVar1 != 0) {
    return 0xffffffff;
  }
  FUN_004465b0();
  *(undefined4 *)(unaff_ESI + 0xc) = *(undefined4 *)(&DAT_0046f2a0 + in_EAX * 4);
  return 0;
}

