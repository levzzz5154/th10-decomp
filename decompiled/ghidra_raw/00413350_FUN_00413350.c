/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x00413350
 * Tracking name: FUN_00413350
 * Ghidra name: FUN_00413350
 * Tracked span: 256 bytes
 */


uint * FUN_00413350(void)

{
  uint *puVar1;
  undefined4 *puVar2;
  int iVar3;
  uint *puVar4;
  
  puVar1 = operator_new(0x8c);
  if (puVar1 == (uint *)0x0) {
    puVar1 = (uint *)0x0;
  }
  else {
    puVar4 = puVar1;
    for (iVar3 = 0x23; iVar3 != 0; iVar3 = iVar3 + -1) {
      *puVar4 = 0;
      puVar4 = puVar4 + 1;
    }
    *puVar1 = *puVar1 | 2;
    DAT_00477708 = puVar1;
  }
  puVar2 = operator_new(0x24);
  if (puVar2 == (undefined4 *)0x0) {
    puVar2 = (undefined4 *)0x0;
  }
  else {
    puVar2[2] = 0;
    puVar2[3] = 0;
    puVar2[4] = 0;
    *puVar2 = 0;
    puVar2[1] = puVar2[1] & 0xfffffffe;
    puVar2[5] = puVar2;
    puVar2[6] = 0;
    puVar2[7] = 0;
  }
  iVar3 = DAT_00491be4;
  puVar2[2] = &LAB_00413690;
  puVar2[3] = 0;
  puVar2[4] = 0;
  puVar2[8] = puVar1;
  puVar2[1] = puVar2[1] | 3;
  FUN_00449b70(iVar3);
  puVar1[3] = (uint)puVar2;
  return puVar1;
}

