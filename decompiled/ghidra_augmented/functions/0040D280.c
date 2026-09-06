/* Raw Ghidra reference; not compilable reconstruction. Address: 0040D280 */

undefined4 FUN_0040d280(undefined4 param_1)

{
  int *piVar1;
  undefined4 *puVar2;
  int iVar3;
  int unaff_EBX;
  int *piVar4;
  
  *(undefined4 *)(unaff_EBX + 0x30) = *(undefined4 *)(DAT_004776f0 + 0x3e0b50);
  piVar1 = operator_new(0x1098);
  if (piVar1 == (int *)0x0) {
    piVar1 = (int *)0x0;
  }
  else {
    piVar1[0x424] = 0;
    piVar1[0x425] = 0;
    piVar4 = piVar1;
    for (iVar3 = 0x426; iVar3 != 0; iVar3 = iVar3 + -1) {
      *piVar4 = 0;
      piVar4 = piVar4 + 1;
    }
    *piVar1 = (int)&PTR_FUN_0046d0b4;
  }
  *(int **)(unaff_EBX + 0x54) = piVar1;
  (**(code **)(*piVar1 + 8))(param_1);
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
  puVar2[2] = FUN_0040d810;
  puVar2[3] = 0;
  puVar2[4] = 0;
  puVar2[8] = unaff_EBX;
  puVar2[1] = puVar2[1] & 0xfffffffd | 1;
  FUN_00449ae0(iVar3);
  *(undefined4 **)(unaff_EBX + 8) = puVar2;
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
  puVar2[2] = FUN_0040d820;
  puVar2[3] = 0;
  puVar2[4] = 0;
  puVar2[8] = unaff_EBX;
  puVar2[1] = puVar2[1] & 0xfffffffd | 1;
  FUN_00449b70(iVar3);
  *(undefined4 **)(unaff_EBX + 0xc) = puVar2;
  if ((*(uint *)(unaff_EBX + 0x50) & 1) == 0) {
    *(undefined4 *)(unaff_EBX + 0x44) = 0;
    *(undefined4 *)(unaff_EBX + 0x40) = 0xfff0bdc1;
    *(undefined4 *)(unaff_EBX + 0x48) = 0;
    *(undefined4 **)(unaff_EBX + 0x4c) = &DAT_00476f78;
    *(uint *)(unaff_EBX + 0x50) = *(uint *)(unaff_EBX + 0x50) | 1;
  }
  *(undefined4 *)(unaff_EBX + 0x44) = 0;
  *(undefined4 *)(unaff_EBX + 0x48) = 0;
  *(undefined4 *)(unaff_EBX + 0x40) = 0xffffffff;
  return 0;
}

