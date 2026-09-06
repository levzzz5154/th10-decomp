/* Raw Ghidra reference; not compilable reconstruction. Address: 00415B00 */

undefined4 * FUN_00415b00(undefined4 *param_1,undefined4 param_2)

{
  undefined4 uVar1;
  int *piVar2;
  int *piVar3;
  void *pvVar4;
  undefined4 *puVar5;
  int iVar6;
  undefined4 extraout_ECX;
  undefined4 extraout_ECX_00;
  undefined4 extraout_ECX_01;
  undefined4 extraout_ECX_02;
  int iVar7;
  
  param_1[5] = param_1[5] & 0xfffffffe;
  param_1[10] = param_1[10] & 0xfffffffe;
  param_1[0xf] = param_1[0xf] & 0xfffffffe;
  puVar5 = param_1;
  for (iVar6 = 0x24; iVar6 != 0; iVar6 = iVar6 + -1) {
    *puVar5 = 0;
    puVar5 = puVar5 + 1;
  }
  if ((param_1[5] & 1) == 0) {
    param_1[2] = 0;
    param_1[1] = 0xfff0bdc1;
    param_1[3] = 0;
    param_1[4] = &DAT_00476f78;
    param_1[5] = param_1[5] | 1;
  }
  param_1[2] = 0;
  param_1[3] = 0;
  param_1[1] = 0xffffffff;
  if ((param_1[10] & 1) == 0) {
    param_1[7] = 0;
    param_1[6] = 0xfff0bdc1;
    param_1[8] = 0;
    param_1[9] = &DAT_00476f78;
    param_1[10] = param_1[10] | 1;
  }
  param_1[7] = 0;
  param_1[8] = 0;
  param_1[6] = 0xffffffff;
  param_1[0x16] = 0;
  if ((param_1[0xf] & 1) == 0) {
    param_1[0xc] = 0;
    param_1[0xb] = 0xfff0bdc1;
    param_1[0xd] = 0;
    param_1[0xe] = &DAT_00476f78;
    param_1[0xf] = param_1[0xf] | 1;
  }
  param_1[0xb] = 0xffffffff;
  pvVar4 = g_pGameThread;
  param_1[0xc] = 0;
  param_1[0xd] = 0;
  param_1[0x17] = param_2;
  uVar1 = *(undefined4 *)((int)pvVar4 + 0x899c);
  puVar5 = FUN_00449950();
  puVar5[8] = 0xf;
  puVar5[0xd7] = puVar5[0xd7] | 0x40000000;
  FUN_00449870(puVar5,0);
  FUN_004489d0(extraout_ECX,(int)g_pGameStateManager);
  pvVar4 = g_pGameThread;
  param_1[0x13] = uVar1;
  uVar1 = *(undefined4 *)((int)pvVar4 + 0x899c);
  puVar5 = FUN_00449950();
  puVar5[0xd7] = puVar5[0xd7] | 0x40000000;
  puVar5[8] = 0xf;
  FUN_00449870(puVar5,1);
  pvVar4 = g_pGameStateManager;
  FUN_004489d0(extraout_ECX_00,(int)g_pGameStateManager);
  param_1[0x14] = uVar1;
  iVar6 = FUN_004491c0(param_1[0x13],(int)pvVar4,param_1[0x13]);
  if (iVar6 == 0) {
    param_1[0x13] = 0;
  }
  *(undefined1 *)(iVar6 + 0x3a0) = 0x10;
  iVar6 = FUN_004491c0(extraout_ECX_01,(int)pvVar4,param_1[0x13]);
  if (iVar6 == 0) {
    param_1[0x13] = 0;
  }
  *(undefined1 *)(iVar6 + 0x3a1) = 0x10;
  iVar6 = FUN_004491c0(extraout_ECX_02,(int)pvVar4,param_1[0x14]);
  if (iVar6 == 0) {
    param_1[0x14] = 0;
  }
  *(undefined1 *)(iVar6 + 0x3a0) = 0x10;
  iVar6 = FUN_004491c0(param_1[0x14],(int)pvVar4,param_1[0x14]);
  if (iVar6 == 0) {
    param_1[0x14] = 0;
  }
  iVar7 = DAT_004776f0;
  *(undefined1 *)(iVar6 + 0x3a1) = 0x10;
  param_1[0x18] = 0x41000000;
  param_1[0x19] = 0;
  param_1[0x1a] = 0;
  param_1[0x1b] = 0x41c00000;
  param_1[0x1c] = 0;
  param_1[0x20] = 0;
  param_1[0x22] = 0xf8f08f;
  param_1[0x23] = 0x8088ff;
  param_1[0x21] = 0;
  param_1[0x1d] = 0;
  iVar7 = iVar7 + 0x60;
  iVar6 = 2000;
  do {
    if ((*(short *)(iVar7 + 0x446) != 0) && (*(short *)(iVar7 + 0x446) != 3)) {
      FUN_00408030();
    }
    iVar7 = iVar7 + 0x7f0;
    iVar6 = iVar6 + -1;
  } while (iVar6 != 0);
  piVar2 = *(int **)(DAT_0047781c + 0x18);
  while (piVar3 = piVar2, piVar3 != (int *)0x0) {
    piVar2 = (int *)piVar3[2];
    if (piVar3[3] != 1) {
      (**(code **)(*piVar3 + 0x14))(0);
    }
  }
  FUN_0040e6a0(DAT_00477704);
  return param_1;
}

