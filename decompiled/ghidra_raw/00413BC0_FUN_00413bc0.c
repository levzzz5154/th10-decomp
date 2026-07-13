/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x00413BC0
 * Tracking name: FUN_00413bc0
 * Ghidra name: FUN_00413bc0
 * Tracked span: 1968 bytes
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __fastcall FUN_00413bc0(undefined4 param_1)

{
  void *pvVar1;
  undefined4 *puVar2;
  uint *puVar3;
  undefined4 *puVar4;
  int *piVar5;
  undefined4 extraout_ECX;
  undefined4 extraout_ECX_00;
  int iVar6;
  int iVar7;
  int unaff_EDI;
  int local_4;
  
  if (*(int *)(unaff_EDI + 8) != 0) {
    puVar3 = (uint *)(*(int *)(unaff_EDI + 8) + 4);
    *puVar3 = *puVar3 | 2;
  }
  if (*(int *)(unaff_EDI + 0xc) != 0) {
    puVar3 = (uint *)(*(int *)(unaff_EDI + 0xc) + 4);
    *puVar3 = *puVar3 | 2;
  }
  if (*(int *)(unaff_EDI + 0x9e58) == 0) {
    puVar2 = FUN_00449950();
    puVar2[8] = 0xf;
    puVar2[0xd7] = puVar2[0xd7] | 0x40000000;
    FUN_00449870(puVar2,0);
    FUN_004489d0(extraout_ECX,(int)g_pGameStateManager);
    *(undefined4 *)(unaff_EDI + 0x9e58) = param_1;
  }
  if (*(int *)(unaff_EDI + 0x9e5c) == 0) {
    puVar2 = FUN_00449950();
    puVar2[8] = 0xf;
    puVar2[0xd7] = puVar2[0xd7] | 0x40000000;
    FUN_00449870(puVar2,1);
    FUN_004489d0(extraout_ECX_00,(int)g_pGameStateManager);
  }
  if ((*(byte *)(unaff_EDI + 0x36c) & 1) == 0) {
    local_4 = 10;
    do {
      FUN_0043e710(*(undefined2 **)(unaff_EDI + 0x9ec8));
      FUN_0043e710(*(undefined2 **)(unaff_EDI + 0x9ec8));
      local_4 = local_4 + -1;
    } while (local_4 != 0);
    iVar7 = 0;
    do {
      FUN_0043e710(*(undefined2 **)(unaff_EDI + 0x9ec8));
      iVar7 = iVar7 + 1;
    } while (iVar7 < 9);
    iVar7 = 0;
    do {
      FUN_0043e710(*(undefined2 **)(unaff_EDI + 0x9ec8));
      iVar7 = iVar7 + 1;
    } while (iVar7 < 4);
    iVar7 = 0;
    do {
      FUN_0043e710(*(undefined2 **)(unaff_EDI + 0x9ec8));
      iVar7 = iVar7 + 1;
    } while (iVar7 < 2);
    iVar7 = 0;
    do {
      FUN_0043e710(*(undefined2 **)(unaff_EDI + 0x9ec8));
      iVar7 = iVar7 + 1;
    } while (iVar7 < 7);
  }
  iVar7 = DAT_00474c70;
  iVar6 = 0;
  if (DAT_00474c70 < 1) {
LAB_00413db0:
    puVar3 = (uint *)(iVar6 * 0x3ac + 0x4cdc + unaff_EDI);
    iVar6 = 9 - iVar6;
    do {
      *puVar3 = *puVar3 & 0xfffffffd;
      puVar3 = puVar3 + 0xeb;
      iVar6 = iVar6 + -1;
    } while (iVar6 != 0);
  }
  else {
    puVar3 = (uint *)(unaff_EDI + 0x4cdc);
    iVar6 = DAT_00474c70;
    do {
      *puVar3 = *puVar3 | 2;
      puVar3 = puVar3 + 0xeb;
      iVar6 = iVar6 + -1;
    } while (iVar6 != 0);
    iVar6 = iVar7;
    if (iVar7 < 9) goto LAB_00413db0;
  }
  iVar7 = (((int)DAT_00474c48 % 0x14) * 100) / 0x14;
  FUN_0043e5a0(*(int *)(unaff_EDI + 0x9ec8),(int)DAT_00474c48 / 0x14 + 8);
  FUN_0043e5a0(*(int *)(unaff_EDI + 0x9ec8),iVar7 / 10 + 8);
  FUN_0043e5a0(*(int *)(unaff_EDI + 0x9ec8),iVar7 % 10 + 8);
  if (DAT_00491fb8 == 8) {
LAB_00413f87:
    if (((byte)DAT_00474ca0 & 0x20) != 0) goto LAB_00413f94;
  }
  else {
    if (((byte)DAT_00474ca0 & 0x20) == 0) {
      puVar4 = FUN_00449950();
      puVar4[0xd7] = puVar4[0xd7] | 0x40000000;
      puVar4[8] = 0xf;
      FUN_00449870(puVar4,0);
      puVar2 = puVar4 + 1;
      puVar4[2] = 0;
      puVar4[3] = 0;
      pvVar1 = g_pGameStateManager;
      *puVar2 = puVar4;
      if (*(int *)((int)pvVar1 + 0x72dad4) == 0) {
        *(undefined4 **)((int)pvVar1 + 0x72dad4) = puVar2;
      }
      else {
        iVar7 = *(int *)((int)pvVar1 + 0x72dad8);
        if (*(int *)(iVar7 + 4) != 0) {
          puVar4[2] = *(int *)(iVar7 + 4);
          *(undefined4 **)(*(int *)(iVar7 + 4) + 8) = puVar2;
        }
        *(undefined4 **)(iVar7 + 4) = puVar2;
        puVar4[3] = iVar7;
      }
      *(undefined4 **)((int)pvVar1 + 0x72dad8) = puVar2;
      iVar7 = *(int *)((int)pvVar1 + 0x732454);
      iVar6 = iVar7 + 1;
      *(int *)((int)pvVar1 + 0x732454) = iVar6;
      if (iVar6 == 0) {
        *(int *)((int)pvVar1 + 0x732454) = iVar7 + 2;
      }
      *puVar4 = *(undefined4 *)((int)pvVar1 + 0x732454);
      puVar4 = FUN_00449950();
      puVar4[0xd7] = puVar4[0xd7] | 0x40000000;
      puVar4[8] = 0xf;
      FUN_00449870(puVar4,1);
      pvVar1 = g_pGameStateManager;
      puVar2 = puVar4 + 1;
      *puVar2 = puVar4;
      puVar4[2] = 0;
      puVar4[3] = 0;
      if (*(int *)((int)pvVar1 + 0x72dad4) == 0) {
        *(undefined4 **)((int)pvVar1 + 0x72dad4) = puVar2;
      }
      else {
        iVar7 = *(int *)((int)pvVar1 + 0x72dad8);
        if (*(int *)(iVar7 + 4) != 0) {
          puVar4[2] = *(int *)(iVar7 + 4);
          *(undefined4 **)(*(int *)(iVar7 + 4) + 8) = puVar2;
        }
        *(undefined4 **)(iVar7 + 4) = puVar2;
        puVar4[3] = iVar7;
      }
      *(undefined4 **)((int)pvVar1 + 0x72dad8) = puVar2;
      iVar7 = *(int *)((int)pvVar1 + 0x732454);
      iVar6 = iVar7 + 1;
      *(int *)((int)pvVar1 + 0x732454) = iVar6;
      if (iVar6 == 0) {
        *(int *)((int)pvVar1 + 0x732454) = iVar7 + 2;
      }
      *puVar4 = *(undefined4 *)((int)pvVar1 + 0x732454);
      goto LAB_00413f87;
    }
LAB_00413f94:
    puVar4 = FUN_00449950();
    puVar4[0xd7] = puVar4[0xd7] | 0x40000000;
    puVar4[8] = 0xf;
    FUN_00449870(puVar4,0x71);
    pvVar1 = g_pGameStateManager;
    puVar2 = puVar4 + 1;
    *puVar2 = puVar4;
    puVar4[2] = 0;
    puVar4[3] = 0;
    if (*(int *)((int)pvVar1 + 0x72dad4) == 0) {
      *(undefined4 **)((int)pvVar1 + 0x72dad4) = puVar2;
    }
    else {
      iVar7 = *(int *)((int)pvVar1 + 0x72dad8);
      if (*(int *)(iVar7 + 4) != 0) {
        puVar4[2] = *(int *)(iVar7 + 4);
        *(undefined4 **)(*(int *)(iVar7 + 4) + 8) = puVar2;
      }
      *(undefined4 **)(iVar7 + 4) = puVar2;
      puVar4[3] = iVar7;
    }
    *(undefined4 **)((int)pvVar1 + 0x72dad8) = puVar2;
    iVar7 = *(int *)((int)pvVar1 + 0x732454);
    iVar6 = iVar7 + 1;
    *(int *)((int)pvVar1 + 0x732454) = iVar6;
    if (iVar6 == 0) {
      *(int *)((int)pvVar1 + 0x732454) = iVar7 + 2;
    }
    *puVar4 = *(undefined4 *)((int)pvVar1 + 0x732454);
  }
  FUN_0043e710(*(undefined2 **)((int)g_pGameThread + 0x8994));
  if (((DAT_00474c7c == 1) && (*(int *)(DAT_00477810 + 0x5c) == 0)) && (_DAT_00474c90 == 0)) {
    puVar4 = FUN_00449950();
    puVar4[0xd7] = puVar4[0xd7] | 0x40000000;
    puVar4[8] = 0xf;
    FUN_00449870(puVar4,0x4f);
    pvVar1 = g_pGameStateManager;
    puVar2 = puVar4 + 1;
    *puVar2 = puVar4;
    puVar4[2] = 0;
    puVar4[3] = 0;
    if (*(int *)((int)pvVar1 + 0x72dad4) == 0) {
      *(undefined4 **)((int)pvVar1 + 0x72dad4) = puVar2;
    }
    else {
      iVar7 = *(int *)((int)pvVar1 + 0x72dad8);
      if (*(int *)(iVar7 + 4) != 0) {
        puVar4[2] = *(int *)(iVar7 + 4);
        *(undefined4 **)(*(int *)(iVar7 + 4) + 8) = puVar2;
      }
      *(undefined4 **)(iVar7 + 4) = puVar2;
      puVar4[3] = iVar7;
    }
    *(undefined4 **)((int)pvVar1 + 0x72dad8) = puVar2;
    iVar7 = *(int *)((int)pvVar1 + 0x732454);
    iVar6 = iVar7 + 1;
    *(int *)((int)pvVar1 + 0x732454) = iVar6;
    if (iVar6 == 0) {
      *(int *)((int)pvVar1 + 0x732454) = iVar7 + 2;
    }
    *puVar4 = *(undefined4 *)((int)pvVar1 + 0x732454);
  }
  iVar7 = DAT_00474c74;
  if (DAT_00491fc4 != 0) {
    puVar4 = FUN_00449950();
    puVar4[0xd7] = puVar4[0xd7] | 0x40000000;
    puVar4[8] = 0xf;
    FUN_00449870(puVar4,iVar7 + 0x66);
    pvVar1 = g_pGameStateManager;
    puVar2 = puVar4 + 1;
    *puVar2 = puVar4;
    puVar4[2] = 0;
    puVar4[3] = 0;
    if (*(int *)((int)pvVar1 + 0x72dad4) == 0) {
      *(undefined4 **)((int)pvVar1 + 0x72dad4) = puVar2;
    }
    else {
      iVar7 = *(int *)((int)pvVar1 + 0x72dad8);
      if (*(int *)(iVar7 + 4) != 0) {
        puVar4[2] = *(int *)(iVar7 + 4);
        *(undefined4 **)(*(int *)(iVar7 + 4) + 8) = puVar2;
      }
      *(undefined4 **)(iVar7 + 4) = puVar2;
      puVar4[3] = iVar7;
    }
    *(undefined4 **)((int)pvVar1 + 0x72dad8) = puVar2;
    iVar7 = *(int *)((int)pvVar1 + 0x732454);
    iVar6 = iVar7 + 1;
    *(int *)((int)pvVar1 + 0x732454) = iVar6;
    if (iVar6 == 0) {
      *(int *)((int)pvVar1 + 0x732454) = iVar7 + 2;
    }
    *puVar4 = *(undefined4 *)((int)pvVar1 + 0x732454);
    iVar7 = *(int *)((int)pvVar1 + 0x732454);
    *(int *)(unaff_EDI + 0x9e50) = iVar7;
    if (iVar7 != 0) {
      for (piVar5 = *(int **)((int)pvVar1 + 0x72dad4); piVar5 != (int *)0x0;
          piVar5 = (int *)piVar5[1]) {
        if (*(int *)*piVar5 == iVar7) goto LAB_00414206;
      }
      for (piVar5 = *(int **)((int)pvVar1 + 0x72dadc); piVar5 != (int *)0x0;
          piVar5 = (int *)piVar5[1]) {
        if (*(int *)*piVar5 == iVar7) goto LAB_00414206;
      }
    }
  }
LAB_00414240:
  iVar7 = DAT_00474c74;
  puVar4 = FUN_00449950();
  puVar4[8] = 0xf;
  puVar4[0xd7] = puVar4[0xd7] | 0x40000000;
  FUN_00449870(puVar4,iVar7 + 0x6b);
  pvVar1 = g_pGameStateManager;
  puVar2 = puVar4 + 1;
  *puVar2 = puVar4;
  puVar4[2] = 0;
  puVar4[3] = 0;
  if (*(int *)((int)pvVar1 + 0x72dad4) == 0) {
    *(undefined4 **)((int)pvVar1 + 0x72dad4) = puVar2;
  }
  else {
    iVar7 = *(int *)((int)pvVar1 + 0x72dad8);
    if (*(int *)(iVar7 + 4) != 0) {
      puVar4[2] = *(int *)(iVar7 + 4);
      *(undefined4 **)(*(int *)(iVar7 + 4) + 8) = puVar2;
    }
    *(undefined4 **)(iVar7 + 4) = puVar2;
    puVar4[3] = iVar7;
  }
  *(undefined4 **)((int)pvVar1 + 0x72dad8) = puVar2;
  iVar7 = *(int *)((int)pvVar1 + 0x732454);
  iVar6 = iVar7 + 1;
  *(int *)((int)pvVar1 + 0x732454) = iVar6;
  if (iVar6 == 0) {
    *(int *)((int)pvVar1 + 0x732454) = iVar7 + 2;
  }
  *puVar4 = *(undefined4 *)((int)pvVar1 + 0x732454);
  iVar7 = *(int *)(unaff_EDI + 0x9e50);
  *(undefined4 *)(unaff_EDI + 0x9e54) = *(undefined4 *)((int)pvVar1 + 0x732454);
  if (iVar7 != 0) {
    for (piVar5 = *(int **)((int)pvVar1 + 0x72dad4); piVar5 != (int *)0x0; piVar5 = (int *)piVar5[1]
        ) {
      if (*(int *)*piVar5 == iVar7) {
        iVar7 = *piVar5;
        goto LAB_00414336;
      }
    }
    piVar5 = *(int **)((int)pvVar1 + 0x72dadc);
    if (piVar5 != (int *)0x0) {
      while (*(int *)*piVar5 != iVar7) {
        piVar5 = (int *)piVar5[1];
        if (piVar5 == (int *)0x0) {
          *(undefined4 *)(unaff_EDI + 0x9e90) = 0;
          return;
        }
      }
      iVar7 = *piVar5;
LAB_00414336:
      if ((iVar7 != 0) && (*(undefined2 *)(iVar7 + 0x304) = 3, *(int *)(iVar7 + 0x18) == 0)) {
        for (piVar5 = *(int **)(iVar7 + 0x14); piVar5 != (int *)0x0; piVar5 = (int *)piVar5[1]) {
          *(undefined2 *)(*piVar5 + 0x304) = 3;
        }
      }
    }
  }
  *(undefined4 *)(unaff_EDI + 0x9e90) = 0;
  return;
LAB_00414206:
  iVar7 = *piVar5;
  if ((iVar7 != 0) && (*(undefined2 *)(iVar7 + 0x304) = 3, *(int *)(iVar7 + 0x18) == 0)) {
    for (piVar5 = *(int **)(iVar7 + 0x14); piVar5 != (int *)0x0; piVar5 = (int *)piVar5[1]) {
      *(undefined2 *)(*piVar5 + 0x304) = 3;
    }
  }
  goto LAB_00414240;
}

