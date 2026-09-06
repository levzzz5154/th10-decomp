/* Raw Ghidra reference; not compilable reconstruction. Address: 00431EE0 */

/* WARNING: Removing unreachable block (ram,0x00431f13) */
/* WARNING: Removing unreachable block (ram,0x00431f20) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __thiscall FUN_00431ee0(void *this,int param_1)

{
  byte bVar1;
  void *pvVar2;
  undefined4 *puVar3;
  int iVar4;
  undefined4 *puVar5;
  int iVar6;
  int *piVar7;
  byte bVar8;
  undefined4 extraout_ECX;
  undefined4 extraout_ECX_00;
  undefined4 extraout_ECX_01;
  undefined4 extraout_ECX_02;
  undefined4 extraout_ECX_03;
  int extraout_ECX_04;
  undefined4 extraout_ECX_05;
  undefined4 uVar9;
  undefined4 extraout_ECX_06;
  undefined4 extraout_ECX_07;
  undefined4 extraout_ECX_08;
  undefined4 extraout_ECX_09;
  undefined4 extraout_ECX_10;
  undefined4 extraout_ECX_11;
  undefined4 extraout_ECX_12;
  undefined4 extraout_ECX_13;
  undefined4 extraout_ECX_14;
  undefined4 extraout_ECX_15;
  undefined4 extraout_ECX_16;
  undefined4 extraout_ECX_17;
  undefined4 extraout_ECX_18;
  int *piVar10;
  
  switch(*(undefined4 *)(param_1 + 0x20)) {
  case 0:
    *(undefined4 *)(param_1 + 0x2c) = 6;
    *(undefined4 *)(param_1 + 0x24) = 0;
    *(undefined4 *)(param_1 + 0x104) = 5;
    iVar4 = *(int *)(param_1 + 0x104);
    if (iVar4 == 0) {
      *(undefined4 *)(param_1 + 0xfc) = 1;
    }
    else if (iVar4 < 2) {
      *(int *)(param_1 + 0xfc) = iVar4 + -1;
    }
    else {
      *(undefined4 *)(param_1 + 0xfc) = 1;
    }
    *(undefined4 *)(param_1 + 0x1cc) = 1;
    iVar4 = FUN_004088c0(this,*(int *)(param_1 + 0xfc));
    iVar6 = (iVar4 + 9) / 10;
    iVar4 = iVar6 + 1;
    *(int *)(param_1 + 0x1dc) = iVar4;
    if (iVar4 == 0) {
      *(undefined4 *)(param_1 + 0x1d4) = 0;
    }
    else if (iVar4 < 1) {
      *(int *)(param_1 + 0x1d4) = iVar6;
    }
    else {
      *(undefined4 *)(param_1 + 0x1d4) = 0;
    }
    *(undefined4 *)(param_1 + 0x2a4) = 1;
    iVar4 = FUN_004491c0(iVar4,(int)g_pGameStateManager,*(int *)(param_1 + 0x43c));
    if (iVar4 == 0) {
      FUN_0042c670(param_1);
      puVar3 = (undefined4 *)FUN_00448d00(*(undefined4 *)((int)g_pGameThread + 0x8994),8,0xf);
      *(undefined4 *)(param_1 + 0x5d0) = *puVar3;
    }
    FUN_0042c670(param_1);
    FUN_0042c620(1);
    FUN_0042c670(param_1);
    FUN_0042c670(param_1);
    FUN_0042c670(param_1);
    FUN_0042c670(param_1);
    FUN_0042c670(param_1);
    FUN_0042c670(param_1);
    FUN_0042c670(param_1);
    FUN_0042c670(param_1);
    FUN_0042c670(param_1);
    FUN_0042c670(param_1);
    FUN_0042c670(param_1);
  case 1:
    if (6 < *(int *)(param_1 + 0x2b4)) {
      FUN_0042c620(2);
      return 1;
    }
    break;
  case 2:
    *(undefined4 *)(param_1 + 0x28) = *(undefined4 *)(param_1 + 0x24);
    *(undefined4 *)(param_1 + 0x100) = *(undefined4 *)(param_1 + 0xfc);
    *(undefined4 *)(param_1 + 0x1d8) = *(undefined4 *)(param_1 + 0x1d4);
    if (((_DAT_00474e36 & 0x10) != 0) || ((DAT_00474e34 & 0x10) != 0)) {
      FUN_0044bea0(-1);
      FUN_00449250(*(undefined4 *)(param_1 + 0x56c),(int)g_pGameStateManager,
                   *(undefined4 *)(param_1 + 0x56c));
    }
    if (((_DAT_00474e36 & 0x20) != 0) || ((DAT_00474e34 & 0x20) != 0)) {
      FUN_0044bea0(1);
      FUN_00449250(extraout_ECX,(int)g_pGameStateManager,*(int *)(param_1 + 0x570));
    }
    if (*(int *)(param_1 + 0x100) != *(int *)(param_1 + 0xfc)) {
      FUN_0043dc90(&DAT_00492590,0);
      FUN_0042c6d0(extraout_ECX_00);
      FUN_0042c670(param_1);
      uVar9 = extraout_ECX_01;
      if (0 < *(int *)(param_1 + 0x1d4)) {
        iVar4 = *(int *)(param_1 + 0x1dc);
        if (iVar4 == 0) {
          *(undefined4 *)(param_1 + 0x1d4) = 1;
        }
        else if (iVar4 < 2) {
          *(int *)(param_1 + 0x1d4) = iVar4 + -1;
        }
        else {
          *(undefined4 *)(param_1 + 0x1d4) = 1;
        }
        FUN_00432690(param_1);
        uVar9 = extraout_ECX_02;
      }
      iVar4 = FUN_004088c0(uVar9,*(int *)(param_1 + 0xfc));
      *(int *)(param_1 + 0x1dc) = (iVar4 + 9) / 10 + 1;
    }
    if (((_DAT_00474e36 & 0x40) != 0) || ((DAT_00474e34 & 0x40) != 0)) {
      FUN_0044bea0(-1);
      FUN_00449250(extraout_ECX_03,(int)g_pGameStateManager,*(int *)(param_1 + 0x564));
    }
    if ((DAT_00474e36 < '\0') || ((char)DAT_00474e34 < '\0')) {
      FUN_0044bea0(1);
      FUN_00449250(*(undefined4 *)(param_1 + 0x568),(int)g_pGameStateManager,
                   *(undefined4 *)(param_1 + 0x568));
    }
    if (*(int *)(param_1 + 0x28) != *(int *)(param_1 + 0x24)) {
      FUN_0043dc90(&DAT_00492590,0);
      iVar4 = *(int *)(param_1 + 0x28) / 3;
      if (*(int *)(param_1 + 0x24) / 3 != iVar4) {
        FUN_0042c6d0(iVar4);
        FUN_0042c670(param_1);
        iVar4 = extraout_ECX_04;
      }
      FUN_0042c6d0(iVar4);
      FUN_0042c670(param_1);
      if (0 < *(int *)(param_1 + 0x1d4)) {
        FUN_00432690(param_1);
      }
    }
    if ((_DAT_00474e36 & 0x1001) != 0) {
      if (*(int *)(param_1 + 0x1d4) == 0) {
        iVar4 = 0;
        puVar3 = (undefined4 *)(param_1 + 0x5d4);
        do {
          puVar5 = (undefined4 *)
                   FUN_00448d00(*(undefined4 *)((int)g_pGameThread + 0x899c),iVar4 + 0x17,0xf);
          *puVar3 = *puVar5;
          iVar4 = iVar4 + 1;
          puVar3 = puVar3 + 1;
        } while (iVar4 < 10);
      }
      FUN_0044bea0(1);
      if (*(int *)(param_1 + 0x1d4) == 0) {
        iVar4 = 10;
        uVar9 = extraout_ECX_05;
        do {
          FUN_00409e50(uVar9);
          iVar4 = iVar4 + -1;
          uVar9 = extraout_ECX_06;
        } while (iVar4 != 0);
      }
      else {
        FUN_00432690(param_1);
      }
      FUN_0043dc90(&DAT_00492590,0);
    }
    if ((*(int *)(param_1 + 0xfc) == 4) && (*(int *)(param_1 + 0x24) == 2)) {
      if ((_DAT_00474e36 & 0x160b) != 0) {
        DAT_004979a4 = 0;
        DAT_004979a0 = 0;
      }
      puVar3 = &DAT_00497e90;
      puVar5 = &DAT_00497d90;
      for (iVar4 = 0x40; iVar4 != 0; iVar4 = iVar4 + -1) {
        *puVar5 = *puVar3;
        puVar3 = puVar3 + 1;
        puVar5 = puVar5 + 1;
      }
      iVar4 = FUN_0044b010(0,(PBYTE)&DAT_00497e90);
      if (iVar4 != 0) {
        iVar4 = 0;
        do {
          bVar8 = *(byte *)((int)&DAT_00497e90 + iVar4 + 1);
          (&DAT_004979a8)[iVar4] =
               (*(byte *)((int)&DAT_00497d90 + iVar4) ^ *(byte *)((int)&DAT_00497e90 + iVar4)) &
               *(byte *)((int)&DAT_00497e90 + iVar4);
          bVar1 = *(byte *)((int)&DAT_00497e90 + iVar4 + 2);
          (&DAT_004979a9)[iVar4] = (*(byte *)((int)&DAT_00497d90 + iVar4 + 1) ^ bVar8) & bVar8;
          bVar8 = *(byte *)((int)&DAT_00497e90 + iVar4 + 3);
          (&DAT_004979aa)[iVar4] = (*(byte *)((int)&DAT_00497d90 + iVar4 + 2) ^ bVar1) & bVar1;
          (&DAT_004979ab)[iVar4] = (*(byte *)((int)&DAT_00497d90 + iVar4 + 3) ^ bVar8) & bVar8;
          iVar4 = iVar4 + 4;
        } while (iVar4 < 0x100);
        if (DAT_004979a4 < 0x16) {
          if ((char)(&DAT_004979a8)[(&DAT_0046ef10)[DAT_004979a4]] < '\0') {
            DAT_004979a4 = DAT_004979a4 + 1;
            DAT_004979a0 = 0;
          }
          else {
            bVar8 = 0;
            iVar4 = 0;
            do {
              iVar6 = iVar4 + 3;
              bVar8 = bVar8 | (&DAT_004979a8)[iVar4] | (&DAT_004979aa)[iVar4] |
                              (&DAT_004979a9)[iVar4];
              iVar4 = iVar6;
            } while (iVar6 < 0x39);
            if ((char)bVar8 < '\0') goto LAB_004324b0;
          }
        }
        else {
          FUN_0042c8c0();
          FUN_0043dc90(&DAT_00492590,0);
LAB_004324b0:
          DAT_004979a4 = 0;
        }
      }
      DAT_004979a0 = DAT_004979a0 + 1;
      if (300 < DAT_004979a0) {
        DAT_004979a4 = 0;
        DAT_004979a0 = 0;
      }
    }
    if ((_DAT_00474e36 & 10) != 0) {
      FUN_0042c620(3);
      FUN_0043dc90(&DAT_00492590,0);
      FUN_0042c6d0(extraout_ECX_07);
      FUN_0042c6d0(extraout_ECX_08);
      FUN_0042c6d0(*(undefined4 *)(param_1 + 0x24));
      FUN_0042c6d0(extraout_ECX_09);
      FUN_0042c6d0(extraout_ECX_10);
      FUN_0042c6d0(extraout_ECX_11);
      FUN_0042c6d0(extraout_ECX_12);
      FUN_0042c6d0(extraout_ECX_13);
      FUN_0042c6d0(extraout_ECX_14);
      FUN_0042c6d0(extraout_ECX_15);
      FUN_0042c6d0(extraout_ECX_16);
      pvVar2 = g_pGameStateManager;
      piVar10 = (int *)(param_1 + 0x5d4);
      iVar4 = 10;
LAB_004325a0:
      iVar6 = *piVar10;
      if (iVar6 != 0) {
        for (piVar7 = *(int **)((int)pvVar2 + 0x72dad4); piVar7 != (int *)0x0;
            piVar7 = (int *)piVar7[1]) {
          if (*(int *)*piVar7 == iVar6) goto LAB_004325d7;
        }
        for (piVar7 = *(int **)((int)pvVar2 + 0x72dadc); piVar7 != (int *)0x0;
            piVar7 = (int *)piVar7[1]) {
          if (*(int *)*piVar7 == iVar6) goto LAB_004325d7;
        }
      }
      goto LAB_00432602;
    }
    break;
  case 3:
    if (5 < *(int *)(param_1 + 0x2b4)) {
      FUN_0042c6d0(this);
      FUN_0042c770(0x5a);
      FUN_0042c770(0x5b);
      FUN_0042c6d0(extraout_ECX_17);
      FUN_00409e50(extraout_ECX_18);
      FUN_0042c5c0(2);
      FUN_0044be70();
    }
  }
  return 1;
LAB_004325d7:
  iVar6 = *piVar7;
  if ((iVar6 != 0) && (*(undefined2 *)(iVar6 + 0x304) = 1, *(int *)(iVar6 + 0x18) == 0)) {
    for (piVar7 = *(int **)(iVar6 + 0x14); piVar7 != (int *)0x0; piVar7 = (int *)piVar7[1]) {
      *(undefined2 *)(*piVar7 + 0x304) = 1;
    }
  }
LAB_00432602:
  piVar10 = piVar10 + 1;
  iVar4 = iVar4 + -1;
  if (iVar4 == 0) {
    return 1;
  }
  goto LAB_004325a0;
}

