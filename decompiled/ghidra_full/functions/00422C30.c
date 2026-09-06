/* Raw Ghidra reference; not compilable reconstruction. Address: 00422C30 */

void FUN_00422c30(void)

{
  uint uVar1;
  undefined4 extraout_ECX;
  int unaff_ESI;
  
  uVar1 = *(uint *)(DAT_00477810 + 0x58) & 0xffffffef;
  *(uint *)(DAT_00477810 + 0x58) = uVar1;
  FUN_0043e460(uVar1,"UnPause",7,0);
  FUN_004492a0(extraout_ECX,(int)g_pGameStateManager,*(int *)(unaff_ESI + 0x1dc));
  *(undefined4 *)(unaff_ESI + 0x1dc) = 0;
  DAT_00476f78 = *(undefined4 *)(unaff_ESI + 0x2c0);
  return;
}

