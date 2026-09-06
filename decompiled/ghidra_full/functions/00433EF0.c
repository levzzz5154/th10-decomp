/* Raw Ghidra reference; not compilable reconstruction. Address: 00433EF0 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __thiscall FUN_00433ef0(void *this,size_t *param_1)

{
  byte bVar1;
  size_t *psVar2;
  size_t *psVar3;
  byte *this_00;
  void *pvVar4;
  undefined4 *puVar5;
  uint uVar6;
  int iVar7;
  size_t sVar8;
  int iVar9;
  int *piVar10;
  size_t *psVar11;
  undefined4 extraout_ECX;
  undefined4 extraout_ECX_00;
  size_t sVar12;
  size_t extraout_ECX_01;
  size_t extraout_ECX_02;
  undefined4 extraout_ECX_03;
  undefined4 extraout_ECX_04;
  undefined4 uVar13;
  undefined4 extraout_ECX_05;
  undefined4 extraout_ECX_06;
  undefined4 extraout_ECX_07;
  undefined4 extraout_ECX_08;
  void *this_01;
  bool bVar14;
  COLORREF CVar15;
  char *pcVar16;
  size_t *local_1c;
  size_t *local_18;
  char *local_14;
  float local_c;
  float local_8;
  size_t local_4;
  
  psVar2 = param_1;
  switch(param_1[8]) {
  case 0:
    if (param_1[0xad] == 1) {
      param_1[0xb] = 6;
      sVar12 = param_1[0xb];
      if (sVar12 == 0) {
        param_1[9] = 0;
      }
      else if ((int)sVar12 < 1) {
        param_1[9] = sVar12 - 1;
      }
      else {
        param_1[9] = 0;
      }
      iVar7 = FUN_004491c0(this,(int)g_pGameStateManager,param_1[0x110]);
      if (iVar7 == 0) {
        FUN_0042c670((int)psVar2);
        psVar3 = (size_t *)FUN_00448d00(*(undefined4 *)((int)g_pGameThread + 0x8994),8,0xf);
        psVar2[0x174] = *psVar3;
      }
      FUN_0042c670((int)psVar2);
      local_14 = (char *)0x0;
      this_00 = FUN_0044b360((size_t *)&param_1,0);
      psVar2[0x16ab] = (size_t)this_00;
      if (this_00 == (byte *)0x0) goto LAB_00434803;
      if (0 < (int)param_1) {
        local_18 = psVar2 + 0x3a6;
        local_1c = psVar2 + 0x1a6;
        psVar3 = psVar2 + 0x5b6;
        psVar11 = local_18;
        do {
          bVar1 = *this_00;
          if ((bVar1 == 0x23) || (bVar1 != 0x40)) {
            this_00 = (byte *)FUN_004349e0(CONCAT31((int3)((uint)psVar11 >> 8),bVar1),
                                           (int *)&param_1);
          }
          else {
            pvVar4 = (void *)FUN_00434a20(this_00 + 1,(int)local_1c);
            this_00 = (byte *)FUN_00434a20(pvVar4,(int)local_18);
            iVar7 = 8;
            do {
              this_00 = (byte *)FUN_00434a20(this_00,(int)psVar3);
              psVar3 = (size_t *)((int)psVar3 + 0x42);
              iVar7 = iVar7 + -1;
            } while (iVar7 != 0);
            local_14 = (char *)((int)local_14 + 1);
            local_1c = local_1c + 0x10;
            local_18 = (size_t *)((int)local_18 + 0x42);
          }
          psVar11 = param_1;
        } while (0 < (int)param_1);
      }
      iVar7 = 0;
      psVar2[0xb] = (size_t)local_14;
      if (local_14 == (char *)0x0) {
        psVar2[9] = 0;
      }
      else if ((int)local_14 < 1) {
        psVar2[9] = (int)local_14 - 1;
      }
      else {
        psVar2[9] = 0;
      }
      param_1 = psVar2 + 0x199;
      psVar2[0x1636] = 0;
      psVar2[0x1a2] = (size_t)local_14;
      do {
        puVar5 = FUN_00449950();
        puVar5[0xd7] = puVar5[0xd7] | 0x40000000;
        puVar5[8] = 0xf;
        FUN_00449870(puVar5,iVar7 + 0x27);
        FUN_004489d0(extraout_ECX,(int)g_pGameStateManager);
        *param_1 = (size_t)local_18;
        iVar7 = iVar7 + 1;
        param_1 = param_1 + 1;
      } while (iVar7 < 8);
      psVar2[0x1a3] = 0;
      psVar2[0x1a4] = 0;
      psVar2[0x1a5] = 0;
    }
    sVar12 = psVar2[0xad];
    if ((int)sVar12 < 10) {
      iVar7 = sVar12 * 2;
      sVar8 = iVar7 - 2;
      local_c = 64.0;
      local_4 = 0;
      local_8 = (_DAT_00470c80 - (float)(int)psVar2[0x1636] * _DAT_00470ca0) +
                (float)(int)(sVar12 * 0x28 + -0x28);
      if ((int)sVar8 < iVar7) {
        local_14 = (char *)(sVar8 * 0x42 + 0xe98 + (int)psVar2);
        param_1 = psVar2 + iVar7 + 0x183;
        do {
          if ((int)psVar2[0x1a2] <= (int)sVar8) break;
          puVar5 = FUN_00449950();
          puVar5[8] = 0xf;
          puVar5[0xd7] = puVar5[0xd7] | 0x40000000;
          FUN_00449870(puVar5,sVar8 + 0xad);
          pvVar4 = g_pGameStateManager;
          FUN_004489d0(extraout_ECX_00,(int)g_pGameStateManager);
          *param_1 = (size_t)local_1c;
          iVar7 = FUN_004491c0(local_1c,(int)pvVar4,(int)local_1c);
          if (iVar7 == 0) {
            *param_1 = 0;
          }
          if (*(char *)(DAT_0047783c + 0x1d892 + sVar8) == '\0') {
            FUN_00447a50(pvVar4,0xffffff,&DAT_0046ecf4);
          }
          else {
            FUN_00447a50(pvVar4,0xffffff,local_14);
          }
          if (((int)sVar8 < (int)psVar2[0x1636]) || ((int)(psVar2[0x1636] + 10) <= (int)sVar8)) {
            uVar6 = *(uint *)(iVar7 + 0x35c) & 0xfffffffd;
          }
          else {
            uVar6 = *(uint *)(iVar7 + 0x35c) | 2;
          }
          *(uint *)(iVar7 + 0x35c) = uVar6;
          if (sVar8 == psVar2[9]) {
            local_c = local_c - (float)_DAT_00470c98;
          }
          FUN_00434a80(&local_c,(undefined4 *)(iVar7 + 0x334),4,0);
          if (sVar8 == psVar2[9]) {
            local_c = local_c + (float)_DAT_00470c98;
          }
          local_8 = local_8 + _DAT_00470ca0;
          local_14 = local_14 + 0x42;
          param_1 = param_1 + 1;
          *(ushort *)(iVar7 + 0x304) = (sVar8 != psVar2[9]) + 2;
          sVar8 = sVar8 + 1;
        } while ((int)sVar8 < (int)(psVar2[0xad] * 2));
      }
    }
    if (9 < (int)psVar2[0xad]) {
      psVar2[8] = 1;
      if ((psVar2[0xb0] & 1) == 0) {
        psVar2[0xad] = 0;
        psVar2[0xac] = 0xfff0bdc1;
        psVar2[0xae] = 0;
        psVar2[0xaf] = (size_t)&DAT_00476f78;
        psVar2[0xb0] = psVar2[0xb0] | 1;
      }
      psVar2[0xad] = 0;
      psVar2[0xae] = 0;
      psVar2[0xac] = 0xffffffff;
      return 0;
    }
    break;
  case 1:
    uVar6 = param_1[0xad] & 0x80000001;
    if ((int)uVar6 < 0) {
      uVar6 = (uVar6 - 1 | 0xfffffffe) + 1;
    }
    if ((uVar6 == 0) && ((int)param_1[0x1a3] < 8)) {
      iVar7 = FUN_00449450(this);
      if ((*(char *)(psVar2[0x1a4] + 0x1d892 + DAT_0047783c) == '\0') && (psVar2[0x1a5] != 0)) {
        pcVar16 = (&PTR_DAT_00476fd8)[psVar2[0x1a3]];
        CVar15 = 0x8080ff;
      }
      else {
        pcVar16 = (char *)((psVar2[0x1a3] + psVar2[0x1a4] * 8) * 0x42 + 0x16d8 + (int)psVar2);
        CVar15 = 0xffffff;
      }
      FUN_00447a50(g_pGameStateManager,CVar15,pcVar16);
      *(undefined2 *)(iVar7 + 0x304) = 2;
      psVar2[0x1a3] = psVar2[0x1a3] + 1;
    }
    if (4 < (int)psVar2[0xad]) {
      FUN_0042c620(2);
      return 0;
    }
    break;
  case 2:
    uVar6 = param_1[0xad] & 0x80000001;
    bVar14 = uVar6 == 0;
    if ((int)uVar6 < 0) {
      bVar14 = (uVar6 - 1 | 0xfffffffe) == 0xffffffff;
    }
    if ((bVar14) && ((int)param_1[0x1a3] < 8)) {
      iVar7 = FUN_00449450(this);
      if ((*(char *)(psVar2[0x1a4] + 0x1d892 + DAT_0047783c) == '\0') && (psVar2[0x1a5] != 0)) {
        pcVar16 = (&PTR_DAT_00476fd8)[psVar2[0x1a3]];
        CVar15 = 0x8080ff;
      }
      else {
        pcVar16 = (char *)((psVar2[0x1a3] + psVar2[0x1a4] * 8) * 0x42 + 0x16d8 + (int)psVar2);
        CVar15 = 0xffffff;
      }
      FUN_00447a50(g_pGameStateManager,CVar15,pcVar16);
      *(undefined2 *)(iVar7 + 0x304) = 2;
      psVar2[0x1a3] = psVar2[0x1a3] + 1;
    }
    psVar2[10] = psVar2[9];
    if (((_DAT_00474e36 & 0x10) != 0) || ((DAT_00474e34 & 0x10) != 0)) {
      FUN_0044bea0(-1);
    }
    if (((_DAT_00474e36 & 0x20) != 0) || ((DAT_00474e34 & 0x20) != 0)) {
      FUN_0044bea0(1);
    }
    sVar12 = psVar2[10];
    if (sVar12 != psVar2[9]) {
      FUN_0043dc90(&DAT_00492590,0);
      sVar12 = psVar2[0x1636];
      sVar8 = psVar2[9];
      if ((int)sVar8 < (int)sVar12) {
LAB_00434541:
        psVar2[0x1636] = sVar8;
      }
      else {
        sVar12 = sVar12 + 10;
        if ((int)sVar12 <= (int)sVar8) {
          sVar8 = sVar8 - 9;
          goto LAB_00434541;
        }
      }
      sVar8 = 0;
      local_c = 64.0;
      local_4 = 0;
      local_8 = _DAT_00470c80 - (float)(int)psVar2[0x1636] * _DAT_00470ca0;
      if (0 < (int)psVar2[0x1a2]) {
        psVar3 = psVar2 + 0x185;
        do {
          iVar7 = FUN_004491c0(sVar12,(int)g_pGameStateManager,*psVar3);
          if (iVar7 == 0) {
            *psVar3 = 0;
          }
          if (((int)sVar8 < (int)psVar2[0x1636]) || ((int)(psVar2[0x1636] + 10) <= (int)sVar8)) {
            uVar6 = *(uint *)(iVar7 + 0x35c) & 0xfffffffd;
          }
          else {
            uVar6 = *(uint *)(iVar7 + 0x35c) | 2;
          }
          *(uint *)(iVar7 + 0x35c) = uVar6;
          if (sVar8 == psVar2[9]) {
            local_c = local_c - (float)_DAT_00470c98;
          }
          if (_DAT_00470c64 <= ABS(*(float *)(iVar7 + 0x338) - local_8)) {
            *(float *)(iVar7 + 0x334) = local_c;
            *(float *)(iVar7 + 0x338) = local_8;
            *(size_t *)(iVar7 + 0x33c) = local_4;
            sVar12 = local_4;
          }
          else {
            FUN_00434a80(&local_c,(undefined4 *)(iVar7 + 0x334),4,0);
            sVar12 = extraout_ECX_01;
          }
          if (sVar8 == psVar2[9]) {
            local_c = local_c + (float)_DAT_00470c98;
          }
          local_8 = local_8 + _DAT_00470ca0;
          psVar3 = psVar3 + 1;
          *(ushort *)(iVar7 + 0x304) = (sVar8 != psVar2[9]) + 2;
          sVar8 = sVar8 + 1;
        } while ((int)sVar8 < (int)psVar2[0x1a2]);
      }
      psVar2[0x1a5] = 0;
    }
    if ((_DAT_00474e36 & 0x1001) != 0) {
      psVar3 = psVar2 + 0x199;
      iVar7 = 8;
      do {
        iVar9 = FUN_004491c0(sVar12,(int)g_pGameStateManager,*psVar3);
        sVar12 = extraout_ECX_02;
        if (iVar9 != 0) {
          sVar12 = 3;
          *(undefined2 *)(iVar9 + 0x304) = 3;
          if (*(int *)(iVar9 + 0x18) == 0) {
            for (piVar10 = *(int **)(iVar9 + 0x14); piVar10 != (int *)0x0;
                piVar10 = (int *)piVar10[1]) {
              *(undefined2 *)(*piVar10 + 0x304) = 3;
            }
          }
        }
        psVar3 = psVar3 + 1;
        iVar7 = iVar7 + -1;
      } while (iVar7 != 0);
      psVar2[0x1a4] = psVar2[9];
      psVar2[0x1a3] = 0;
      if ((psVar2[0xb0] & 1) == 0) {
        psVar2[0xad] = 0;
        psVar2[0xac] = 0xfff0bdc1;
        psVar2[0xae] = 0;
        psVar2[0xaf] = (size_t)&DAT_00476f78;
        psVar2[0xb0] = psVar2[0xb0] | 1;
      }
      iVar7 = DAT_0047783c;
      psVar2[0xad] = 0;
      psVar2[0xae] = 0;
      psVar2[0xac] = 0xffffffff;
      sVar12 = psVar2[0x1a4];
      if ((*(char *)(sVar12 + 0x1d892 + iVar7) == '\0') && (psVar2[0x1a5] == 0)) {
        if (((byte)DAT_00491d78 & 0x10) == 0) {
          FUN_0043e460(sVar12,"dummy",3,0);
          psVar2[0x1a5] = 1;
          return 0;
        }
        FUN_0043e460(sVar12,"dummy",4,0);
        psVar2[0x1a5] = 1;
        return 0;
      }
      FUN_00420a90(0,(char *)(psVar2 + psVar2[9] * 0x10 + 0x1a6));
      uVar13 = extraout_ECX_03;
      if (((byte)DAT_00491d78 & 0x10) != 0) {
        FUN_0043e460(extraout_ECX_03,"dummy",4,0);
        uVar13 = extraout_ECX_04;
      }
      FUN_0043e460(uVar13,"dummy",2,0);
      *(undefined1 *)(DAT_0047783c + 0x1d892) = 1;
      psVar2[0x1a5] = 0;
      return 0;
    }
    if ((_DAT_00474e36 & 10) != 0) {
LAB_00434803:
      if ((void *)psVar2[0x16ab] != (void *)0x0) {
        _free((void *)psVar2[0x16ab]);
        psVar2[0x16ab] = 0;
      }
      psVar2[0x16ab] = 0;
      FUN_0044be70();
      iVar7 = 0;
      uVar13 = extraout_ECX_05;
      if (0 < (int)psVar2[0x1a2]) {
        do {
          FUN_00409e50(uVar13);
          iVar7 = iVar7 + 1;
          uVar13 = extraout_ECX_06;
        } while (iVar7 < (int)psVar2[0x1a2]);
      }
      pvVar4 = g_pGameStateManager;
      psVar3 = psVar2 + 0x199;
      param_1 = (size_t *)0x8;
LAB_00434870:
      sVar12 = *psVar3;
      if (sVar12 != 0) {
        for (piVar10 = *(int **)((int)pvVar4 + 0x72dad4); piVar10 != (int *)0x0;
            piVar10 = (int *)piVar10[1]) {
          if (*(size_t *)*piVar10 == sVar12) goto LAB_004348a6;
        }
        for (piVar10 = *(int **)((int)pvVar4 + 0x72dadc); piVar10 != (int *)0x0;
            piVar10 = (int *)piVar10[1]) {
          if (*(size_t *)*piVar10 == sVar12) goto LAB_004348a6;
        }
      }
      goto LAB_004348d4;
    }
    break;
  case 3:
    if (9 < (int)param_1[0xad]) {
      FUN_0042c6d0(this);
      FUN_0042c770(0x5a);
      FUN_0042c770(0x5b);
      FUN_0042c6d0(extraout_ECX_07);
      FUN_00409e50(extraout_ECX_08);
      FUN_0042c5c0(2);
      FUN_00420a90(0,"bgm/th10_02.wav");
      FUN_00420b10(this_01,0,0);
      FUN_0044be70();
    }
  }
  return 0;
LAB_004348a6:
  iVar7 = *piVar10;
  if ((iVar7 != 0) && (*(undefined2 *)(iVar7 + 0x304) = 1, *(int *)(iVar7 + 0x18) == 0)) {
    for (piVar10 = *(int **)(iVar7 + 0x14); piVar10 != (int *)0x0; piVar10 = (int *)piVar10[1]) {
      *(undefined2 *)(*piVar10 + 0x304) = 1;
    }
  }
LAB_004348d4:
  psVar3 = psVar3 + 1;
  param_1 = (size_t *)((int)param_1 + -1);
  if (param_1 == (size_t *)0x0) {
    FUN_0043dc90(&DAT_00492590,0);
    psVar2[8] = 3;
    if ((psVar2[0xb0] & 1) == 0) {
      psVar2[0xad] = 0;
      psVar2[0xac] = 0xfff0bdc1;
      psVar2[0xae] = 0;
      psVar2[0xaf] = (size_t)&DAT_00476f78;
      psVar2[0xb0] = psVar2[0xb0] | 1;
    }
    psVar2[0xad] = 0;
    psVar2[0xae] = 0;
    psVar2[0xac] = 0xffffffff;
    return 0;
  }
  goto LAB_00434870;
}

