/* Raw Ghidra reference; not compilable reconstruction. Address: 00417870 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_00417870(int param_1)

{
  undefined4 *puVar1;
  uint *puVar2;
  void *pvVar3;
  int iVar4;
  void *extraout_ECX;
  void *extraout_ECX_00;
  void *extraout_ECX_01;
  void *extraout_ECX_02;
  void *extraout_ECX_03;
  void *extraout_ECX_04;
  void *extraout_ECX_05;
  void *extraout_ECX_06;
  void *extraout_ECX_07;
  void *extraout_ECX_08;
  void *extraout_ECX_09;
  void *pvVar5;
  void *extraout_ECX_10;
  void *extraout_ECX_11;
  void *extraout_ECX_12;
  void *extraout_ECX_13;
  void *extraout_ECX_14;
  void *extraout_ECX_15;
  int iVar6;
  int iVar7;
  undefined4 *puVar8;
  undefined4 *puVar9;
  
  *(uint *)(param_1 + 0x58) = *(uint *)(param_1 + 0x58) | 4;
  while ((iVar4 = DAT_0047783c, pvVar5 = *(void **)g_pGameStateManager, -1 < (int)pvVar5 ||
         (-1 < *(int *)((int)g_pGameStateManager + 4)))) {
    if (((byte)DAT_00491ff4 & 0x80) != 0) goto LAB_00417b3e;
    Sleep(1);
  }
  DAT_00476f78 = 0x3f800000;
  DAT_00474c88 = 0;
  DAT_00474c8c = 0;
  if (DAT_00491fc4 == 0) {
    if (DAT_00474c40 < DAT_00474c44) {
      DAT_00474c40 = DAT_00474c44;
    }
  }
  else {
    if (DAT_00474c7c == 7) {
      DAT_00474c74 = 4;
    }
    iVar6 = (DAT_00474c6c + DAT_00474c68 * 3) * 0x437c + DAT_0047783c;
    DAT_00474c40 = *(int *)(DAT_00474c74 * 0xf0 + 0x18 + iVar6);
    DAT_00474c94 = (int)*(char *)(DAT_00474c74 * 0xf0 + iVar6 + 0x1d);
    if ((_DAT_00474ca0 & 8) == 0) {
      DAT_00474c90 = 0;
    }
    DAT_00474c44 = 0;
    FUN_00418b80(&DAT_00474c40,50000);
    if ((_DAT_00474ca0 & 0x10) == 0) {
      DAT_00474c70 = 2;
    }
    else if (DAT_00474cac == 0) {
      DAT_00474c70 = 9;
    }
    else {
      DAT_00474c70 = DAT_00474cac + -1;
    }
    DAT_00474c48 = -(ushort)(DAT_00474c7c != 1) & 0x50;
    _DAT_00474ca0 = _DAT_00474ca0 & 0xfffffffb;
    if (*(int *)(param_1 + 0x5c) == 0) {
      iVar7 = (DAT_00474c6c + DAT_00474c68 * 3) * 0x437c;
      iVar6 = *(int *)(iVar7 + 0x4c8 + iVar4);
      if (iVar6 < 99999) {
        *(int *)(iVar7 + 0x4c8 + iVar4) = iVar6 + 1;
      }
    }
    DAT_00474c9c = 0;
    DAT_00474c98 = -(uint)((_DAT_00474ca0 & 8) != 0) & 0xfffffe00;
  }
  _DAT_00474c50 = 9;
  iVar6 = FUN_00449ed0(FUN_004187c0);
  iVar4 = DAT_00491be4;
  *(int *)(iVar6 + 0x20) = param_1;
  *(uint *)(iVar6 + 4) = *(uint *)(iVar6 + 4) & 0xfffffffd;
  FUN_00449ae0(iVar4);
  *(int *)(param_1 + 8) = iVar6;
  iVar6 = FUN_00449ed0(FUN_004187d0);
  *(uint *)(iVar6 + 4) = *(uint *)(iVar6 + 4) & 0xfffffffd;
  iVar4 = DAT_00491be4;
  *(int *)(iVar6 + 0x20) = param_1;
  FUN_00449b70(iVar4);
  puVar1 = DAT_00477848;
  *(int *)(param_1 + 0xc) = iVar6;
  puVar8 = &DAT_00491d48;
  puVar9 = (undefined4 *)(param_1 + 0x24);
  for (iVar4 = 0xd; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar9 = *puVar8;
    puVar8 = puVar8 + 1;
    puVar9 = puVar9 + 1;
  }
  *(undefined4 *)(param_1 + 4) = *puVar1;
  if ((_DAT_00474ca0 & 2) == 0) {
    puVar1 = FUN_00429610(*(undefined4 *)(param_1 + 0x5c),&DAT_00477710);
    pvVar5 = extraout_ECX;
    if ((((puVar1 == (undefined4 *)0x0) ||
         (puVar2 = CreateGameState((void *)DAT_00477848[1],0), pvVar5 = extraout_ECX_00,
         puVar2 == (uint *)0x0)) ||
        (puVar2 = FUN_00414830(), pvVar5 = extraout_ECX_01, puVar2 == (uint *)0x0)) ||
       ((((pvVar3 = FUN_00425020(), pvVar5 = extraout_ECX_02, pvVar3 == (void *)0x0 ||
          (puVar1 = FUN_00406060(), pvVar5 = extraout_ECX_03, puVar1 == (undefined4 *)0x0)) ||
         ((puVar2 = FUN_0041aed0(), pvVar5 = extraout_ECX_04, puVar2 == (uint *)0x0 ||
          ((puVar1 = FUN_0041c290(), pvVar5 = extraout_ECX_05, puVar1 == (undefined4 *)0x0 ||
           (puVar2 = FUN_00422360(), pvVar5 = extraout_ECX_06, puVar2 == (uint *)0x0)))))) ||
        (puVar2 = FUN_00419090(), pvVar5 = extraout_ECX_07, puVar2 == (uint *)0x0))))
    goto LAB_00417b3e;
    puVar2 = FUN_0042b660();
    pvVar5 = extraout_ECX_08;
  }
  else {
    FUN_0042a6a0();
    FUN_00413a20(DAT_0047770c);
    puVar2 = CreateGameState((void *)DAT_00477848[1],0);
    pvVar5 = extraout_ECX_09;
  }
  if (puVar2 != (uint *)0x0) {
    if ((_DAT_00474ca0 & 9) == 0) {
      puVar2 = FUN_0040d6b0(DAT_00477848[3]);
      pvVar5 = extraout_ECX_10;
      if (puVar2 == (uint *)0x0) goto LAB_00417b3e;
    }
    else {
      ResetPathState();
    }
    puVar2 = FUN_0040af90();
    pvVar5 = extraout_ECX_11;
    if (((puVar2 != (uint *)0x0) &&
        (puVar2 = FUN_004056b0(), pvVar5 = extraout_ECX_12, puVar2 != (uint *)0x0)) &&
       (puVar2 = FUN_00408c90(), pvVar5 = extraout_ECX_13, puVar2 != (uint *)0x0)) {
      if ((_DAT_00474ca0 & 0x20) == 0) {
        FUN_00420c00(extraout_ECX_13);
        FUN_00420a90(0,(char *)DAT_00477848[4]);
        FUN_00420a90(1,(char *)DAT_00477848[5]);
      }
      iVar4 = DAT_00477708;
      *(undefined8 *)(DAT_00477708 + 0x2c) = _DAT_00470b70;
      *(undefined8 *)(iVar4 + 0x24) = _DAT_00470b70;
      FUN_00405410(0);
      pvVar5 = extraout_ECX_14;
      while (DAT_00494518 != 0) {
        Sleep(0x10);
        pvVar5 = extraout_ECX_15;
      }
      if (DAT_00474c84 != 0) {
        DAT_00474c8c = 0;
      }
      DAT_00474c84 = 0;
      FUN_00421070(pvVar5,0x491c28);
      *(uint *)(param_1 + 0x58) = *(uint *)(param_1 + 0x58) & 0xfffffffb;
      _DAT_00474ca0 = _DAT_00474ca0 & 0xfffffff4;
      _DAT_00492264 = 0;
      _DAT_00492260 = 1;
      DAT_004918a4 = 0;
      FUN_00409e20();
      return 0;
    }
  }
LAB_00417b3e:
  *(uint *)(param_1 + 0x58) = *(uint *)(param_1 + 0x58) | 8;
  FUN_00421300(pvVar5,0x491c28);
  _DAT_00492264 = 0;
  _DAT_00492260 = 1;
  if (*(int *)(param_1 + 8) != 0) {
    puVar2 = (uint *)(*(int *)(param_1 + 8) + 4);
    *puVar2 = *puVar2 | 2;
  }
  if (*(int *)(param_1 + 0xc) != 0) {
    puVar2 = (uint *)(*(int *)(param_1 + 0xc) + 4);
    *puVar2 = *puVar2 | 2;
  }
  return 0xffffffff;
}

