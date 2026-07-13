/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x004135D0
 * Tracking name: FUN_004135d0
 * Ghidra name: FUN_004135d0
 * Tracked span: 240 bytes
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_004135d0(void)

{
  undefined4 uVar1;
  int unaff_EDI;
  
  FUN_004134b0();
  if ((DAT_00491fb8 != 0xe) && (g_pGameThread != (void *)0x0)) {
    if (_DAT_00470c30 <= *(float *)(unaff_EDI + 0x34)) {
      if (_DAT_00470c64 <= *(float *)(unaff_EDI + 0x34)) {
        uVar1 = 0xffffffff;
      }
      else {
        uVar1 = 0xffa0a0ff;
      }
    }
    else {
      uVar1 = 0xff5050ff;
    }
    *(undefined4 *)((int)g_pGameThread + 0x8974) = uVar1;
    FUN_00401690("%2.1ffps");
    *(undefined4 *)((int)g_pGameThread + 0x8974) = 0xffffffff;
  }
  *(uint *)(unaff_EDI + 0x20) = *(int *)(unaff_EDI + 0x20) + DAT_00491d66 + 1;
  return 1;
}

