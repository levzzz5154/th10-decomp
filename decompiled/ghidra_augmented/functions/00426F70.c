/* Raw Ghidra reference; not compilable reconstruction. Address: 00426F70 */

void FUN_00426f70(int param_1)

{
  void *pvVar1;
  int iVar2;
  int *piVar3;
  int *piVar4;
  undefined4 *puVar5;
  int iVar6;
  undefined4 extraout_ECX;
  undefined4 extraout_ECX_00;
  undefined4 extraout_ECX_01;
  undefined4 extraout_ECX_02;
  undefined4 extraout_ECX_03;
  undefined4 extraout_ECX_04;
  undefined4 extraout_ECX_05;
  int iVar7;
  int iVar8;
  ulonglong uVar9;
  int local_38;
  undefined4 local_34;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  
  iVar2 = param_1;
  pvVar1 = g_pGameStateManager;
  iVar7 = (int)DAT_00474c48;
  if (DAT_00474c48 < 100) {
    piVar4 = (int *)(param_1 + 0x330c);
    iVar8 = 4;
LAB_004270f7:
    iVar6 = *piVar4;
    if (iVar6 != 0) {
      for (piVar3 = *(int **)((int)pvVar1 + 0x72dad4); piVar3 != (int *)0x0;
          piVar3 = (int *)piVar3[1]) {
        if (*(int *)*piVar3 == iVar6) goto LAB_0042712f;
      }
      for (piVar3 = *(int **)((int)pvVar1 + 0x72dadc); piVar3 != (int *)0x0;
          piVar3 = (int *)piVar3[1]) {
        if (*(int *)*piVar3 == iVar6) goto LAB_0042712f;
      }
    }
    goto LAB_00427160;
  }
  piVar4 = (int *)(param_1 + 0x330c);
  local_38 = 4;
LAB_00426fb7:
  iVar8 = *piVar4;
  if (iVar8 != 0) {
    for (piVar3 = *(int **)((int)g_pGameStateManager + 0x72dad4); piVar3 != (int *)0x0;
        piVar3 = (int *)piVar3[1]) {
      if (*(int *)*piVar3 == iVar8) goto LAB_00426ff6;
    }
    for (piVar3 = *(int **)((int)g_pGameStateManager + 0x72dadc); piVar3 != (int *)0x0;
        piVar3 = (int *)piVar3[1]) {
      if (*(int *)*piVar3 == iVar8) goto LAB_00426ff6;
    }
  }
  goto LAB_0042702f;
LAB_0042712f:
  iVar6 = *piVar3;
  if ((iVar6 != 0) && (*(undefined2 *)(iVar6 + 0x304) = 1, *(int *)(iVar6 + 0x18) == 0)) {
    for (piVar3 = *(int **)(iVar6 + 0x14); piVar3 != (int *)0x0; piVar3 = (int *)piVar3[1]) {
      *(undefined2 *)(*piVar3 + 0x304) = 1;
    }
  }
LAB_00427160:
  piVar4 = piVar4 + 0x26;
  iVar8 = iVar8 + -1;
  if (iVar8 == 0) goto LAB_00427169;
  goto LAB_004270f7;
LAB_00426ff6:
  iVar8 = *piVar3;
  if ((iVar8 != 0) &&
     (*(uint *)(iVar8 + 0x35c) = *(uint *)(iVar8 + 0x35c) | 0x4000000, *(int *)(iVar8 + 0x18) == 0))
  {
    for (piVar3 = *(int **)(iVar8 + 0x14); piVar3 != (int *)0x0; piVar3 = (int *)piVar3[1]) {
      *(uint *)(*piVar3 + 0x35c) = *(uint *)(*piVar3 + 0x35c) | 0x4000000;
    }
  }
LAB_0042702f:
  *piVar4 = 0;
  switch(DAT_00474c6c + DAT_00474c68 * 3) {
  case 0:
    piVar3 = (int *)FUN_00448e30(*(undefined4 *)(param_1 + 0x10),0x14,0xf);
    *piVar4 = *piVar3;
    break;
  case 1:
    piVar3 = (int *)FUN_00448e30(*(undefined4 *)(param_1 + 0x10),0x15,0xf);
    *piVar4 = *piVar3;
    break;
  case 2:
    goto LAB_004270bb;
  case 3:
    piVar3 = (int *)FUN_00448e30(*(undefined4 *)(param_1 + 0x10),0x14,0xf);
    *piVar4 = *piVar3;
    break;
  case 4:
    piVar3 = (int *)FUN_00448e30(*(undefined4 *)(param_1 + 0x10),0x15,0xf);
    *piVar4 = *piVar3;
    break;
  case 5:
LAB_004270bb:
    piVar3 = (int *)FUN_00448e30(*(undefined4 *)(param_1 + 0x10),0x16,0xf);
    *piVar4 = *piVar3;
  }
  piVar4 = piVar4 + 0x26;
  local_38 = local_38 + -1;
  if (local_38 == 0) goto LAB_00427169;
  goto LAB_00426fb7;
LAB_00427169:
  param_1 = iVar7 / 0x14;
  if (4 < iVar7 / 0x14) {
    param_1 = 4;
  }
  if (*(int *)(iVar2 + 0x3500) == param_1) {
    return;
  }
  iVar7 = 0;
  local_38 = 0;
  if (0 < param_1) {
LAB_004271a0:
    iVar8 = local_38 * 0x98 + iVar2;
    *(undefined4 *)(iVar8 + 0x32dc) = *(undefined4 *)(iVar2 + 0x3cc);
    *(undefined4 *)(iVar8 + 0x32e0) = *(undefined4 *)(iVar2 + 0x3d0);
    iVar7 = *(int *)(iVar8 + 0x3308);
    if (iVar7 != 0) {
      for (piVar4 = *(int **)((int)g_pGameStateManager + 0x72dad4); piVar4 != (int *)0x0;
          piVar4 = (int *)piVar4[1]) {
        if (*(int *)*piVar4 == iVar7) goto LAB_00427206;
      }
      for (piVar4 = *(int **)((int)g_pGameStateManager + 0x72dadc); piVar4 != (int *)0x0;
          piVar4 = (int *)piVar4[1]) {
        if (*(int *)*piVar4 == iVar7) goto LAB_00427206;
      }
    }
    goto LAB_0042723f;
  }
  goto LAB_00427857;
LAB_00427206:
  iVar7 = *piVar4;
  if ((iVar7 != 0) &&
     (*(uint *)(iVar7 + 0x35c) = *(uint *)(iVar7 + 0x35c) | 0x4000000, *(int *)(iVar7 + 0x18) == 0))
  {
    for (piVar4 = *(int **)(iVar7 + 0x14); piVar4 != (int *)0x0; piVar4 = (int *)piVar4[1]) {
      *(uint *)(*piVar4 + 0x35c) = *(uint *)(*piVar4 + 0x35c) | 0x4000000;
    }
  }
LAB_0042723f:
  *(undefined4 *)(iVar8 + 0x3308) = 0;
  *(int *)(iVar8 + 0x3328) = local_38;
  if (DAT_00474c68 == 0) {
    piVar4 = (int *)(iVar8 + 0x32e4);
    uVar9 = FUN_00463b2c();
    *piVar4 = (int)uVar9;
    uVar9 = FUN_00463b2c();
    *(int *)(iVar8 + 0x32e8) = (int)uVar9;
    uVar9 = FUN_00463b2c();
    *(int *)(iVar8 + 0x32ec) = (int)uVar9;
    uVar9 = FUN_00463b2c();
    *(int *)(iVar8 + 0x32f0) = (int)uVar9;
    if (*(int *)(iVar2 + 0x4474) != 0) {
      piVar4 = (int *)(iVar8 + 0x32ec);
    }
    iVar7 = *(int *)(iVar2 + 0x3cc) + *piVar4;
    iVar6 = *(int *)(iVar2 + 0x3d0) + piVar4[1];
    *(int *)(iVar8 + 0x32d4) = iVar7;
    *(int *)(iVar8 + 0x32d8) = iVar6;
    *(int *)(iVar8 + 0x32dc) = iVar7;
    *(int *)(iVar8 + 0x32e0) = iVar6;
    if (DAT_00474c6c == 0) {
      puVar5 = FUN_00449950();
      puVar5[8] = 0xf;
      puVar5[0xd7] = puVar5[0xd7] | 0x40000000;
      FUN_00449870(puVar5,0x11);
      FUN_004489d0(extraout_ECX_05,(int)g_pGameStateManager);
      *(undefined4 *)(iVar8 + 0x3308) = local_1c;
    }
    else if (DAT_00474c6c == 1) {
      puVar5 = FUN_00449950();
      puVar5[8] = 0xf;
      puVar5[0xd7] = puVar5[0xd7] | 0x40000000;
      FUN_00449870(puVar5,0x12);
      FUN_004489d0(extraout_ECX_04,(int)g_pGameStateManager);
      *(undefined4 *)(iVar8 + 0x3308) = local_20;
    }
    else if (DAT_00474c6c == 2) {
      puVar5 = FUN_00449950();
      puVar5[8] = 0xf;
      puVar5[0xd7] = puVar5[0xd7] | 0x40000000;
      FUN_00449870(puVar5,0x13);
      FUN_004489d0(extraout_ECX_03,(int)g_pGameStateManager);
      *(undefined4 *)(iVar8 + 0x3308) = local_24;
    }
  }
  else if (DAT_00474c68 == 1) {
    if (DAT_00474c6c == 0) {
      if (*(int *)(iVar2 + 0x4474) == 0) {
        uVar9 = FUN_00463b2c();
        *(int *)(iVar8 + 0x32e4) = (int)uVar9;
        uVar9 = FUN_00463b2c();
        *(int *)(iVar8 + 0x32e8) = (int)uVar9;
      }
      uVar9 = FUN_00463b2c();
      *(int *)(iVar8 + 0x32ec) = (int)uVar9;
      uVar9 = FUN_00463b2c();
      iVar7 = DAT_00477834;
      *(int *)(iVar8 + 0x32f0) = (int)uVar9;
      iVar6 = local_38 * 0x40;
      *(undefined4 *)(iVar8 + 0x32d4) = *(undefined4 *)(iVar6 + 0x43ac + iVar7);
      *(undefined4 *)(iVar8 + 0x32d8) = *(undefined4 *)(iVar6 + 0x43b0 + iVar7);
      if ((*(int *)(iVar2 + 0x4474) != 0) && (*(int *)(iVar8 + 0x32a0) == 0)) {
        if (local_38 == 0) {
          uVar9 = FUN_00463b2c();
          *(int *)(iVar2 + 0x32e4) = (int)uVar9;
          uVar9 = FUN_00463b2c();
          *(int *)(iVar2 + 0x32e8) = (int)uVar9;
        }
        else {
          *(undefined4 *)(iVar8 + 0x32e4) = *(undefined4 *)(iVar8 + 0x324c);
          *(undefined4 *)(iVar8 + 0x32e8) = *(undefined4 *)(iVar8 + 0x3250);
        }
      }
      *(code **)(iVar8 + 0x3330) = InvokeZeroCallback;
      puVar5 = FUN_00449950();
      puVar5[8] = 0xf;
      puVar5[0xd7] = puVar5[0xd7] | 0x40000000;
      FUN_00449870(puVar5,0x11);
      FUN_004489d0(extraout_ECX_02,(int)g_pGameStateManager);
      *(undefined4 *)(iVar8 + 0x3308) = local_28;
      *(undefined4 *)(iVar8 + 0x32dc) = *(undefined4 *)(iVar6 + 0x436c + iVar2);
      *(undefined4 *)(iVar8 + 0x32e0) = *(undefined4 *)(iVar6 + 0x4370 + iVar2);
    }
    else if (DAT_00474c6c == 1) {
      uVar9 = FUN_00463b2c();
      *(int *)(iVar8 + 0x32e4) = (int)uVar9;
      uVar9 = FUN_00463b2c();
      *(int *)(iVar8 + 0x32e8) = (int)uVar9;
      uVar9 = FUN_00463b2c();
      *(int *)(iVar8 + 0x32ec) = (int)uVar9;
      uVar9 = FUN_00463b2c();
      *(int *)(iVar8 + 0x32f0) = (int)uVar9;
      piVar4 = (int *)(iVar8 + 0x32ec);
      if (*(int *)(iVar2 + 0x4474) == 0) {
        piVar4 = (int *)(iVar8 + 0x32e4);
      }
      iVar7 = piVar4[1];
      iVar6 = *(int *)(iVar2 + 0x3d0);
      *(int *)(iVar8 + 0x32d4) = *piVar4 + *(int *)(iVar2 + 0x3cc);
      *(int *)(iVar8 + 0x32d8) = iVar6 + iVar7;
      puVar5 = FUN_00449950();
      puVar5[8] = 0xf;
      puVar5[0xd7] = puVar5[0xd7] | 0x40000000;
      FUN_00449870(puVar5,0x12);
      FUN_004489d0(extraout_ECX_01,(int)g_pGameStateManager);
      *(undefined4 *)(iVar8 + 0x3308) = local_2c;
    }
    else if (DAT_00474c6c == 2) {
      uVar9 = FUN_00463b2c();
      *(int *)(iVar8 + 0x32e4) = (int)uVar9;
      uVar9 = FUN_00463b2c();
      *(int *)(iVar8 + 0x32e8) = (int)uVar9;
      if ((*(int *)(iVar2 + 0x4474) == 0) || (*(int *)(iVar8 + 0x32a0) == 0)) {
        iVar7 = *(int *)(iVar2 + 0x3cc) + *(int *)(iVar8 + 0x32e4);
        iVar6 = *(int *)(iVar8 + 0x32e8) + *(int *)(iVar2 + 0x3d0);
        *(int *)(iVar8 + 0x32d4) = iVar7;
        *(int *)(iVar8 + 0x32d8) = iVar6;
        *(int *)(iVar8 + 0x32ec) = iVar7;
        *(int *)(iVar8 + 0x32f0) = iVar6;
      }
      puVar5 = FUN_00449950();
      puVar5[8] = 0xf;
      puVar5[0xd7] = puVar5[0xd7] | 0x40000000;
      FUN_00449870(puVar5,0x13);
      FUN_004489d0(extraout_ECX,(int)g_pGameStateManager);
      *(undefined4 *)(iVar8 + 0x3308) = local_34;
      if (*(int *)(iVar2 + 0x4474) != 0) {
        FUN_00449470(extraout_ECX_00);
      }
      *(code **)(iVar8 + 0x3330) = FUN_00427ad0;
    }
  }
  iVar7 = local_38 + 1;
  *(undefined4 *)(iVar8 + 0x32a0) = 2;
  local_38 = iVar7;
  if (param_1 <= iVar7) goto code_r0x0042784e;
  goto LAB_004271a0;
code_r0x0042784e:
  if (3 < iVar7) {
LAB_004278fd:
    *(int *)(iVar2 + 0x3500) = param_1;
    *(undefined4 *)(iVar2 + 0x332c) = 1;
    *(undefined4 *)(iVar2 + 0x33c4) = 1;
    *(undefined4 *)(iVar2 + 0x345c) = 1;
    *(undefined4 *)(iVar2 + 0x34f4) = 1;
    return;
  }
LAB_00427857:
  pvVar1 = g_pGameStateManager;
  piVar4 = (int *)(iVar7 * 0x98 + 0x3308 + iVar2);
  iVar7 = 4 - iVar7;
LAB_00427873:
  iVar8 = *piVar4;
  piVar4[-0x1a] = 0;
  if (iVar8 != 0) {
    for (piVar3 = *(int **)((int)pvVar1 + 0x72dad4); piVar3 != (int *)0x0; piVar3 = (int *)piVar3[1]
        ) {
      if (*(int *)*piVar3 == iVar8) goto LAB_004278b6;
    }
    for (piVar3 = *(int **)((int)pvVar1 + 0x72dadc); piVar3 != (int *)0x0; piVar3 = (int *)piVar3[1]
        ) {
      if (*(int *)*piVar3 == iVar8) goto LAB_004278b6;
    }
  }
  goto LAB_004278f0;
LAB_004278b6:
  iVar8 = *piVar3;
  if ((iVar8 != 0) && (*(undefined2 *)(iVar8 + 0x304) = 1, *(int *)(iVar8 + 0x18) == 0)) {
    for (piVar3 = *(int **)(iVar8 + 0x14); piVar3 != (int *)0x0; piVar3 = (int *)piVar3[1]) {
      *(undefined2 *)(*piVar3 + 0x304) = 1;
    }
  }
LAB_004278f0:
  piVar4 = piVar4 + 0x26;
  iVar7 = iVar7 + -1;
  if (iVar7 == 0) goto LAB_004278fd;
  goto LAB_00427873;
}

