/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x00409280
 * Tracking name: FUN_00409280
 * Ghidra name: FUN_00409280
 * Tracked span: 2432 bytes
 */


void FUN_00409280(int param_1,int param_2,char *param_3,undefined4 param_4)

{
  int iVar1;
  char cVar2;
  int iVar3;
  void *pvVar4;
  void *pvVar5;
  char *pcVar6;
  int iVar7;
  undefined4 *puVar8;
  int *piVar9;
  undefined4 *puVar10;
  int iVar11;
  void *this;
  void *this_00;
  undefined4 extraout_ECX;
  char *pcVar12;
  
  if ((*(uint *)(param_1 + 0x3744) & 1) == 0) {
    *(undefined4 *)(param_1 + 0x3738) = 0;
    *(undefined4 *)(param_1 + 0x3734) = 0xfff0bdc1;
    *(undefined4 *)(param_1 + 0x373c) = 0;
    *(undefined4 **)(param_1 + 0x3740) = &DAT_00476f78;
    *(uint *)(param_1 + 0x3744) = *(uint *)(param_1 + 0x3744) | 1;
  }
  *(undefined4 *)(param_1 + 0x3738) = 0;
  *(undefined4 *)(param_1 + 0x373c) = 0;
  *(undefined4 *)(param_1 + 0x3734) = 0xffffffff;
  *(int *)(param_1 + 0x3788) = param_2;
  pcVar6 = param_3;
  do {
    cVar2 = *pcVar6;
    pcVar6[(param_1 + 0x3748) - (int)param_3] = cVar2;
    iVar7 = DAT_00477838;
    pcVar6 = pcVar6 + 1;
  } while (cVar2 != '\0');
  *(uint *)(param_1 + 0x378c) = *(uint *)(param_1 + 0x378c) & 0xffffffe7 | 3;
  iVar11 = DAT_0047783c;
  if (*(int *)(iVar7 + 0x10) != 1) {
    iVar7 = param_2 * 0x90;
    pcVar6 = (char *)((DAT_00474c6c + DAT_00474c68 * 3) * 0x437c + iVar7 + 0x5a4 + DAT_0047783c);
    pcVar12 = param_3;
    do {
      cVar2 = *pcVar12;
      pcVar12 = pcVar12 + 1;
      *pcVar6 = cVar2;
      pcVar6 = pcVar6 + 1;
    } while (cVar2 != '\0');
    iVar1 = (DAT_00474c6c + DAT_00474c68 * 3) * 0x437c + iVar7 + 0x5a4 + iVar11;
    iVar3 = *(int *)(iVar1 + 0x84);
    if (iVar3 < 99999) {
      *(int *)(iVar1 + 0x84) = iVar3 + 1;
    }
    iVar11 = iVar7 + 0x19a8c + iVar11;
    pcVar6 = param_3;
    do {
      cVar2 = *pcVar6;
      pcVar6[iVar11 - (int)param_3] = cVar2;
      pcVar6 = pcVar6 + 1;
    } while (cVar2 != '\0');
    if (*(int *)(iVar11 + 0x84) < 99999) {
      *(int *)(iVar11 + 0x84) = *(int *)(iVar11 + 0x84) + 1;
    }
  }
  iVar7 = 0;
  do {
    FUN_0043e710(*(undefined2 **)(DAT_0047770c + 0x9ec8));
    iVar7 = iVar7 + 1;
  } while (iVar7 < 8);
  iVar7 = 0;
  do {
    FUN_0043e710(*(undefined2 **)(DAT_0047770c + 0x9ec8));
    iVar7 = iVar7 + 1;
  } while (iVar7 < 5);
  puVar8 = FUN_00449950();
  puVar8[8] = 0xf;
  puVar8[0xd7] = puVar8[0xd7] | 0x40000000;
  FUN_00449870(puVar8,1);
  pvVar4 = g_pGameStateManager;
  puVar10 = puVar8 + 1;
  *puVar10 = puVar8;
  puVar8[2] = 0;
  puVar8[3] = 0;
  if (*(int *)((int)pvVar4 + 0x72dad4) == 0) {
    *(undefined4 **)((int)pvVar4 + 0x72dad4) = puVar10;
  }
  else {
    iVar7 = *(int *)((int)pvVar4 + 0x72dad8);
    if (*(int *)(iVar7 + 4) != 0) {
      puVar8[2] = *(int *)(iVar7 + 4);
      *(undefined4 **)(*(int *)(iVar7 + 4) + 8) = puVar10;
    }
    *(undefined4 **)(iVar7 + 4) = puVar10;
    puVar8[3] = iVar7;
  }
  *(undefined4 **)((int)pvVar4 + 0x72dad8) = puVar10;
  iVar7 = *(int *)((int)pvVar4 + 0x732454);
  iVar11 = iVar7 + 1;
  *(int *)((int)pvVar4 + 0x732454) = iVar11;
  if (iVar11 == 0) {
    *(int *)((int)pvVar4 + 0x732454) = iVar7 + 2;
  }
  *puVar8 = *(undefined4 *)((int)pvVar4 + 0x732454);
  *(undefined4 *)(param_1 + 0x768) = *(undefined4 *)((int)pvVar4 + 0x732454);
  puVar8 = FUN_00449950();
  puVar8[0xd7] = puVar8[0xd7] | 0x40000000;
  puVar8[8] = 0xf;
  FUN_00449870(puVar8,0x48);
  pvVar4 = g_pGameStateManager;
  puVar10 = puVar8 + 1;
  *puVar10 = puVar8;
  puVar8[2] = 0;
  puVar8[3] = 0;
  if (*(int *)((int)pvVar4 + 0x72dad4) == 0) {
    *(undefined4 **)((int)pvVar4 + 0x72dad4) = puVar10;
  }
  else {
    iVar7 = *(int *)((int)pvVar4 + 0x72dad8);
    if (*(int *)(iVar7 + 4) != 0) {
      puVar8[2] = *(int *)(iVar7 + 4);
      *(undefined4 **)(*(int *)(iVar7 + 4) + 8) = puVar10;
    }
    *(undefined4 **)(iVar7 + 4) = puVar10;
    puVar8[3] = iVar7;
  }
  *(undefined4 **)((int)pvVar4 + 0x72dad8) = puVar10;
  iVar7 = *(int *)((int)pvVar4 + 0x732454);
  iVar11 = iVar7 + 1;
  *(int *)((int)pvVar4 + 0x732454) = iVar11;
  if (iVar11 == 0) {
    *(int *)((int)pvVar4 + 0x732454) = iVar7 + 2;
  }
  *puVar8 = *(undefined4 *)((int)pvVar4 + 0x732454);
  *(undefined4 *)(param_1 + 0x76c) = *(undefined4 *)((int)pvVar4 + 0x732454);
  puVar8 = FUN_00449950();
  puVar8[8] = 0xf;
  puVar8[0xd7] = puVar8[0xd7] | 0x40000000;
  FUN_00449870(puVar8,2);
  pvVar4 = g_pGameStateManager;
  puVar10 = puVar8 + 1;
  *puVar10 = puVar8;
  puVar8[2] = 0;
  puVar8[3] = 0;
  if (*(int *)((int)pvVar4 + 0x72dad4) == 0) {
    *(undefined4 **)((int)pvVar4 + 0x72dad4) = puVar10;
  }
  else {
    iVar7 = *(int *)((int)pvVar4 + 0x72dad8);
    if (*(int *)(iVar7 + 4) != 0) {
      puVar8[2] = *(int *)(iVar7 + 4);
      *(undefined4 **)(*(int *)(iVar7 + 4) + 8) = puVar10;
    }
    *(undefined4 **)(iVar7 + 4) = puVar10;
    puVar8[3] = iVar7;
  }
  *(undefined4 **)((int)pvVar4 + 0x72dad8) = puVar10;
  iVar7 = *(int *)((int)pvVar4 + 0x732454);
  iVar11 = iVar7 + 1;
  *(int *)((int)pvVar4 + 0x732454) = iVar11;
  if (iVar11 == 0) {
    *(int *)((int)pvVar4 + 0x732454) = iVar7 + 2;
  }
  *puVar8 = *(undefined4 *)((int)pvVar4 + 0x732454);
  *(undefined4 *)(param_1 + 0x770) = *(undefined4 *)((int)pvVar4 + 0x732454);
  iVar7 = *(int *)(param_1 + 0x76c);
  if (iVar7 != 0) {
    for (piVar9 = *(int **)((int)pvVar4 + 0x72dad4); piVar9 != (int *)0x0; piVar9 = (int *)piVar9[1]
        ) {
      if (*(int *)*piVar9 == iVar7) goto LAB_00409668;
    }
    for (piVar9 = *(int **)((int)pvVar4 + 0x72dadc); piVar9 != (int *)0x0; piVar9 = (int *)piVar9[1]
        ) {
      if (*(int *)*piVar9 == iVar7) goto LAB_00409668;
    }
  }
LAB_0040966e:
  *(undefined4 *)(param_1 + 0x76c) = 0;
LAB_00409674:
  FUN_00447ae0(pvVar4,0xffffff,param_3);
  FUN_0043dc90(&DAT_00492590,0);
  puVar8 = FUN_00449950();
  puVar8[0xd7] = puVar8[0xd7] | 0x40000000;
  puVar8[8] = 0xf;
  FUN_00449870(puVar8,0x1a1);
  pvVar4 = g_pGameStateManager;
  puVar10 = puVar8 + 1;
  *puVar10 = puVar8;
  puVar8[2] = 0;
  puVar8[3] = 0;
  if (*(int *)((int)pvVar4 + 0x72dad4) == 0) {
    *(undefined4 **)((int)pvVar4 + 0x72dad4) = puVar10;
  }
  else {
    iVar7 = *(int *)((int)pvVar4 + 0x72dad8);
    if (*(int *)(iVar7 + 4) != 0) {
      puVar8[2] = *(int *)(iVar7 + 4);
      *(undefined4 **)(*(int *)(iVar7 + 4) + 8) = puVar10;
    }
    *(undefined4 **)(iVar7 + 4) = puVar10;
    puVar8[3] = iVar7;
  }
  *(undefined4 **)((int)pvVar4 + 0x72dad8) = puVar10;
  iVar7 = *(int *)((int)pvVar4 + 0x732454);
  iVar11 = iVar7 + 1;
  *(int *)((int)pvVar4 + 0x732454) = iVar11;
  if (iVar11 == 0) {
    *(int *)((int)pvVar4 + 0x732454) = iVar7 + 2;
  }
  pvVar5 = DAT_00477704;
  *puVar8 = *(undefined4 *)((int)pvVar4 + 0x732454);
  iVar7 = *(int *)((int)pvVar4 + 0x732454);
  *(int *)(param_1 + 0x774) = iVar7;
  iVar11 = *(int *)((int)pvVar5 + 0x10);
  *(undefined4 *)(param_1 + 0x379c) = *(undefined4 *)(iVar11 + 0x1068);
  *(undefined4 *)(param_1 + 0x37a0) = *(undefined4 *)(iVar11 + 0x106c);
  *(undefined4 *)(param_1 + 0x37a4) = *(undefined4 *)(iVar11 + 0x1070);
  FUN_00449350((undefined4 *)(param_1 + 0x379c),(int)pvVar4,iVar7);
  iVar7 = *(int *)(param_1 + 0x774);
  if (iVar7 == 0) {
LAB_00409783:
    iVar7 = 0;
  }
  else {
    for (piVar9 = *(int **)((int)pvVar4 + 0x72dad4); piVar9 != (int *)0x0; piVar9 = (int *)piVar9[1]
        ) {
      if (*(int *)*piVar9 == iVar7) goto LAB_004097b9;
    }
    piVar9 = *(int **)((int)pvVar4 + 0x72dadc);
    if (piVar9 == (int *)0x0) goto LAB_00409783;
    do {
      if (*(int *)*piVar9 == iVar7) goto LAB_004097b9;
      piVar9 = (int *)piVar9[1];
    } while (piVar9 != (int *)0x0);
    iVar7 = 0;
  }
LAB_004097bf:
  *(undefined4 *)(param_1 + 0x774) = 0;
LAB_004097c5:
  for (piVar9 = (int *)(iVar7 + 0x10); piVar9 != (int *)0x0; piVar9 = (int *)piVar9[1]) {
    if (*(short *)(*piVar9 + 0x38a) == 0x19f) {
      iVar7 = *piVar9;
      goto LAB_004097e5;
    }
  }
  iVar7 = 0;
LAB_004097e5:
  *(undefined4 *)(iVar7 + 0x314) = param_4;
  iVar7 = *(int *)(param_1 + 0x774);
  if (iVar7 == 0) {
LAB_004097f9:
    iVar7 = 0;
  }
  else {
    for (piVar9 = *(int **)((int)pvVar4 + 0x72dad4); piVar9 != (int *)0x0; piVar9 = (int *)piVar9[1]
        ) {
      if (*(int *)*piVar9 == iVar7) goto LAB_00409838;
    }
    piVar9 = *(int **)((int)pvVar4 + 0x72dadc);
    if (piVar9 == (int *)0x0) goto LAB_004097f9;
    do {
      if (*(int *)*piVar9 == iVar7) goto LAB_00409838;
      piVar9 = (int *)piVar9[1];
    } while (piVar9 != (int *)0x0);
    iVar7 = 0;
  }
LAB_0040983e:
  *(undefined4 *)(param_1 + 0x774) = 0;
LAB_00409844:
  for (piVar9 = (int *)(iVar7 + 0x10); piVar9 != (int *)0x0; piVar9 = (int *)piVar9[1]) {
    if (*(short *)(*piVar9 + 0x38a) == 0x1a0) {
      iVar7 = *piVar9;
      goto LAB_00409868;
    }
  }
  iVar7 = 0;
LAB_00409868:
  *(undefined4 *)(iVar7 + 0x314) = param_4;
  *(undefined4 *)(param_1 + 0x3798) = param_4;
  iVar7 = (DAT_00474c7c * 3 + 10) * DAT_00474c4c * 10;
  *(int *)(param_1 + 0x3790) = iVar7;
  *(int *)(param_1 + 0x3794) = iVar7;
  if (99999999 < iVar7) {
    *(undefined4 *)(param_1 + 0x3794) = 99999999;
  }
  puVar8 = FUN_00449950();
  puVar8[0xd7] = puVar8[0xd7] | 0x40000000;
  puVar8[8] = 0xf;
  FUN_00449870(puVar8,0x1ab);
  pvVar4 = g_pGameStateManager;
  puVar10 = puVar8 + 1;
  *puVar10 = puVar8;
  puVar8[2] = 0;
  puVar8[3] = 0;
  if (*(int *)((int)pvVar4 + 0x72dad4) == 0) {
    *(undefined4 **)((int)pvVar4 + 0x72dad4) = puVar10;
  }
  else {
    iVar7 = *(int *)((int)pvVar4 + 0x72dad8);
    if (*(int *)(iVar7 + 4) != 0) {
      puVar8[2] = *(int *)(iVar7 + 4);
      *(undefined4 **)(*(int *)(iVar7 + 4) + 8) = puVar10;
    }
    *(undefined4 **)(iVar7 + 4) = puVar10;
    puVar8[3] = iVar7;
  }
  *(undefined4 **)((int)pvVar4 + 0x72dad8) = puVar10;
  iVar7 = *(int *)((int)pvVar4 + 0x732454);
  iVar11 = iVar7 + 1;
  *(int *)((int)pvVar4 + 0x732454) = iVar11;
  if (iVar11 == 0) {
    *(int *)((int)pvVar4 + 0x732454) = iVar7 + 2;
  }
  pvVar4 = *(void **)((int)pvVar4 + 0x732454);
  *puVar8 = pvVar4;
  switch(DAT_00474c7c) {
  case 1:
    FUN_00404f30(pvVar4,*(undefined2 **)((int)DAT_00477704 + 0x38));
    FUN_00404f30(DAT_00477704,*(undefined2 **)((int)DAT_00477704 + 0x38));
    if (param_2 < 2) {
      puVar10 = FUN_00449950();
      iVar7 = 0xf;
    }
    else {
      puVar10 = FUN_00449950();
      iVar7 = 0xe;
    }
    break;
  case 2:
    FUN_00404f30(pvVar4,*(undefined2 **)((int)DAT_00477704 + 0x38));
    FUN_00404f30(DAT_00477704,*(undefined2 **)((int)DAT_00477704 + 0x38));
    puVar10 = FUN_00449950();
    iVar7 = 0x11;
    break;
  case 3:
    FUN_00404f30(DAT_00477704,*(undefined2 **)((int)DAT_00477704 + 0x38));
    FUN_00404f30(*(void **)((int)DAT_00477704 + 0x38),*(void **)((int)DAT_00477704 + 0x38));
    puVar10 = FUN_00449950();
    iVar7 = 0x15;
    break;
  case 4:
    FUN_00404f30(*(void **)((int)DAT_00477704 + 0x38),*(void **)((int)DAT_00477704 + 0x38));
    FUN_00404f30(this,*(undefined2 **)((int)DAT_00477704 + 0x38));
    puVar10 = FUN_00449950();
    iVar7 = 0x16;
    break;
  case 5:
    FUN_00404f30(pvVar4,*(undefined2 **)((int)DAT_00477704 + 0x38));
    FUN_00404f30(DAT_00477704,*(undefined2 **)((int)DAT_00477704 + 0x38));
    puVar10 = FUN_00449950();
    iVar7 = 0xf;
    break;
  case 6:
    FUN_00404f30(DAT_00477704,*(undefined2 **)((int)DAT_00477704 + 0x38));
    FUN_00404f30(*(void **)((int)DAT_00477704 + 0x38),*(void **)((int)DAT_00477704 + 0x38));
    puVar10 = FUN_00449950();
    iVar7 = 0x24;
    break;
  case 7:
    pvVar4 = *(void **)((int)DAT_00477704 + 0x38);
    if (DAT_00474c84 < 0x18) {
      FUN_00404f30(pvVar4,pvVar4);
      puVar10 = FUN_00449950();
      iVar7 = 0x28;
    }
    else {
      FUN_00404f30(pvVar4,pvVar4);
      FUN_00404f30(this_00,*(undefined2 **)((int)DAT_00477704 + 0x38));
      puVar10 = FUN_00449950();
      iVar7 = 0x1e;
    }
    break;
  default:
    goto switchD_0040995d_default;
  }
  puVar10[0xd7] = puVar10[0xd7] | 0x40000000;
  puVar10[8] = 0xf;
  FUN_00449870(puVar10,iVar7);
  FUN_004489d0(extraout_ECX,(int)g_pGameStateManager);
switchD_0040995d_default:
  return;
LAB_00409668:
  if (*piVar9 == 0) goto LAB_0040966e;
  goto LAB_00409674;
LAB_004097b9:
  iVar7 = *piVar9;
  if (iVar7 == 0) goto LAB_004097bf;
  goto LAB_004097c5;
LAB_00409838:
  iVar7 = *piVar9;
  if (iVar7 == 0) goto LAB_0040983e;
  goto LAB_00409844;
}

