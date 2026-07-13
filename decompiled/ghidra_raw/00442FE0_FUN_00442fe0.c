/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x00442FE0
 * Tracking name: FUN_00442fe0
 * Ghidra name: FUN_00442fe0
 * Tracked span: 160 bytes
 */


undefined4 __fastcall FUN_00442fe0(undefined4 param_1,undefined4 *param_2)

{
  int in_EAX;
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  
  puVar2 = param_2;
  puVar3 = *(undefined4 **)(in_EAX + 0x72dacc);
  for (iVar1 = 7; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar3 = *puVar2;
    puVar2 = puVar2 + 1;
    puVar3 = puVar3 + 1;
  }
  puVar2 = param_2 + 7;
  puVar3 = (undefined4 *)(*(int *)(in_EAX + 0x72dacc) + 0x1c);
  for (iVar1 = 7; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar3 = *puVar2;
    puVar2 = puVar2 + 1;
    puVar3 = puVar3 + 1;
  }
  puVar2 = param_2 + 0xe;
  puVar3 = (undefined4 *)(*(int *)(in_EAX + 0x72dacc) + 0x38);
  for (iVar1 = 7; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar3 = *puVar2;
    puVar2 = puVar2 + 1;
    puVar3 = puVar3 + 1;
  }
  puVar2 = param_2 + 7;
  puVar3 = (undefined4 *)(*(int *)(in_EAX + 0x72dacc) + 0x54);
  for (iVar1 = 7; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar3 = *puVar2;
    puVar2 = puVar2 + 1;
    puVar3 = puVar3 + 1;
  }
  puVar2 = param_2 + 0xe;
  puVar3 = (undefined4 *)(*(int *)(in_EAX + 0x72dacc) + 0x70);
  for (iVar1 = 7; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar3 = *puVar2;
    puVar2 = puVar2 + 1;
    puVar3 = puVar3 + 1;
  }
  puVar2 = param_2 + 0x15;
  puVar3 = (undefined4 *)(*(int *)(in_EAX + 0x72dacc) + 0x8c);
  for (iVar1 = 7; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar3 = *puVar2;
    puVar2 = puVar2 + 1;
    puVar3 = puVar3 + 1;
  }
  *(int *)(in_EAX + 0x72dacc) = *(int *)(in_EAX + 0x72dacc) + 0xa8;
  *(int *)(in_EAX + 0x3adac8) = *(int *)(in_EAX + 0x3adac8) + 1;
  return 0;
}

