/* Raw Ghidra reference; not compilable reconstruction. Address: 00432CB0 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __thiscall FUN_00432cb0(void *this,int param_1)

{
  undefined *puVar1;
  int *piVar2;
  char cVar3;
  undefined4 *puVar4;
  uint uVar5;
  undefined4 uVar6;
  char *pcVar7;
  void *this_00;
  undefined4 extraout_ECX;
  char *pcVar8;
  undefined4 extraout_ECX_00;
  undefined4 extraout_ECX_01;
  char *pcVar9;
  bool bVar10;
  int iVar11;
  
  switch(*(undefined4 *)(param_1 + 0x20)) {
  case 0:
    *(undefined4 *)(param_1 + 0x2c) = 0x1e;
    FUN_00420a90(0,"bgm/th10_17.wav");
    FUN_00420b10(this_00,0,0x11);
    iVar11 = FUN_004491c0(extraout_ECX,(int)g_pGameStateManager,*(int *)(param_1 + 0x43c));
    if (iVar11 == 0) {
      FUN_0042c670(param_1);
      puVar4 = (undefined4 *)FUN_00448d00(*(undefined4 *)((int)g_pGameThread + 0x8994),8,0xf);
      *(undefined4 *)(param_1 + 0x5d0) = *puVar4;
    }
    FUN_0042c670(param_1);
    FUN_0042c620(1);
    FUN_0042c670(param_1);
    FUN_0042c670(param_1);
    FUN_0042c670(param_1);
    DAT_00474c7c = 8;
    DAT_00474c80 = 8;
    DAT_00477848 = &PTR_DAT_00474908;
    uVar5 = FUN_00421fa0();
    DAT_00477848 = (undefined **)&DAT_00474788;
    DAT_00474c7c = 0;
    DAT_00474c80 = 0;
    if ((int)uVar5 < 0) {
      uVar5 = *(uint *)(param_1 + 0x2c);
      if (uVar5 == 0) {
        *(undefined4 *)(param_1 + 0x24) = 0xffffffff;
      }
      else if (uVar5 < 0x80000000) {
        *(undefined4 *)(param_1 + 0x24) = 0;
      }
      else {
        *(uint *)(param_1 + 0x24) = uVar5 - 1;
      }
      *(undefined4 *)(param_1 + 0x58ec) = 1;
    }
    else {
      FUN_00405410(0);
      *(undefined4 *)(param_1 + 0xf4) = 1;
      FUN_0040ad20(uVar5,(uint *)(param_1 + 0x24));
      iVar11 = *(int *)(param_1 + 0x58fc);
      piVar2 = (int *)(param_1 + 0x58f4);
      if (iVar11 == 0) {
        *piVar2 = 0;
      }
      else if (iVar11 < 1) {
        *piVar2 = iVar11 + -1;
      }
      else {
        *piVar2 = 0;
      }
      pcVar7 = PTR_s_ABCDEFGHIJKLMNOPQRSTUVWXYZabcdef_004746d8;
      do {
        cVar3 = *pcVar7;
        pcVar7 = pcVar7 + 1;
      } while (cVar3 != '\0');
      *(int *)(param_1 + 0x58fc) =
           (int)pcVar7 - (int)(PTR_s_ABCDEFGHIJKLMNOPQRSTUVWXYZabcdef_004746d8 + 1);
      pcVar7 = (char *)(DAT_0047783c + 0x1d878);
      *(undefined4 *)(param_1 + 0x59c4) = 1;
      iVar11 = (param_1 + 0x58dc) - (int)pcVar7;
      do {
        cVar3 = *pcVar7;
        pcVar7[iVar11] = cVar3;
        pcVar7 = pcVar7 + 1;
      } while (cVar3 != '\0');
      iVar11 = 9;
      bVar10 = true;
      pcVar7 = (char *)(param_1 + 0x58dc);
      pcVar8 = "        ";
      do {
        if (iVar11 == 0) break;
        iVar11 = iVar11 + -1;
        bVar10 = *pcVar7 == *pcVar8;
        pcVar7 = pcVar7 + 1;
        pcVar8 = pcVar8 + 1;
      } while (bVar10);
      if (!bVar10) {
        FUN_0044bea0(-1);
      }
      iVar11 = 8;
      do {
        if (*(char *)(iVar11 + 0x58db + param_1) != ' ') break;
        iVar11 = iVar11 + -1;
      } while (0 < iVar11);
      *(int *)(param_1 + 0x58e8) = iVar11;
      *(undefined4 *)(param_1 + 0x58ec) = 0;
    }
  case 1:
    if (6 < *(int *)(param_1 + 0x2b4)) {
      FUN_0042c620(2);
      return 1;
    }
    break;
  case 2:
    if (*(int *)(param_1 + 0x58ec) == 0) {
      piVar2 = (int *)(param_1 + 0x58f4);
      *(undefined4 *)(param_1 + 0x58f8) = *(undefined4 *)(param_1 + 0x58f4);
      uVar6 = FUN_0040ace0(0x474e30);
      if ((short)uVar6 != 0) {
        FUN_0044bea0(-0xd);
      }
      uVar6 = FUN_0040ace0(0x474e30);
      if ((short)uVar6 != 0) {
        FUN_0044bea0(0xd);
      }
      uVar6 = FUN_0040ace0(0x474e30);
      if ((short)uVar6 != 0) {
        if (*piVar2 % 0xd == 0) {
          iVar11 = 0xc;
        }
        else {
          iVar11 = -1;
        }
        FUN_0044bea0(iVar11);
      }
      uVar6 = FUN_0040ace0(0x474e30);
      if ((short)uVar6 != 0) {
        if (*piVar2 % 0xd == 0xc) {
          iVar11 = -0xc;
        }
        else {
          iVar11 = 1;
        }
        FUN_0044bea0(iVar11);
      }
      if (*(int *)(param_1 + 0x58f8) != *piVar2) {
        FUN_0043dc90(&DAT_00492590,0);
      }
    }
    iVar11 = DAT_0047783c;
    if ((_DAT_00474e36 & 0x1001) != 0) {
      if (*(int *)(param_1 + 0x58ec) == 0) {
        puVar1 = PTR_s_ABCDEFGHIJKLMNOPQRSTUVWXYZabcdef_004746d8 + 1;
        pcVar7 = PTR_s_ABCDEFGHIJKLMNOPQRSTUVWXYZabcdef_004746d8;
        do {
          cVar3 = *pcVar7;
          pcVar7 = pcVar7 + 1;
        } while (cVar3 != '\0');
        pcVar8 = *(char **)(param_1 + 0x58f4);
        if ((int)pcVar8 < (int)(pcVar7 + (-3 - (int)puVar1))) {
          iVar11 = *(int *)(param_1 + 0x58e8);
          if (iVar11 < 8) {
            *(undefined *)(iVar11 + 0x58dc + param_1) =
                 PTR_s_ABCDEFGHIJKLMNOPQRSTUVWXYZabcdef_004746d8[(int)pcVar8];
LAB_00433056:
            iVar11 = *(int *)(param_1 + 0x58e8) + 1;
            *(int *)(param_1 + 0x58e8) = iVar11;
            if (7 < iVar11) {
              FUN_0040ad20((uint)(pcVar7 + (-1 - (int)puVar1)),(uint *)(param_1 + 0x58f4));
            }
          }
          else {
            *(undefined *)(iVar11 + 0x58db + param_1) =
                 PTR_s_ABCDEFGHIJKLMNOPQRSTUVWXYZabcdef_004746d8[(int)pcVar8];
          }
        }
        else if (pcVar8 == pcVar7 + (-3 - (int)puVar1)) {
          iVar11 = *(int *)(param_1 + 0x58e8);
          if (iVar11 < 8) {
            *(undefined1 *)(iVar11 + 0x58dc + param_1) = 0x20;
            goto LAB_00433056;
          }
          *(undefined1 *)(iVar11 + 0x58db + param_1) = 0x20;
        }
        else if (pcVar8 == pcVar7 + (-2 - (int)puVar1)) {
          iVar11 = *(int *)(param_1 + 0x58e8);
          if (iVar11 == 0) {
            return 1;
          }
          *(int *)(param_1 + 0x58e8) = iVar11 + -1;
          *(undefined1 *)(iVar11 + 0x58db + param_1) = 0x20;
        }
        else if (pcVar8 == pcVar7 + (-1 - (int)puVar1)) {
          pcVar7 = (char *)(param_1 + 0x58dc);
          pcVar8 = (char *)((DAT_00474c6c + DAT_00474c68 * 3) * 0x437c + DAT_0047783c + 0x1e +
                           (*(int *)(param_1 + 0x24) + DAT_00474c74 * 10) * 0x18);
          pcVar9 = pcVar7;
          do {
            cVar3 = *pcVar9;
            pcVar9 = pcVar9 + 1;
            *pcVar8 = cVar3;
            pcVar8 = pcVar8 + 1;
          } while (cVar3 != '\0');
          iVar11 = (iVar11 + 0x1d878) - (int)pcVar7;
          do {
            cVar3 = *pcVar7;
            pcVar7[iVar11] = cVar3;
            pcVar7 = pcVar7 + 1;
          } while (cVar3 != '\0');
          goto LAB_0043310e;
        }
      }
      else {
LAB_0043310e:
        FUN_0042c620(3);
      }
      FUN_0043dc90(&DAT_00492590,0);
    }
    if ((_DAT_00474e36 & 10) != 0) {
      if (*(int *)(param_1 + 0x58ec) != 0) {
        FUN_0042c620(3);
        FUN_0043dc90(&DAT_00492590,0);
        return 1;
      }
      if (*(int *)(param_1 + 0x58e8) != 0) {
        FUN_0043dc90(&DAT_00492590,0);
        iVar11 = *(int *)(param_1 + 0x58e8);
        *(int *)(param_1 + 0x58e8) = iVar11 + -1;
        *(undefined1 *)(iVar11 + 0x58db + param_1) = 0x20;
        return 1;
      }
    }
    break;
  case 3:
    if (5 < *(int *)(param_1 + 0x2b4)) {
      FUN_0042c6d0(this);
      FUN_0042c6d0(extraout_ECX_00);
      FUN_0042c6d0(DAT_00474c6c);
      FUN_0042c6d0(extraout_ECX_01);
      FUN_0042c5c0(0x10);
    }
  }
  return 1;
}

