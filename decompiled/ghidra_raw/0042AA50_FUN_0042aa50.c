/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x0042AA50
 * Tracking name: FUN_0042aa50
 * Ghidra name: FUN_0042aa50
 * Tracked span: 208 bytes
 */


void FUN_0042aa50(int param_1)

{
  int iVar1;
  undefined4 *puVar2;
  int iVar3;
  int unaff_ESI;
  undefined4 *puVar4;
  
  puVar2 = operator_new(0x6284);
  if (puVar2 == (undefined4 *)0x0) {
    puVar2 = (undefined4 *)0x0;
  }
  else {
    puVar4 = puVar2;
    for (iVar3 = 0x18a1; iVar3 != 0; iVar3 = iVar3 + -1) {
      *puVar4 = 0;
      puVar4 = puVar4 + 1;
    }
    puVar2[0x1518] = puVar2;
    puVar2[0x189d] = puVar2 + 0x1519;
    puVar2[0x189e] = puVar2;
    puVar2[0x189f] = 0;
    puVar2[0x18a0] = 0;
  }
  iVar3 = param_1 + (unaff_ESI * 3 + 0xf) * 4;
  iVar1 = *(int *)(iVar3 + 4);
  while (iVar1 != 0) {
    iVar3 = *(int *)(iVar3 + 4);
    iVar1 = *(int *)(iVar3 + 4);
  }
  if (*(int *)(iVar3 + 4) != 0) {
    puVar2[0x189f] = *(int *)(iVar3 + 4);
    *(undefined4 **)(*(int *)(iVar3 + 4) + 8) = puVar2 + 0x189e;
  }
  *(undefined4 **)(iVar3 + 4) = puVar2 + 0x189e;
  puVar2[0x18a0] = iVar3;
  return;
}

