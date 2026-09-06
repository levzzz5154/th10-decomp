/* Raw Ghidra reference; not compilable reconstruction. Address: 00427E90 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_00427e90(int param_1,int param_2,undefined4 param_3)

{
  short sVar1;
  float fVar2;
  void *pvVar3;
  int iVar4;
  undefined4 *puVar5;
  undefined4 extraout_ECX;
  int iVar6;
  int *piVar7;
  undefined4 extraout_ECX_00;
  undefined4 *puVar8;
  float10 fVar9;
  
  puVar8 = (undefined4 *)(param_1 + 0x49c);
  if ((*(char *)(param_2 + 0x1d) == '\x03') &&
     (*(int *)(param_1 + 0x42f4 + *(char *)(param_2 + 0x1c) * 4) != 0)) {
    return 0;
  }
  iVar4 = 0;
  while (puVar8[0x10] != 0) {
    iVar4 = iVar4 + 1;
    puVar8 = puVar8 + 0x17;
    if (0x7f < iVar4) {
      return 0;
    }
  }
  puVar8[0x10] = 1;
  puVar8[0x16] = param_2;
  if ((puVar8[4] & 1) == 0) {
    puVar8[1] = 0;
    *puVar8 = 0xfff0bdc1;
    puVar8[2] = 0;
    puVar8[3] = &DAT_00476f78;
    puVar8[4] = puVar8[4] | 1;
  }
  puVar8[1] = 0;
  puVar8[2] = 0;
  *puVar8 = 0xffffffff;
  if (*(char *)(param_2 + 0x1c) == '\0') {
    puVar8[5] = *(undefined4 *)(param_1 + 0x3c0);
    puVar8[6] = *(undefined4 *)(param_1 + 0x3c4);
    puVar8[7] = *(undefined4 *)(param_1 + 0x3c8);
  }
  else {
    iVar4 = *(char *)(param_2 + 0x1c) * 0x98;
    fVar2 = (float)*(int *)(iVar4 + 0x3248 + param_1) * _DAT_00470b00;
    puVar8[5] = (float)*(int *)(iVar4 + 0x3244 + param_1) * _DAT_00470b00;
    puVar8[6] = fVar2;
    puVar8[7] = 0;
  }
  if (*(char *)(param_2 + 0x1d) == '\x03') {
    *(undefined4 *)(param_1 + 0x42f4 + *(char *)(param_2 + 0x1c) * 4) = 1;
  }
  puVar8[0xb] = *(undefined4 *)(param_2 + 0x18);
  fVar9 = (float10)NormalizeAngle(*(float *)(param_2 + 0x14));
  puVar8[0xc] = (float)fVar9;
  if ((*(byte *)(puVar8 + 0xf) & 1) == 0) {
    FUN_0044c5d0(puVar8 + 8,(float)puVar8[0xc],(float)puVar8[0xb]);
    puVar8[10] = 0;
  }
  else {
    puVar8[0xd] = (float)puVar8[0xe] + (float)puVar8[0xd];
    fVar9 = (float10)NormalizeAngle((float)puVar8[0xb] + (float)puVar8[0xc]);
    puVar8[0xc] = (float)fVar9;
  }
  puVar8[5] = (*(float *)(param_2 + 4) - (float)puVar8[8]) + (float)puVar8[5];
  puVar8[6] = (*(float *)(param_2 + 8) - (float)puVar8[9]) + (float)puVar8[6];
  sVar1 = *(short *)(param_2 + 0x1e);
  iVar4 = *(int *)(param_1 + 0x10);
  puVar5 = FUN_00449950();
  puVar5[8] = 0xf;
  puVar5[0xd7] = puVar5[0xd7] | 0x40000000;
  FUN_00449870(puVar5,sVar1 + 5);
  pvVar3 = g_pGameStateManager;
  FUN_004489d0(extraout_ECX,(int)g_pGameStateManager);
  puVar8[0x11] = iVar4;
  if (iVar4 != 0) {
    for (piVar7 = *(int **)((int)pvVar3 + 0x72dad4); piVar7 != (int *)0x0; piVar7 = (int *)piVar7[1]
        ) {
      if (*(int *)*piVar7 == iVar4) goto LAB_004280a1;
    }
    piVar7 = *(int **)((int)pvVar3 + 0x72dadc);
    if (piVar7 != (int *)0x0) {
      do {
        if (*(int *)*piVar7 == iVar4) goto LAB_004280a1;
        piVar7 = (int *)piVar7[1];
      } while (piVar7 != (int *)0x0);
      iVar6 = 0;
      goto LAB_004280a7;
    }
  }
  iVar6 = 0;
LAB_004280a7:
  puVar8[0x11] = 0;
LAB_004280aa:
  if ((*(uint *)(iVar6 + 0x35c) & 0x8000000) != 0) {
    *(undefined4 *)(iVar6 + 0x2c) = *(undefined4 *)(param_2 + 0x14);
    *(uint *)(iVar6 + 0x35c) = *(uint *)(iVar6 + 0x35c) | 4;
  }
  if (*(char *)(param_2 + 0x1d) == '\x03') {
    puVar5 = FUN_00449950();
    puVar5[8] = 0xf;
    puVar5[0xd7] = puVar5[0xd7] | 0x40000000;
    FUN_00449870(puVar5,0x10);
    FUN_004489d0(extraout_ECX_00,(int)g_pGameStateManager);
    puVar8[0x12] = iVar4;
  }
  else {
    puVar8[0x12] = 0;
  }
  if (*(code **)(param_2 + 0x24) != (code *)0x0) {
    (**(code **)(param_2 + 0x24))(param_3);
  }
  if (-1 < *(short *)(param_2 + 0x22)) {
    FUN_0043dd10();
  }
  return 0;
LAB_004280a1:
  iVar6 = *piVar7;
  if (iVar6 != 0) goto LAB_004280aa;
  goto LAB_004280a7;
}

