/* Raw Ghidra reference; not compilable reconstruction. Address: 0042C9F0 */

undefined4 FUN_0042c9f0(void)

{
  uint *puVar1;
  int iVar2;
  int iVar3;
  undefined4 *puVar4;
  
  iVar3 = FUN_0042caa0();
  if (iVar3 == 0) {
    if (DAT_00477820 != 0) {
      iVar3 = *(int *)(DAT_00477820 + 0x3ec);
      iVar2 = iVar3;
      while ((iVar3 < 300 && ((DAT_00491ff4 & 0x80) == 0))) {
        Sleep(0x10);
        iVar3 = *(int *)(DAT_00477820 + 0x3ec);
        iVar2 = DAT_00477820;
      }
      puVar4 = (undefined4 *)((int)g_pGameStateManager + 0x3ad070);
      if (*(int *)((int)g_pGameStateManager + 0x3ad070) != 0) {
        FUN_00447810(iVar2);
        _free((void *)*puVar4);
        *puVar4 = 0;
      }
    }
    puVar1 = (uint *)(*(int *)(DAT_0047784c + 0xc) + 4);
    *puVar1 = *puVar1 | 2;
    return 0;
  }
  DAT_00491fb8 = ~(DAT_00491ff4 >> 0xc) & 1 | 2;
  return 0;
}

