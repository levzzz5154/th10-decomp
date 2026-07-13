/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x0040BD80
 * Tracking name: FUN_0040bd80
 * Ghidra name: FUN_0040bd80
 * Tracked span: 1600 bytes
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_0040bd80(undefined4 *param_1)

{
  float *pfVar1;
  int iVar2;
  char *pcVar3;
  undefined4 *puVar4;
  byte *pbVar5;
  uint uVar6;
  undefined4 uVar7;
  undefined4 extraout_ECX;
  undefined4 extraout_ECX_00;
  undefined4 extraout_ECX_01;
  undefined4 extraout_ECX_02;
  uint extraout_ECX_03;
  void *pvVar8;
  uint extraout_ECX_04;
  undefined4 extraout_ECX_05;
  int *piVar9;
  char *pcVar10;
  int iVar11;
  bool bVar12;
  ulonglong uVar13;
  undefined4 uVar14;
  COLORREF CVar15;
  
  uVar6 = param_1[0x1d];
  if ((uVar6 & 4) != 0) {
    return 0;
  }
  if (((((*(byte *)(DAT_00477700 + 0x20) & 1) == 0) && ((uVar6 & 2) == 0)) &&
      ((DAT_00474e30 & 0x100) != 0)) && ((uVar6 & 1) != 0)) {
    FUN_00405410((uint)*(ushort *)param_1[0x15]);
  }
  if ((int)(uint)*(ushort *)param_1[0x15] <= (int)param_1[7]) {
    do {
      pvVar8 = g_pGameStateManager;
      iVar11 = param_1[0x15];
      uVar6 = (uint)*(byte *)(iVar11 + 2);
      switch(uVar6) {
      case 0:
        return 0xffffffff;
      case 3:
        if (param_1[0x1e] == 0) {
          piVar9 = param_1 + 0x10;
          iVar11 = 5;
          uVar7 = 0;
          do {
            pvVar8 = g_pGameStateManager;
            iVar2 = FUN_004491c0(uVar7,(int)g_pGameStateManager,*piVar9);
            if (iVar2 == 0) {
              *piVar9 = 0;
            }
            FUN_00447a50(pvVar8,0xffffff," ");
            FUN_0040c4d0(extraout_ECX);
            pvVar8 = g_pGameStateManager;
            piVar9 = piVar9 + 1;
            iVar11 = iVar11 + -1;
            uVar7 = extraout_ECX_00;
          } while (iVar11 != 0);
          iVar11 = FUN_004491c0(param_1[0x10],(int)g_pGameStateManager,param_1[0x10]);
          if (iVar11 == 0) {
            param_1[0x10] = 0;
          }
          pcVar3 = FUN_00417010();
          FUN_00447a50(pvVar8,param_1[0x1f],pcVar3);
          FUN_0040c480(extraout_ECX_01);
          param_1[0x1e] = param_1[0x1e] + 1;
        }
        else {
          pcVar3 = FUN_00417010();
          CVar15 = param_1[0x1f];
          FUN_00449450(param_1[0x1e]);
          FUN_00447a50(g_pGameStateManager,CVar15,pcVar3);
          FUN_0040c480(extraout_ECX_02);
          iVar11 = param_1[0x1e];
          param_1[0x1e] = iVar11 + 1;
          if (4 < iVar11 + 1) {
            param_1[0x1e] = 0;
          }
        }
        break;
      case 4:
        iVar11 = 5;
        do {
          FUN_0040c4d0(uVar6);
          iVar11 = iVar11 + -1;
          uVar6 = extraout_ECX_03;
        } while (iVar11 != 0);
        break;
      case 5:
        if ((int)param_1[0xc] < 1) {
          FUN_00405410(*(int *)(iVar11 + 4));
        }
        FUN_0044bf40(-1.0);
        if (*(int *)(param_1[0x15] + 4) < 0) {
          FUN_00405410(999);
        }
        if (((_DAT_00474e36 & 0x1001) == 0) && (0 < (int)param_1[0xc])) {
          if ((*(byte *)(DAT_00477700 + 0x20) & 1) != 0) {
            return 0;
          }
          if ((DAT_00474e30 & 0x100) == 0) {
            return 0;
          }
          if ((int)param_1[0xc] % 6 != 0) {
            return 0;
          }
          FUN_00405410(0);
        }
        else {
          FUN_0043dc90(&DAT_00492590,0);
          FUN_00405410(0);
        }
        break;
      case 6:
        if ((int)param_1[0xc] < 1) {
          FUN_00405410(*(int *)(iVar11 + 4));
        }
        FUN_0044bf40(-1.0);
        if (((_DAT_00474e36 & 0x1001) == 0) && (0 < (int)param_1[0xc])) {
          if ((*(byte *)(DAT_00477700 + 0x20) & 1) != 0) {
            return 0;
          }
          if ((DAT_00474e30 & 0x100) == 0) {
            return 0;
          }
          if ((int)param_1[0xc] % 6 != 0) {
            return 0;
          }
        }
        else {
          FUN_0043dc90(&DAT_00492590,0);
        }
        FUN_00405410(0);
        param_1[0x1e] = 0;
        DAT_004918a4 = 0;
        break;
      case 7:
        FUN_0040c540();
        FUN_004477d0(extraout_ECX_05);
        param_1[0x1c] = param_1[0x15] + 8;
        param_1[0x1d] = param_1[0x1d] | 4;
        FUN_0044c1c0(param_1);
        param_1[0x15] = *(byte *)(param_1[0x15] + 3) + 4 + param_1[0x15];
        return 0;
      case 8:
        iVar11 = *(int *)(iVar11 + 4);
        FUN_004492a0(uVar6,(int)g_pGameStateManager,param_1[iVar11 + 0x24]);
        param_1[iVar11 + 0x24] = 0;
        puVar4 = (undefined4 *)
                 FUN_00448d00(param_1[*(int *)(param_1[0x15] + 8) + 0x20],
                              *(int *)(param_1[0x15] + 0xc),0xf);
        param_1[*(int *)(param_1[0x15] + 4) + 0x24] = *puVar4;
        break;
      case 9:
        param_1[0x1f] = *(undefined4 *)(iVar11 + 4);
        break;
      case 10:
        FUN_00420a90(0,(char *)(iVar11 + 4));
        pvVar8 = (void *)0x10;
        bVar12 = true;
        pcVar3 = (char *)(param_1[0x15] + 4);
        pcVar10 = "bgm/th10_13.wav";
        do {
          if (pvVar8 == (void *)0x0) break;
          pvVar8 = (void *)((int)pvVar8 + -1);
          bVar12 = *pcVar3 == *pcVar10;
          pcVar3 = pcVar3 + 1;
          pcVar10 = pcVar10 + 1;
        } while (bVar12);
        if (bVar12) {
          FUN_00420b10(pvVar8,0,0xf);
        }
        else {
          FUN_00420b10(pvVar8,0,0x10);
        }
        break;
      case 0xb:
        FUN_00420c30();
        param_1[0x1d] = param_1[0x1d] & 0xfffffffe;
        break;
      case 0xc:
        piVar9 = param_1 + 0x10;
        iVar11 = 5;
        do {
          FUN_004492a0(uVar6,(int)pvVar8,*piVar9);
          *piVar9 = 0;
          piVar9 = piVar9 + 1;
          iVar11 = iVar11 + -1;
          uVar6 = extraout_ECX_04;
        } while (iVar11 != 0);
        pbVar5 = FUN_0040b480(DAT_00477700);
        if (pbVar5 == (byte *)0x0) {
          return 0xffffffff;
        }
        puVar4 = param_1;
        for (iVar11 = 0x3b; iVar11 != 0; iVar11 = iVar11 + -1) {
          *puVar4 = 0;
          puVar4 = puVar4 + 1;
        }
        param_1[0x15] = pbVar5 + *(int *)(pbVar5 + 4);
        FUN_00405410(0);
        FUN_00405410(0);
        FUN_00405410(0);
        param_1[0x1f] = 0xffffff;
        param_1[0x1d] = param_1[0x1d] | 2;
        goto LAB_0040c26d;
      case 0xd:
        uVar7 = *(undefined4 *)(iVar11 + 4);
        uVar14 = 0;
        goto LAB_0040c255;
      case 0xe:
        uVar7 = *(undefined4 *)(iVar11 + 4);
        uVar14 = 5;
LAB_0040c255:
        FUN_0043c8b0(uVar14,uVar7,0,0,0);
        break;
      case 0xf:
        if (DAT_00474c74 == 1) {
          FUN_00449630(*(undefined4 *)(iVar11 + 4));
          puVar4 = (undefined4 *)
                   FUN_00448d00(param_1[*(int *)(param_1[0x15] + 8) + 0x20],
                                *(int *)(param_1[0x15] + 0xc),0xf);
          param_1[*(int *)(param_1[0x15] + 4) + 0x24] = *puVar4;
        }
        break;
      case 0x10:
        if (DAT_00474c74 == 2) {
          FUN_00449630(uVar6);
          puVar4 = (undefined4 *)
                   FUN_00448d00(param_1[*(int *)(param_1[0x15] + 8) + 0x20],
                                *(int *)(param_1[0x15] + 0xc),0xf);
          param_1[*(int *)(param_1[0x15] + 4) + 0x24] = *puVar4;
        }
        break;
      case 0x11:
        if (DAT_00474c74 == 3) {
          FUN_00449630(*(undefined4 *)(iVar11 + 4));
          puVar4 = (undefined4 *)
                   FUN_00448d00(param_1[*(int *)(param_1[0x15] + 8) + 0x20],
                                *(int *)(param_1[0x15] + 0xc),0xf);
          param_1[*(int *)(param_1[0x15] + 4) + 0x24] = *puVar4;
        }
      }
      param_1[0x15] = *(byte *)(param_1[0x15] + 3) + 4 + param_1[0x15];
LAB_0040c26d:
    } while ((int)(uint)*(ushort *)param_1[0x15] <= (int)param_1[7]);
  }
  pfVar1 = (float *)param_1[9];
  param_1[6] = param_1[7];
  if ((_DAT_00470b68 < *pfVar1) && (*pfVar1 < _DAT_00470b64)) {
    param_1[8] = (float)param_1[8] + _DAT_00470afc;
    param_1[7] = param_1[7] + 1;
    return 0;
  }
  param_1[8] = *pfVar1 + (float)param_1[8];
  uVar13 = FUN_00463b2c();
  param_1[7] = (int)uVar13;
  return 0;
}

