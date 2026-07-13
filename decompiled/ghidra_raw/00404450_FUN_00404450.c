/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x00404450
 * Tracking name: FUN_00404450
 * Ghidra name: FUN_00404450
 * Tracked span: 224 bytes
 */


void FUN_00404450(int param_1)

{
  uint *puVar1;
  undefined4 *puVar2;
  short sVar3;
  int iVar4;
  short *psVar5;
  int local_4;
  
  iVar4 = param_1;
  *(uint *)(*(int *)(param_1 + 8) + 4) = *(uint *)(*(int *)(param_1 + 8) + 4) | 2;
  puVar1 = (uint *)(*(int *)(param_1 + 0xc) + 4);
  *puVar1 = *puVar1 | 2;
  puVar1 = (uint *)(*(int *)(param_1 + 0x2a40) + 4);
  *puVar1 = *puVar1 | 2;
  puVar2 = (undefined4 *)(param_1 + 0x10);
  param_1 = 0;
  local_4 = 0;
  if (0 < *(short *)*puVar2) {
    do {
      *(undefined1 *)(*(int *)(*(int *)(iVar4 + 0x14) + local_4 * 4) + 3) = 1;
      psVar5 = (short *)(*(int *)(*(int *)(iVar4 + 0x14) + local_4 * 4) + 0x1c);
      sVar3 = *psVar5;
      while (-1 < sVar3) {
        FUN_00404f30(*(void **)(iVar4 + 0x178),*(void **)(iVar4 + 0x178));
        psVar5[3] = (short)param_1;
        param_1 = param_1 + 1;
        psVar5 = (short *)((int)psVar5 + (int)psVar5[1]);
        sVar3 = *psVar5;
      }
      local_4 = local_4 + 1;
    } while (local_4 < **(short **)(iVar4 + 0x10));
    *(undefined4 *)(iVar4 + 0x4c) = *(undefined4 *)(iVar4 + 0x1c);
    return;
  }
  *(undefined4 *)(iVar4 + 0x4c) = *(undefined4 *)(iVar4 + 0x1c);
  return;
}

