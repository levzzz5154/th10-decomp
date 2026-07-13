/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x0041A120
 * Tracking name: FUN_0041a120
 * Ghidra name: FUN_0041a120
 * Tracked span: 224 bytes
 */


undefined4 * FUN_0041a120(int param_1,char *param_2)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  int iVar4;
  undefined4 *unaff_EBX;
  undefined4 *puVar5;
  
  puVar2 = operator_new(0x88);
  if (puVar2 == (undefined4 *)0x0) {
    puVar2 = (undefined4 *)0x0;
  }
  else {
    puVar5 = puVar2;
    for (iVar4 = 0x22; iVar4 != 0; iVar4 = iVar4 + -1) {
      *puVar5 = 0;
      puVar5 = puVar5 + 1;
    }
    puVar2[4] = 0;
    puVar2[5] = 0;
    puVar2[3] = puVar2;
    puVar2[0x21] = 0xffffffff;
    puVar2[0x1b] = 300;
    puVar2[0x1f] = 0x3f800000;
    puVar2[0x1c] = 0xffffffff;
  }
  iVar4 = param_1 + (DAT_00474c7c * 3 + 0x1e) * 4;
  iVar1 = *(int *)(iVar4 + 4);
  while (iVar1 != 0) {
    iVar4 = *(int *)(iVar4 + 4);
    iVar1 = *(int *)(iVar4 + 4);
  }
  if (*(int *)(iVar4 + 4) != 0) {
    puVar2[4] = *(int *)(iVar4 + 4);
    *(undefined4 **)(*(int *)(iVar4 + 4) + 8) = puVar2 + 3;
  }
  *(undefined4 **)(iVar4 + 4) = puVar2 + 3;
  puVar2[5] = iVar4;
  puVar2[0x1c] = 0x1e;
  *puVar2 = *unaff_EBX;
  puVar2[1] = unaff_EBX[1];
  puVar2[2] = unaff_EBX[2];
  _strncpy((char *)(puVar2 + 7),param_2,0x40);
  puVar2[0x19] = 0;
  puVar2[0x1a] = DAT_00474c84;
  uVar3 = DAT_00474c8c;
  if (DAT_00474c84 == 0) {
    uVar3 = DAT_00474c88;
  }
  puVar2[0x18] = uVar3;
  return puVar2;
}

