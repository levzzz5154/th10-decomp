/* Raw Ghidra reference; not compilable reconstruction. Address: 00414900 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 __fastcall FUN_00414900(int param_1,uint param_2,int param_3)

{
  undefined4 *puVar1;
  float fVar2;
  float *pfVar3;
  void *_Memory;
  undefined2 *puVar4;
  uint uVar5;
  int iVar6;
  int *piVar7;
  int *piVar8;
  undefined4 *puVar9;
  uint uVar10;
  int extraout_ECX;
  int extraout_ECX_00;
  int extraout_ECX_01;
  undefined4 extraout_ECX_02;
  uint uVar11;
  int iVar12;
  int iVar13;
  int iVar14;
  void *pvVar15;
  int iVar16;
  bool bVar17;
  bool bVar18;
  ulonglong uVar19;
  
  if ((*(byte *)(param_3 + 0x9eb4) & 0x10) != 0) {
    param_1 = *(int *)(param_3 + 0x9ecc) + 1;
    *(int *)(param_3 + 0x9ecc) = param_1;
    if (0x77 < param_1) {
      DAT_00491fb8 = (-(uint)((DAT_00491ff4 & 0x1000) != 0) & 0xfffffff4) + 0xe;
    }
  }
  iVar14 = param_3 + 0x4980;
  iVar12 = 9;
  do {
    uVar19 = FUN_0043ee30(param_1,param_2,iVar14);
    param_2 = (uint)(uVar19 >> 0x20);
    iVar14 = iVar14 + 0x3ac;
    iVar12 = iVar12 + -1;
    param_1 = extraout_ECX;
  } while (iVar12 != 0);
  iVar14 = param_3 + 0x6a8c;
  iVar13 = 4;
  iVar12 = extraout_ECX;
  do {
    uVar19 = FUN_0043ee30(iVar12,param_2,iVar14);
    param_2 = (uint)(uVar19 >> 0x20);
    iVar14 = iVar14 + 0x3ac;
    iVar13 = iVar13 + -1;
    iVar12 = extraout_ECX_00;
  } while (iVar13 != 0);
  iVar14 = param_3 + 0x793c;
  iVar13 = 2;
  do {
    uVar19 = FUN_0043ee30(iVar12,param_2,iVar14);
    param_2 = (uint)(uVar19 >> 0x20);
    iVar14 = iVar14 + 0x3ac;
    iVar13 = iVar13 + -1;
    iVar12 = extraout_ECX_01;
  } while (iVar13 != 0);
  if ((*(byte *)(param_3 + 0x9eb4) & 1) == 0) {
    if (((DAT_00477834 != 0) && (_DAT_00470bdc < *(float *)(DAT_00477834 + 0x3c4))) &&
       (*(float *)(DAT_00477834 + 0x3c0) < (float)_DAT_00470d10)) {
      puVar4 = (undefined2 *)(param_3 + 0x8398);
      iVar14 = 7;
      do {
        *puVar4 = 3;
        puVar4 = puVar4 + 0x1d6;
        iVar14 = iVar14 + -1;
      } while (iVar14 != 0);
      uVar5 = *(uint *)(param_3 + 0x9eb4) | 1;
LAB_00414a56:
      *(uint *)(param_3 + 0x9eb4) = uVar5;
    }
  }
  else if ((DAT_00477834 != 0) &&
          ((*(float *)(DAT_00477834 + 0x3c4) < _DAT_00470d08 ||
           ((float)_DAT_00470d00 < *(float *)(DAT_00477834 + 0x3c0))))) {
    puVar4 = (undefined2 *)(param_3 + 0x8398);
    iVar14 = 7;
    do {
      *puVar4 = 2;
      puVar4 = puVar4 + 0x1d6;
      iVar14 = iVar14 + -1;
    } while (iVar14 != 0);
    uVar5 = *(uint *)(param_3 + 0x9eb4) & 0xfffffffe;
    goto LAB_00414a56;
  }
  iVar14 = DAT_00474c4c;
  iVar12 = 10000;
  FUN_0043ee30(param_3 + 0x8094,param_2,param_3 + 0x8094);
  iVar16 = param_3 + 0x8440;
  iVar13 = 5;
  do {
    iVar6 = iVar14 / iVar12;
    iVar14 = iVar14 % iVar12;
    FUN_0043e5a0(*(int *)(param_3 + 0x9ec8),iVar6 + 0x1e);
    uVar5 = iVar12 / 10 + (iVar12 >> 0x1f);
    iVar12 = uVar5 - (iVar12 >> 0x1f);
    uVar19 = FUN_0043ee30(extraout_ECX_02,uVar5,iVar16);
    iVar16 = iVar16 + 0x3ac;
    iVar13 = iVar13 + -1;
  } while (iVar13 != 0);
  FUN_0043ee30(param_3 + 0x969c,(uint)(uVar19 >> 0x20),param_3 + 0x969c);
  if (((DAT_00477704 == 0) || (iVar14 = *(int *)(DAT_00477704 + 0x10), iVar14 == 0)) ||
     (*(int *)(param_3 + 0x9eb8) != 0)) {
    iVar14 = *(int *)(param_3 + 0x9e24);
    if (iVar14 != 0) {
      for (piVar8 = *(int **)((int)g_pGameStateManager + 0x72dad4); piVar8 != (int *)0x0;
          piVar8 = (int *)piVar8[1]) {
        if (*(int *)*piVar8 == iVar14) goto LAB_004150cf;
      }
      for (piVar8 = *(int **)((int)g_pGameStateManager + 0x72dadc); piVar8 != (int *)0x0;
          piVar8 = (int *)piVar8[1]) {
        if (*(int *)*piVar8 == iVar14) goto LAB_004150cf;
      }
      goto LAB_00415100;
    }
    goto LAB_0041510a;
  }
  iVar12 = *(int *)(iVar14 + 0x23fc);
  *(int *)(param_3 + 0x9e8c) = iVar12;
  fVar2 = (float)iVar12 / (float)*(int *)(iVar14 + 0x2400);
  *(float *)(param_3 + 0x9e88) = fVar2;
  if (*(float *)(param_3 + 0x9e84) < fVar2) {
    *(float *)(param_3 + 0x9e84) = *(float *)(param_3 + 0x9e84) + _DAT_00470cf8;
  }
  if (*(float *)(param_3 + 0x9e88) < *(float *)(param_3 + 0x9e84)) {
    *(undefined4 *)(param_3 + 0x9e84) = *(undefined4 *)(param_3 + 0x9e88);
  }
  pvVar15 = g_pGameStateManager;
  fVar2 = *(float *)(DAT_00477834 + 0x3c4);
  if ((*(byte *)(param_3 + 0x9eb4) & 8) == 0) {
    if ((fVar2 < _DAT_00470bc8 != (fVar2 == _DAT_00470bc8)) &&
       (*(float *)(DAT_00477834 + 0x3c0) < _DAT_00470b5c)) {
      iVar14 = 0;
      if (0 < *(int *)(param_3 + 0x9e90)) {
        piVar8 = (int *)(param_3 + 0x9e28);
LAB_00414cf0:
        iVar12 = *piVar8;
        if (iVar12 != 0) {
          for (piVar7 = *(int **)((int)pvVar15 + 0x72dad4); piVar7 != (int *)0x0;
              piVar7 = (int *)piVar7[1]) {
            if (*(int *)*piVar7 == iVar12) goto LAB_00414d28;
          }
          for (piVar7 = *(int **)((int)pvVar15 + 0x72dadc); piVar7 != (int *)0x0;
              piVar7 = (int *)piVar7[1]) {
            if (*(int *)*piVar7 == iVar12) goto LAB_00414d28;
          }
        }
        goto LAB_00414d60;
      }
LAB_00414d6e:
      iVar14 = *(int *)(param_3 + 0x9e24);
      if (iVar14 != 0) {
        for (piVar8 = *(int **)((int)pvVar15 + 0x72dad4); piVar8 != (int *)0x0;
            piVar8 = (int *)piVar8[1]) {
          if (*(int *)*piVar8 == iVar14) goto LAB_00414daf;
        }
        for (piVar8 = *(int **)((int)pvVar15 + 0x72dadc); piVar8 != (int *)0x0;
            piVar8 = (int *)piVar8[1]) {
          if (*(int *)*piVar8 == iVar14) goto LAB_00414daf;
        }
      }
      goto LAB_00414de0;
    }
  }
  else if ((_DAT_00470c28 <= fVar2) || (_DAT_00470b04 < *(float *)(DAT_00477834 + 0x3c0))) {
    iVar14 = 0;
    if (0 < *(int *)(param_3 + 0x9e90)) {
      piVar8 = (int *)(param_3 + 0x9e28);
LAB_00414ba8:
      iVar12 = *piVar8;
      if (iVar12 != 0) {
        for (piVar7 = *(int **)((int)pvVar15 + 0x72dad4); piVar7 != (int *)0x0;
            piVar7 = (int *)piVar7[1]) {
          if (*(int *)*piVar7 == iVar12) goto LAB_00414be0;
        }
        for (piVar7 = *(int **)((int)pvVar15 + 0x72dadc); piVar7 != (int *)0x0;
            piVar7 = (int *)piVar7[1]) {
          if (*(int *)*piVar7 == iVar12) goto LAB_00414be0;
        }
      }
      goto LAB_00414c10;
    }
LAB_00414c1e:
    iVar14 = *(int *)(param_3 + 0x9e24);
    if (iVar14 != 0) {
      for (piVar8 = *(int **)((int)pvVar15 + 0x72dad4); piVar8 != (int *)0x0;
          piVar8 = (int *)piVar8[1]) {
        if (*(int *)*piVar8 == iVar14) goto LAB_00414c6b;
      }
      piVar8 = *(int **)((int)pvVar15 + 0x72dadc);
      if (piVar8 != (int *)0x0) {
        do {
          if (*(int *)*piVar8 == iVar14) goto LAB_00414c6b;
          piVar8 = (int *)piVar8[1];
        } while (piVar8 != (int *)0x0);
        uVar5 = *(uint *)(param_3 + 0x9eb4) & 0xfffffff7;
        goto LAB_00414de9;
      }
    }
LAB_00414ca0:
    uVar5 = *(uint *)(param_3 + 0x9eb4) & 0xfffffff7;
    goto LAB_00414de9;
  }
  goto LAB_00414def;
LAB_004150cf:
  iVar14 = *piVar8;
  if ((iVar14 != 0) && (*(undefined2 *)(iVar14 + 0x304) = 1, *(int *)(iVar14 + 0x18) == 0)) {
    for (piVar8 = *(int **)(iVar14 + 0x14); piVar8 != (int *)0x0; piVar8 = (int *)piVar8[1]) {
      *(undefined2 *)(*piVar8 + 0x304) = 1;
    }
  }
LAB_00415100:
  *(undefined4 *)(param_3 + 0x9e24) = 0;
LAB_0041510a:
  *(undefined4 *)(param_3 + 0x9e84) = 0;
  *(undefined4 *)(param_3 + 0x9e94) = 0;
  *(undefined4 *)(param_3 + 0x9e9c) = 0;
  *(undefined4 *)(param_3 + 0x9ea4) = 0;
  *(undefined4 *)(param_3 + 0x9eac) = 0;
LAB_0041513c:
  piVar8 = *(int **)(param_3 + 0x9eb8);
  if (piVar8 != (int *)0x0) {
    iVar14 = FUN_00415e90(piVar8);
    pvVar15 = g_pGameStateManager;
    if (iVar14 == 0) {
      pfVar3 = (float *)piVar8[4];
      piVar8[1] = piVar8[2];
      if ((*pfVar3 <= _DAT_00470b68) || (_DAT_00470b64 <= *pfVar3)) {
        piVar8[3] = (int)(*pfVar3 + (float)piVar8[3]);
        uVar19 = FUN_00463b2c();
        piVar8[2] = (int)uVar19;
      }
      else {
        fVar2 = (float)piVar8[3] + _DAT_00470afc;
        piVar8[2] = piVar8[2] + 1;
        piVar8[3] = (int)fVar2;
      }
      goto LAB_0041549a;
    }
    _Memory = *(void **)(param_3 + 0x9eb8);
    if (_Memory != (void *)0x0) {
      iVar14 = *(int *)((int)_Memory + 0x40);
      if (iVar14 != 0) {
        for (piVar8 = *(int **)((int)g_pGameStateManager + 0x72dad4); piVar8 != (int *)0x0;
            piVar8 = (int *)piVar8[1]) {
          if (*(int *)*piVar8 == iVar14) goto LAB_004151f8;
        }
        for (piVar8 = *(int **)((int)g_pGameStateManager + 0x72dadc); piVar8 != (int *)0x0;
            piVar8 = (int *)piVar8[1]) {
          if (*(int *)*piVar8 == iVar14) goto LAB_004151f8;
        }
      }
      goto LAB_0041522f;
    }
    goto LAB_00415490;
  }
  goto LAB_0041549a;
LAB_00414d28:
  iVar12 = *piVar7;
  if ((iVar12 != 0) && (*(undefined2 *)(iVar12 + 0x304) = 3, *(int *)(iVar12 + 0x18) == 0)) {
    for (piVar7 = *(int **)(iVar12 + 0x14); piVar7 != (int *)0x0; piVar7 = (int *)piVar7[1]) {
      *(undefined2 *)(*piVar7 + 0x304) = 3;
    }
  }
LAB_00414d60:
  iVar14 = iVar14 + 1;
  piVar8 = piVar8 + 1;
  if (*(int *)(param_3 + 0x9e90) <= iVar14) goto LAB_00414d6e;
  goto LAB_00414cf0;
LAB_00414daf:
  iVar14 = *piVar8;
  if ((iVar14 != 0) && (*(undefined2 *)(iVar14 + 0x304) = 3, *(int *)(iVar14 + 0x18) == 0)) {
    for (piVar8 = *(int **)(iVar14 + 0x14); piVar8 != (int *)0x0; piVar8 = (int *)piVar8[1]) {
      *(undefined2 *)(*piVar8 + 0x304) = 3;
    }
  }
LAB_00414de0:
  uVar5 = *(uint *)(param_3 + 0x9eb4) | 8;
LAB_00414de9:
  *(uint *)(param_3 + 0x9eb4) = uVar5;
LAB_00414def:
  if (*(int *)(param_3 + 0x9e24) == 0) {
    iVar14 = 0x85;
    switch(DAT_00474c7c) {
    case 1:
      if (0x17 < DAT_00474c84) {
        iVar14 = 0x86;
      }
      break;
    case 2:
      if (DAT_00474c84 < 0x18) goto LAB_00414f33;
      iVar14 = 0x87;
      break;
    case 3:
      if (DAT_00474c84 < 0x18) goto LAB_00414f33;
      iVar14 = 0x88;
      break;
    case 4:
      iVar14 = (0x17 < DAT_00474c84) + 0x89;
      break;
    case 5:
      iVar14 = 0x8b;
      break;
    case 6:
      iVar14 = 0x8c;
      break;
    case 7:
      iVar14 = (0x17 < DAT_00474c84) + 0x8c;
    }
    puVar9 = FUN_00449950();
    puVar9[0xd7] = puVar9[0xd7] | 0x40000000;
    puVar9[8] = 0xf;
    FUN_00449870(puVar9,iVar14);
    pvVar15 = g_pGameStateManager;
    puVar1 = puVar9 + 1;
    *puVar1 = puVar9;
    puVar9[2] = 0;
    puVar9[3] = 0;
    if (*(int *)((int)pvVar15 + 0x72dad4) == 0) {
      *(undefined4 **)((int)pvVar15 + 0x72dad4) = puVar1;
    }
    else {
      iVar14 = *(int *)((int)pvVar15 + 0x72dad8);
      if (*(int *)(iVar14 + 4) != 0) {
        puVar9[2] = *(int *)(iVar14 + 4);
        *(undefined4 **)(*(int *)(iVar14 + 4) + 8) = puVar1;
      }
      *(undefined4 **)(iVar14 + 4) = puVar1;
      puVar9[3] = iVar14;
    }
    *(undefined4 **)((int)pvVar15 + 0x72dad8) = puVar1;
    iVar14 = *(int *)((int)pvVar15 + 0x732454);
    iVar12 = iVar14 + 1;
    *(int *)((int)pvVar15 + 0x732454) = iVar12;
    if (iVar12 == 0) {
      *(int *)((int)pvVar15 + 0x732454) = iVar14 + 2;
    }
    *puVar9 = *(undefined4 *)((int)pvVar15 + 0x732454);
    *(undefined4 *)(param_3 + 0x9e24) = *(undefined4 *)((int)pvVar15 + 0x732454);
  }
LAB_00414f33:
  piVar8 = (int *)(param_3 + 0x9e28);
  uVar5 = 0;
LAB_00414f40:
  if (*(int *)(param_3 + 0x9e90) <= (int)uVar5) {
    iVar14 = *piVar8;
    if (iVar14 == 0) goto LAB_00415076;
    for (piVar7 = *(int **)((int)pvVar15 + 0x72dad4); piVar7 != (int *)0x0;
        piVar7 = (int *)piVar7[1]) {
      if (*(int *)*piVar7 == iVar14) goto LAB_00415038;
    }
    for (piVar7 = *(int **)((int)pvVar15 + 0x72dadc); piVar7 != (int *)0x0;
        piVar7 = (int *)piVar7[1]) {
      if (*(int *)*piVar7 == iVar14) goto LAB_00415038;
    }
    goto LAB_00415070;
  }
  if (*piVar8 == 0) {
    puVar9 = FUN_00449950();
    puVar9[0xd7] = puVar9[0xd7] | 0x40000000;
    puVar9[8] = 0xf;
    FUN_00449870(puVar9,uVar5 + 0x5b);
    pvVar15 = g_pGameStateManager;
    puVar1 = puVar9 + 1;
    *puVar1 = puVar9;
    puVar9[2] = 0;
    puVar9[3] = 0;
    if (*(int *)((int)pvVar15 + 0x72dad4) == 0) {
      *(undefined4 **)((int)pvVar15 + 0x72dad4) = puVar1;
    }
    else {
      iVar14 = *(int *)((int)pvVar15 + 0x72dad8);
      if (*(int *)(iVar14 + 4) != 0) {
        puVar9[2] = *(int *)(iVar14 + 4);
        *(undefined4 **)(*(int *)(iVar14 + 4) + 8) = puVar1;
      }
      *(undefined4 **)(iVar14 + 4) = puVar1;
      puVar9[3] = iVar14;
    }
    *(undefined4 **)((int)pvVar15 + 0x72dad8) = puVar1;
    iVar14 = *(int *)((int)pvVar15 + 0x732454);
    iVar12 = iVar14 + 1;
    *(int *)((int)pvVar15 + 0x732454) = iVar12;
    if (iVar12 == 0) {
      *(int *)((int)pvVar15 + 0x732454) = iVar14 + 2;
    }
    *puVar9 = *(undefined4 *)((int)pvVar15 + 0x732454);
    *piVar8 = *(int *)((int)pvVar15 + 0x732454);
  }
  goto LAB_00415076;
LAB_00414be0:
  iVar12 = *piVar7;
  if ((iVar12 != 0) && (*(undefined2 *)(iVar12 + 0x304) = 2, *(int *)(iVar12 + 0x18) == 0)) {
    for (piVar7 = *(int **)(iVar12 + 0x14); piVar7 != (int *)0x0; piVar7 = (int *)piVar7[1]) {
      *(undefined2 *)(*piVar7 + 0x304) = 2;
    }
  }
LAB_00414c10:
  iVar14 = iVar14 + 1;
  piVar8 = piVar8 + 1;
  if (*(int *)(param_3 + 0x9e90) <= iVar14) goto LAB_00414c1e;
  goto LAB_00414ba8;
LAB_00414c6b:
  iVar14 = *piVar8;
  if ((iVar14 != 0) && (*(undefined2 *)(iVar14 + 0x304) = 2, *(int *)(iVar14 + 0x18) == 0)) {
    for (piVar8 = *(int **)(iVar14 + 0x14); piVar8 != (int *)0x0; piVar8 = (int *)piVar8[1]) {
      *(undefined2 *)(*piVar8 + 0x304) = 2;
    }
  }
  goto LAB_00414ca0;
LAB_00415038:
  iVar14 = *piVar7;
  if ((iVar14 != 0) && (*(undefined2 *)(iVar14 + 0x304) = 1, *(int *)(iVar14 + 0x18) == 0)) {
    for (piVar7 = *(int **)(iVar14 + 0x14); piVar7 != (int *)0x0; piVar7 = (int *)piVar7[1]) {
      *(undefined2 *)(*piVar7 + 0x304) = 1;
    }
  }
LAB_00415070:
  *piVar8 = 0;
LAB_00415076:
  uVar5 = uVar5 + 1;
  piVar8 = piVar8 + 1;
  if (9 < uVar5) goto LAB_0041513c;
  goto LAB_00414f40;
LAB_00415270:
  iVar14 = *piVar8;
  if ((iVar14 != 0) &&
     (*(uint *)(iVar14 + 0x35c) = *(uint *)(iVar14 + 0x35c) | 0x4000000,
     *(int *)(iVar14 + 0x18) == 0)) {
    for (piVar8 = *(int **)(iVar14 + 0x14); piVar8 != (int *)0x0; piVar8 = (int *)piVar8[1]) {
      *(uint *)(*piVar8 + 0x35c) = *(uint *)(*piVar8 + 0x35c) | 0x4000000;
    }
  }
  goto LAB_004152a1;
LAB_004152e8:
  iVar14 = *piVar8;
  if ((iVar14 != 0) &&
     (*(uint *)(iVar14 + 0x35c) = *(uint *)(iVar14 + 0x35c) | 0x4000000,
     *(int *)(iVar14 + 0x18) == 0)) {
    for (piVar8 = *(int **)(iVar14 + 0x14); piVar8 != (int *)0x0; piVar8 = (int *)piVar8[1]) {
      *(uint *)(*piVar8 + 0x35c) = *(uint *)(*piVar8 + 0x35c) | 0x4000000;
    }
  }
  goto LAB_0041531f;
LAB_00415360:
  iVar14 = *piVar8;
  if ((iVar14 != 0) &&
     (*(uint *)(iVar14 + 0x35c) = *(uint *)(iVar14 + 0x35c) | 0x4000000,
     *(int *)(iVar14 + 0x18) == 0)) {
    for (piVar8 = *(int **)(iVar14 + 0x14); piVar8 != (int *)0x0; piVar8 = (int *)piVar8[1]) {
      *(uint *)(*piVar8 + 0x35c) = *(uint *)(*piVar8 + 0x35c) | 0x4000000;
    }
  }
  goto LAB_00415391;
LAB_004153d8:
  iVar14 = *piVar8;
  if ((iVar14 != 0) &&
     (*(uint *)(iVar14 + 0x35c) = *(uint *)(iVar14 + 0x35c) | 0x4000000,
     *(int *)(iVar14 + 0x18) == 0)) {
    for (piVar8 = *(int **)(iVar14 + 0x14); piVar8 != (int *)0x0; piVar8 = (int *)piVar8[1]) {
      *(uint *)(*piVar8 + 0x35c) = *(uint *)(*piVar8 + 0x35c) | 0x4000000;
    }
  }
  goto LAB_0041540f;
LAB_0041544f:
  iVar14 = *piVar8;
  if ((iVar14 != 0) &&
     (*(uint *)(iVar14 + 0x35c) = *(uint *)(iVar14 + 0x35c) | 0x4000000,
     *(int *)(iVar14 + 0x18) == 0)) {
    for (piVar8 = *(int **)(iVar14 + 0x14); piVar8 != (int *)0x0; piVar8 = (int *)piVar8[1]) {
      *(uint *)(*piVar8 + 0x35c) = *(uint *)(*piVar8 + 0x35c) | 0x4000000;
    }
  }
  goto LAB_00415480;
LAB_004151f8:
  iVar14 = *piVar8;
  if ((iVar14 != 0) &&
     (*(uint *)(iVar14 + 0x35c) = *(uint *)(iVar14 + 0x35c) | 0x4000000,
     *(int *)(iVar14 + 0x18) == 0)) {
    for (piVar8 = *(int **)(iVar14 + 0x14); piVar8 != (int *)0x0; piVar8 = (int *)piVar8[1]) {
      *(uint *)(*piVar8 + 0x35c) = *(uint *)(*piVar8 + 0x35c) | 0x4000000;
    }
  }
LAB_0041522f:
  *(undefined4 *)((int)_Memory + 0x40) = 0;
  iVar14 = *(int *)((int)_Memory + 0x44);
  if (iVar14 != 0) {
    for (piVar8 = *(int **)((int)pvVar15 + 0x72dad4); piVar8 != (int *)0x0;
        piVar8 = (int *)piVar8[1]) {
      if (*(int *)*piVar8 == iVar14) goto LAB_00415270;
    }
    for (piVar8 = *(int **)((int)pvVar15 + 0x72dadc); piVar8 != (int *)0x0;
        piVar8 = (int *)piVar8[1]) {
      if (*(int *)*piVar8 == iVar14) goto LAB_00415270;
    }
  }
LAB_004152a1:
  *(undefined4 *)((int)_Memory + 0x44) = 0;
  iVar14 = *(int *)((int)_Memory + 0x48);
  if (iVar14 != 0) {
    for (piVar8 = *(int **)((int)pvVar15 + 0x72dad4); piVar8 != (int *)0x0;
        piVar8 = (int *)piVar8[1]) {
      if (*(int *)*piVar8 == iVar14) goto LAB_004152e8;
    }
    for (piVar8 = *(int **)((int)pvVar15 + 0x72dadc); piVar8 != (int *)0x0;
        piVar8 = (int *)piVar8[1]) {
      if (*(int *)*piVar8 == iVar14) goto LAB_004152e8;
    }
  }
LAB_0041531f:
  *(undefined4 *)((int)_Memory + 0x48) = 0;
  iVar14 = *(int *)((int)_Memory + 0x4c);
  if (iVar14 != 0) {
    for (piVar8 = *(int **)((int)pvVar15 + 0x72dad4); piVar8 != (int *)0x0;
        piVar8 = (int *)piVar8[1]) {
      if (*(int *)*piVar8 == iVar14) goto LAB_00415360;
    }
    for (piVar8 = *(int **)((int)pvVar15 + 0x72dadc); piVar8 != (int *)0x0;
        piVar8 = (int *)piVar8[1]) {
      if (*(int *)*piVar8 == iVar14) goto LAB_00415360;
    }
  }
LAB_00415391:
  *(undefined4 *)((int)_Memory + 0x4c) = 0;
  iVar14 = *(int *)((int)_Memory + 0x50);
  if (iVar14 != 0) {
    for (piVar8 = *(int **)((int)pvVar15 + 0x72dad4); piVar8 != (int *)0x0;
        piVar8 = (int *)piVar8[1]) {
      if (*(int *)*piVar8 == iVar14) goto LAB_004153d8;
    }
    for (piVar8 = *(int **)((int)pvVar15 + 0x72dadc); piVar8 != (int *)0x0;
        piVar8 = (int *)piVar8[1]) {
      if (*(int *)*piVar8 == iVar14) goto LAB_004153d8;
    }
  }
LAB_0041540f:
  *(undefined4 *)((int)_Memory + 0x50) = 0;
  iVar14 = *(int *)((int)_Memory + 0x54);
  if (iVar14 != 0) {
    for (piVar8 = *(int **)((int)pvVar15 + 0x72dad4); piVar8 != (int *)0x0;
        piVar8 = (int *)piVar8[1]) {
      if (*(int *)*piVar8 == iVar14) goto LAB_0041544f;
    }
    for (piVar8 = *(int **)((int)pvVar15 + 0x72dadc); piVar8 != (int *)0x0;
        piVar8 = (int *)piVar8[1]) {
      if (*(int *)*piVar8 == iVar14) goto LAB_0041544f;
    }
  }
LAB_00415480:
  *(undefined4 *)((int)_Memory + 0x54) = 0;
  _free(_Memory);
LAB_00415490:
  *(undefined4 *)(param_3 + 0x9eb8) = 0;
LAB_0041549a:
  if (DAT_00477704 == 0) goto LAB_00415764;
  iVar14 = *(int *)(param_3 + 0x9ec0);
  iVar12 = DAT_00477704;
  if (((-1 < iVar14) && (*(int *)(DAT_00477704 + 0x10) != 0)) && (*(int *)(param_3 + 0x9eb8) == 0))
  {
    if (iVar14 < *(int *)(param_3 + 0x9ec4)) {
      if (iVar14 < 6) {
        *(undefined2 *)(param_3 + 0x7c40) = 9;
        *(undefined2 *)(param_3 + 0x7fec) = 9;
        FUN_0043dc90(&DAT_00492590,0);
      }
      else if (iVar14 < 0xb) {
        *(undefined2 *)(param_3 + 0x7c40) = 8;
        *(undefined2 *)(param_3 + 0x7fec) = 8;
        FUN_0043dc90(&DAT_00492590,0);
      }
    }
    else if (*(int *)(param_3 + 0x9ec4) < iVar14) {
      *(undefined2 *)(param_3 + 0x7c40) = 7;
      *(undefined2 *)(param_3 + 0x7fec) = 7;
    }
    if (*(int *)(param_3 + 0x9ec0) != *(int *)(param_3 + 0x9ec4)) {
      FUN_0043e5a0(*(int *)(param_3 + 0x9ec8),*(int *)(param_3 + 0x9ec0) / 10 + 8);
      FUN_0043e5a0(*(int *)(param_3 + 0x9ec8),*(int *)(param_3 + 0x9ec0) % 10 + 8);
    }
    iVar12 = DAT_00477704;
    *(undefined4 *)(param_3 + 0x9ec4) = *(undefined4 *)(param_3 + 0x9ec0);
  }
  uVar5 = DAT_004776f4;
  iVar14 = *(int *)(iVar12 + 0x10);
  if (((iVar14 == 0) || ((~(*(uint *)(iVar14 + 0x2480) >> 4) & 1) == 0)) ||
     ((~*(uint *)(iVar14 + 0x2480) & 1) == 0)) goto LAB_00415764;
  uVar10 = *(uint *)(param_3 + 0x9eb4);
  if ((*(byte *)(DAT_004776f4 + 0x378c) & 1) == 0) {
    uVar11 = uVar10 >> 1 & 3;
    if (uVar11 == 0) {
      bVar17 = SBORROW4(*(int *)(iVar14 + 0x2404),700);
      iVar12 = *(int *)(iVar14 + 0x2404) + -700;
      goto LAB_00415657;
    }
    if (uVar11 == 1) {
      bVar17 = SBORROW4(*(int *)(iVar14 + 0x2404),400);
      iVar12 = *(int *)(iVar14 + 0x2404) + -400;
      goto LAB_00415679;
    }
    if (uVar11 != 2) {
      if (uVar11 == 3) {
        iVar12 = *(int *)(iVar14 + 0x2404);
        bVar18 = SBORROW4(iVar12,200);
        iVar13 = iVar12 + -200;
        bVar17 = iVar12 == 200;
        goto LAB_004156ba;
      }
      goto LAB_004156ce;
    }
    bVar17 = SBORROW4(*(int *)(iVar14 + 0x2404),200);
    iVar12 = *(int *)(iVar14 + 0x2404) + -200;
LAB_0041569b:
    if (bVar17 == iVar12 < 0) goto LAB_004156ce;
    *(undefined2 *)(param_3 + 0x9d4c) = 9;
    uVar10 = uVar10 | 6;
LAB_004156c8:
    *(uint *)(param_3 + 0x9eb4) = uVar10;
  }
  else {
    uVar11 = uVar10 >> 1 & 3;
    if (uVar11 == 0) {
      bVar17 = SBORROW4(*(int *)(iVar14 + 0x2404),2000);
      iVar12 = *(int *)(iVar14 + 0x2404) + -2000;
LAB_00415657:
      if (bVar17 != iVar12 < 0) {
        *(undefined2 *)(param_3 + 0x9d4c) = 7;
        uVar10 = uVar10 & 0xfffffffb | 2;
        goto LAB_004156c8;
      }
    }
    else if (uVar11 == 1) {
      bVar17 = SBORROW4(*(int *)(iVar14 + 0x2404),1000);
      iVar12 = *(int *)(iVar14 + 0x2404) + -1000;
LAB_00415679:
      if (bVar17 != iVar12 < 0) {
        *(undefined2 *)(param_3 + 0x9d4c) = 8;
        uVar10 = uVar10 & 0xfffffffd | 4;
        goto LAB_004156c8;
      }
    }
    else {
      if (uVar11 == 2) {
        bVar17 = SBORROW4(*(int *)(iVar14 + 0x2404),400);
        iVar12 = *(int *)(iVar14 + 0x2404) + -400;
        goto LAB_0041569b;
      }
      if (uVar11 == 3) {
        iVar12 = *(int *)(iVar14 + 0x2404);
        bVar18 = SBORROW4(iVar12,400);
        iVar13 = iVar12 + -400;
        bVar17 = iVar12 == 400;
LAB_004156ba:
        if (!bVar17 && bVar18 == iVar13 < 0) {
          *(undefined2 *)(param_3 + 0x9d4c) = 10;
          uVar10 = uVar10 & 0xfffffff9;
          goto LAB_004156c8;
        }
      }
    }
  }
LAB_004156ce:
  FUN_0043ee30(uVar11,uVar5,param_3 + 0x9a48);
  iVar12 = DAT_00477834;
  fVar2 = *(float *)(iVar14 + 0x1068) + _DAT_00470b4c;
  *(undefined4 *)(param_3 + 0x9d8c) = 0x43f00000;
  *(float *)(param_3 + 0x9d88) = fVar2;
  if (ABS(*(float *)(iVar14 + 0x1068) - *(float *)(iVar12 + 0x3c0)) < (float)_DAT_00470cf0) {
    uVar19 = FUN_00463b2c();
    *(char *)(param_3 + 0x9d47) = '@' - (char)uVar19;
  }
  else {
    *(undefined1 *)(param_3 + 0x9d47) = 0xff;
  }
  if ((*(float *)(iVar14 + 0x1068) < _DAT_00470b40) || (_DAT_00470b3c < *(float *)(iVar14 + 0x1068))
     ) {
    *(undefined1 *)(param_3 + 0x9d47) = 0;
  }
LAB_00415764:
  pfVar3 = *(float **)(param_3 + 0x9e6c);
  *(int *)(param_3 + 0x9e60) = *(int *)(param_3 + 0x9e64);
  if ((_DAT_00470b68 < *pfVar3) && (*pfVar3 < _DAT_00470b64)) {
    iVar14 = *(int *)(param_3 + 0x9e64) + 1;
    fVar2 = *(float *)(param_3 + 0x9e68) + _DAT_00470afc;
    *(int *)(param_3 + 0x9e64) = iVar14;
    *(float *)(param_3 + 0x9e68) = fVar2;
    return CONCAT44(iVar14,1);
  }
  *(float *)(param_3 + 0x9e68) = *pfVar3 + *(float *)(param_3 + 0x9e68);
  uVar19 = FUN_00463b2c();
  *(int *)(param_3 + 0x9e64) = (int)uVar19;
  return CONCAT44((int)(uVar19 >> 0x20),1);
}

