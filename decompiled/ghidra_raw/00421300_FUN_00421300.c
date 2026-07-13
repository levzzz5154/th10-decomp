/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x00421300
 * Tracking name: FUN_00421300
 * Ghidra name: FUN_00421300
 * Tracked span: 384 bytes
 */


void __thiscall FUN_00421300(void *this,int param_1)

{
  int *piVar1;
  void *pvVar2;
  int iVar3;
  int iVar4;
  int extraout_ECX;
  int extraout_ECX_00;
  
  pvVar2 = g_pGameStateManager;
  if (*(int *)(param_1 + 0x6fc) == 1) {
    iVar3 = FUN_004491c0(this,(int)g_pGameStateManager,DAT_00477824);
    iVar4 = extraout_ECX;
    if ((iVar3 != 0) && (*(undefined2 *)(iVar3 + 0x304) = 2, *(int *)(iVar3 + 0x18) == 0)) {
      for (piVar1 = *(int **)(iVar3 + 0x14); piVar1 != (int *)0x0; piVar1 = (int *)piVar1[1]) {
        iVar4 = *piVar1;
        *(undefined2 *)(iVar4 + 0x304) = 2;
      }
    }
    iVar3 = FUN_004491c0(iVar4,(int)pvVar2,DAT_00477828);
    iVar4 = extraout_ECX_00;
    if ((iVar3 != 0) && (*(undefined2 *)(iVar3 + 0x304) = 2, *(int *)(iVar3 + 0x18) == 0)) {
      for (piVar1 = *(int **)(iVar3 + 0x14); piVar1 != (int *)0x0; piVar1 = (int *)piVar1[1]) {
        iVar4 = *piVar1;
        *(undefined2 *)(iVar4 + 0x304) = 2;
      }
    }
    iVar4 = FUN_004491c0(iVar4,(int)pvVar2,DAT_0047782c);
    if ((iVar4 != 0) && (*(undefined2 *)(iVar4 + 0x304) = 2, *(int *)(iVar4 + 0x18) == 0)) {
      for (piVar1 = *(int **)(iVar4 + 0x14); piVar1 != (int *)0x0; piVar1 = (int *)piVar1[1]) {
        *(undefined2 *)(*piVar1 + 0x304) = 2;
      }
    }
    DAT_00477824 = 0;
    DAT_00477828 = 0;
    DAT_0047782c = 0;
    *(undefined4 *)(param_1 + 0x6fc) = 2;
  }
  if (DAT_00491bec != 0) {
    DAT_00491bec = 0;
  }
  return;
}

