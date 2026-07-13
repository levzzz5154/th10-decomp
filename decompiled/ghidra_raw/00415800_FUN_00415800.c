/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x00415800
 * Tracking name: FUN_00415800
 * Ghidra name: FUN_00415800
 * Tracked span: 768 bytes
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_00415800(int param_1)

{
  uint uVar1;
  float *pfVar2;
  int iVar3;
  int iVar4;
  
  iVar4 = param_1;
  iVar3 = 10;
  do {
    FUN_004451c0(g_pGameStateManager);
    FUN_004451c0(g_pGameStateManager);
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  iVar3 = 9;
  do {
    FUN_004451c0(g_pGameStateManager);
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  iVar3 = 4;
  do {
    FUN_004451c0(g_pGameStateManager);
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  iVar3 = 7;
  do {
    FUN_004451c0(g_pGameStateManager);
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  if (DAT_00474c58 != 0) {
    FUN_0043bda0();
    FUN_0043bda0();
  }
  if (_DAT_00470b04 < *(float *)(param_1 + 0x9e84)) {
    FUN_0043bda0();
    FUN_0043bda0();
    pfVar2 = (float *)(param_1 + 0x9e94);
    param_1 = 4;
    do {
      if (*pfVar2 != _DAT_00470b04) {
        FUN_0043bda0();
      }
      pfVar2 = pfVar2 + 2;
      param_1 = param_1 + -1;
    } while (param_1 != 0);
  }
  if (DAT_00477704 != 0) {
    if (((*(int *)(DAT_00477704 + 0x10) != 0) &&
        (uVar1 = *(uint *)(*(int *)(DAT_00477704 + 0x10) + 0x2480), (~(uVar1 >> 4) & 1) != 0)) &&
       ((~uVar1 & 1) != 0)) {
      FUN_004451c0(g_pGameStateManager);
    }
    if (((DAT_00477704 != 0) && (-1 < *(int *)(iVar4 + 0x9ec0))) &&
       ((*(int *)(DAT_00477704 + 0x10) != 0 && (*(int *)(iVar4 + 0x9eb8) == 0)))) {
      iVar4 = 2;
      do {
        FUN_004451c0(g_pGameStateManager);
        iVar4 = iVar4 + -1;
      } while (iVar4 != 0);
    }
  }
  return 1;
}

