/* Raw Ghidra reference; not compilable reconstruction. Address: 004236F0 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_004236f0(int param_1)

{
  undefined *puVar1;
  uint *puVar2;
  char cVar3;
  void *_Memory;
  undefined4 *puVar4;
  undefined4 *puVar5;
  undefined4 uVar6;
  char *pcVar7;
  undefined4 extraout_ECX;
  undefined4 extraout_ECX_00;
  int extraout_ECX_01;
  undefined4 extraout_ECX_02;
  undefined4 extraout_ECX_03;
  undefined4 extraout_ECX_04;
  undefined4 extraout_ECX_05;
  undefined4 extraout_ECX_06;
  undefined4 extraout_ECX_07;
  char *pcVar8;
  undefined4 extraout_ECX_08;
  undefined4 extraout_ECX_09;
  undefined4 extraout_ECX_10;
  undefined4 extraout_ECX_11;
  char *pcVar9;
  int iVar10;
  int *piVar11;
  bool bVar12;
  int iVar13;
  int local_4c [2];
  char local_44 [64];
  uint local_4;
  
  local_4 = DAT_00473660 ^ (uint)local_4c;
  switch(*(undefined4 *)(param_1 + 4)) {
  case 6:
    if ((9 < *(int *)(param_1 + 0x14)) && ((_DAT_00474e36 & 0x1001) != 0)) {
      FUN_0043dc90(&DAT_00492590,0);
      *(undefined4 *)(param_1 + 4) = 7;
      FUN_00449470(extraout_ECX);
      FUN_00405410(0);
      return;
    }
    break;
  case 7:
    if (9 < *(int *)(param_1 + 0x14)) {
      FUN_00421f60();
      iVar13 = DAT_00474c44;
      if ((DAT_00474ca0 & 0x10) == 0) {
        FUN_00423570(param_1);
        FUN_00405410(0);
        iVar13 = extraout_ECX_01;
        if (*(int *)(param_1 + 0x1e8) == 0) {
          *(undefined4 *)(param_1 + 4) = 0xc;
          FUN_004495e0();
          return;
        }
      }
      else {
        piVar11 = (int *)((DAT_00474c6c + DAT_00474c68 * 3) * 0x437c + DAT_0047783c + 0x4dc +
                         (DAT_00474c7c + DAT_00474c74 * 6) * 8);
        if (*piVar11 < DAT_00474c44) {
          *piVar11 = DAT_00474c44;
        }
      }
      *(undefined4 *)(param_1 + 4) = 8;
      *(undefined4 *)(param_1 + 0x2c) = 3;
      *(undefined4 *)(param_1 + 0xf4) = 1;
      iVar10 = *(int *)(param_1 + 0x2c);
      if (iVar10 == 0) {
        *(undefined4 *)(param_1 + 0x24) = 2;
      }
      else if (iVar10 < 3) {
        *(int *)(param_1 + 0x24) = iVar10 + -1;
      }
      else {
        *(undefined4 *)(param_1 + 0x24) = 2;
      }
      FUN_0040c4d0(iVar13);
      FUN_00449470(extraout_ECX_00);
      return;
    }
    break;
  case 8:
    uVar6 = *(undefined4 *)(param_1 + 0x24);
    *(undefined4 *)(param_1 + 0x28) = uVar6;
    if (((_DAT_00474e36 & 0x10) != 0) || ((DAT_00474e34 & 0x10) != 0)) {
      FUN_0044bea0(-1);
      uVar6 = extraout_ECX_02;
    }
    if (((_DAT_00474e36 & 0x20) != 0) || ((DAT_00474e34 & 0x20) != 0)) {
      FUN_0044bea0(1);
      uVar6 = extraout_ECX_03;
    }
    if (*(int *)(param_1 + 0x28) != *(int *)(param_1 + 0x24)) {
      FUN_00449470(uVar6);
      FUN_0043dc90(&DAT_00492590,0);
      uVar6 = extraout_ECX_04;
    }
    if ((_DAT_00474e36 & 0x1001) != 0) {
      FUN_004497d0(uVar6);
      FUN_004243f0(extraout_ECX_05);
      FUN_0043dc90(&DAT_00492590,0);
      *(undefined4 *)(param_1 + 4) = 0xd;
      FUN_00405410(0);
      FUN_00421f60();
      if (*(int *)(param_1 + 0x24) == 1) {
        *(undefined4 *)(param_1 + 4) = 10;
        FUN_00405410(0);
        FUN_004495e0();
        piVar11 = (int *)FUN_0044be20();
        iVar10 = 1;
        *(undefined4 *)(param_1 + 0x2c) = 0x19;
        *(undefined4 *)(param_1 + 0xf4) = 1;
        iVar13 = piVar11[2];
        if (iVar13 == 0) {
          *piVar11 = 0;
        }
        else if (iVar13 < 1) {
          *piVar11 = iVar13 + -1;
        }
        else {
          *piVar11 = 0;
        }
        puVar5 = (undefined4 *)(param_1 + 0x1ec);
        do {
          _sprintf(local_44,"th10_%.2d.rpy",iVar10);
          puVar4 = FUN_004296f0(local_44);
          *puVar5 = puVar4;
          iVar10 = iVar10 + 1;
          puVar5 = puVar5 + 1;
        } while (iVar10 < 0x1a);
      }
      else if (*(int *)(param_1 + 0x24) == 2) {
        *(undefined4 *)(param_1 + 4) = 0xd;
        FUN_00405410(0);
        FUN_0043dc90(&DAT_00492590,0);
      }
    }
    if (((_DAT_00474e36 & 10) != 0) &&
       (FUN_0043dc90(&DAT_00492590,0), *(int *)(param_1 + 0x24) != 2)) {
      iVar13 = *(int *)(param_1 + 0x2c);
      if (iVar13 == 0) {
        *(undefined4 *)(param_1 + 0x24) = 2;
      }
      else if (iVar13 < 3) {
        *(int *)(param_1 + 0x24) = iVar13 + -1;
      }
      else {
        *(undefined4 *)(param_1 + 0x24) = 2;
      }
      FUN_00449470(extraout_ECX_06);
      return;
    }
    break;
  case 9:
    break;
  case 10:
    if (9 < *(int *)(param_1 + 0x14)) {
      *(undefined4 *)(param_1 + 0x28) = *(undefined4 *)(param_1 + 0x24);
      uVar6 = FUN_0040ace0(0x474e30);
      if ((short)uVar6 != 0) {
        FUN_0044bea0(-1);
      }
      uVar6 = FUN_0040ace0(0x474e30);
      if ((short)uVar6 != 0) {
        FUN_0044bea0(1);
      }
      if (*(int *)(param_1 + 0x28) != *(int *)(param_1 + 0x24)) {
        FUN_0043dc90(&DAT_00492590,0);
      }
      if ((_DAT_00474e36 & 0x1001) != 0) {
        *(undefined4 *)(param_1 + 4) = 0xb;
        FUN_00405410(0);
        iVar13 = *(int *)(param_1 + 0x104);
        piVar11 = (int *)(param_1 + 0xfc);
        if (iVar13 == 0) {
          *piVar11 = 0;
        }
        else if (iVar13 < 1) {
          *piVar11 = iVar13 + -1;
        }
        else {
          *piVar11 = 0;
        }
        pcVar7 = PTR_s_ABCDEFGHIJKLMNOPQRSTUVWXYZabcdef_004746d8;
        do {
          cVar3 = *pcVar7;
          pcVar7 = pcVar7 + 1;
        } while (cVar3 != '\0');
        *(int *)(param_1 + 0x104) =
             (int)pcVar7 - (int)(PTR_s_ABCDEFGHIJKLMNOPQRSTUVWXYZabcdef_004746d8 + 1);
        *(undefined4 *)(param_1 + 0x1cc) = 1;
        if ((*(int *)(param_1 + 0x1e4) == 0) || ((DAT_00474ca0 & 0x10) != 0)) {
          piVar11 = (int *)(DAT_00477838 + 0x18);
          FID_conflict___time32((__time32_t *)(*(int *)(DAT_00477838 + 0x18) + 0xc));
          *(int *)(*piVar11 + 0x5c) = DAT_00474c7c;
        }
        else {
          piVar11 = (int *)(DAT_00477838 + 0x18);
          FID_conflict___time32((__time32_t *)(*(int *)(DAT_00477838 + 0x18) + 0xc));
          *(undefined4 *)(*piVar11 + 0x5c) = 8;
        }
        pcVar7 = (char *)(DAT_0047783c + 0x1d878);
        iVar13 = (param_1 + 0x2b4) - (int)pcVar7;
        do {
          cVar3 = *pcVar7;
          pcVar7[iVar13] = cVar3;
          pcVar7 = pcVar7 + 1;
        } while (cVar3 != '\0');
        iVar13 = 9;
        bVar12 = true;
        *(undefined4 *)(param_1 + 0x1e0) = 0;
        pcVar7 = (char *)(param_1 + 0x2b4);
        pcVar8 = "        ";
        do {
          if (iVar13 == 0) break;
          iVar13 = iVar13 + -1;
          bVar12 = *pcVar7 == *pcVar8;
          pcVar7 = pcVar7 + 1;
          pcVar8 = pcVar8 + 1;
        } while (bVar12);
        if (!bVar12) {
          FUN_0044bea0(-1);
        }
        iVar13 = 8;
        do {
          if (*(char *)(iVar13 + 0x2b3 + param_1) != ' ') break;
          iVar13 = iVar13 + -1;
        } while (0 < iVar13);
        *(int *)(param_1 + 0x1e0) = iVar13;
        goto LAB_00423bfa;
      }
      if ((_DAT_00474e36 & 10) != 0) {
        *(undefined4 *)(param_1 + 4) = 8;
        FUN_00405410(0);
        FUN_00449590();
        FUN_0044be70();
        *(undefined4 *)(param_1 + 0x2c) = 3;
        *(undefined4 *)(param_1 + 0xf4) = 1;
        FUN_00449470(extraout_ECX_07);
        puVar5 = (undefined4 *)(param_1 + 0x1ec);
        local_4c[0] = 0x19;
        do {
          _Memory = (void *)*puVar5;
          if (_Memory != (void *)0x0) {
            FUN_004294a0((int)_Memory);
            _free(_Memory);
          }
          *puVar5 = 0;
          puVar5 = puVar5 + 1;
          local_4c[0] = local_4c[0] + -1;
        } while (local_4c[0] != 0);
        *(undefined4 *)(param_1 + 4) = 8;
        FUN_00405410(0);
LAB_00423cb9:
        FUN_0043dc90(&DAT_00492590,0);
        return;
      }
    }
    break;
  case 0xb:
    if (9 < *(int *)(param_1 + 0x14)) {
      puVar2 = (uint *)(param_1 + 0xfc);
      *(undefined4 *)(param_1 + 0x100) = *(undefined4 *)(param_1 + 0xfc);
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
        if ((int)*puVar2 % 0xd == 0) {
          iVar13 = 0xc;
        }
        else {
          iVar13 = -1;
        }
        FUN_0044bea0(iVar13);
      }
      uVar6 = FUN_0040ace0(0x474e30);
      if ((short)uVar6 != 0) {
        if ((int)*puVar2 % 0xd == 0xc) {
          iVar13 = -0xc;
        }
        else {
          iVar13 = 1;
        }
        FUN_0044bea0(iVar13);
      }
      if (*(uint *)(param_1 + 0x100) != *puVar2) {
        FUN_0043dc90(&DAT_00492590,0);
      }
      if ((_DAT_00474e36 & 0x1001) != 0) {
        puVar1 = PTR_s_ABCDEFGHIJKLMNOPQRSTUVWXYZabcdef_004746d8 + 1;
        pcVar7 = PTR_s_ABCDEFGHIJKLMNOPQRSTUVWXYZabcdef_004746d8;
        do {
          cVar3 = *pcVar7;
          pcVar7 = pcVar7 + 1;
        } while (cVar3 != '\0');
        pcVar8 = (char *)*puVar2;
        if ((int)pcVar8 < (int)(pcVar7 + (-3 - (int)puVar1))) {
          iVar13 = *(int *)(param_1 + 0x1e0);
          if (iVar13 < 8) {
            *(undefined *)(iVar13 + 0x2b4 + param_1) =
                 PTR_s_ABCDEFGHIJKLMNOPQRSTUVWXYZabcdef_004746d8[(int)pcVar8];
LAB_00423e68:
            iVar13 = *(int *)(param_1 + 0x1e0) + 1;
            *(int *)(param_1 + 0x1e0) = iVar13;
            if (7 < iVar13) {
              FUN_0040ad20((uint)(pcVar7 + (-1 - (int)puVar1)),puVar2);
            }
          }
          else {
            *(undefined *)(iVar13 + 0x2b3 + param_1) =
                 PTR_s_ABCDEFGHIJKLMNOPQRSTUVWXYZabcdef_004746d8[(int)pcVar8];
          }
        }
        else if (pcVar8 == pcVar7 + (-3 - (int)puVar1)) {
          iVar13 = *(int *)(param_1 + 0x1e0);
          if (iVar13 < 8) {
            *(undefined1 *)(iVar13 + 0x2b4 + param_1) = 0x20;
            goto LAB_00423e68;
          }
          *(undefined1 *)(iVar13 + 0x2b3 + param_1) = 0x20;
        }
        else {
          if (pcVar8 == pcVar7 + (-2 - (int)puVar1)) {
            iVar13 = *(int *)(param_1 + 0x1e0);
            if (iVar13 != 0) {
              *(int *)(param_1 + 0x1e0) = iVar13 + -1;
              *(undefined1 *)(iVar13 + 0x2b3 + param_1) = 0x20;
              goto LAB_00423cb9;
            }
            break;
          }
          if (pcVar8 == pcVar7 + (-1 - (int)puVar1)) {
            FUN_0043dc90(&DAT_00492590,0);
            _sprintf(local_44,"th10_%.2d.rpy",*(int *)(param_1 + 0x24) + 1);
            DestroyPlatformResource();
            pcVar7 = (char *)(param_1 + 0x2b4);
            FUN_00429b60(DAT_00477838,local_44,pcVar7);
            iVar13 = *(int *)(param_1 + 0x24);
            puVar5 = FUN_004296f0(local_44);
            *(undefined4 **)(param_1 + 0x1ec + iVar13 * 4) = puVar5;
            *(undefined4 *)(param_1 + 4) = 10;
            FUN_00405410(0);
            iVar13 = (DAT_0047783c + 0x1d878) - (int)pcVar7;
            do {
              cVar3 = *pcVar7;
              pcVar7[iVar13] = cVar3;
              pcVar7 = pcVar7 + 1;
            } while (cVar3 != '\0');
            return;
          }
        }
        FUN_0043dc90(&DAT_00492590,0);
      }
      if ((_DAT_00474e36 & 10) != 0) {
        FUN_0043dc90(&DAT_00492590,0);
        iVar13 = *(int *)(param_1 + 0x1e0);
        if (iVar13 != 0) {
          *(int *)(param_1 + 0x1e0) = iVar13 + -1;
          *(undefined1 *)(iVar13 + 0x2b3 + param_1) = 0x20;
          return;
        }
        *(undefined4 *)(param_1 + 4) = 10;
        FUN_00405410(0);
        return;
      }
    }
    break;
  case 0xc:
    if (9 < *(int *)(param_1 + 0x14)) {
      if (*(int *)(param_1 + 0x1e8) == 0) {
        piVar11 = (int *)(param_1 + 0xfc);
        *(undefined4 *)(param_1 + 0x100) = *(undefined4 *)(param_1 + 0xfc);
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
          if (*piVar11 % 0xd == 0) {
            iVar13 = 0xc;
          }
          else {
            iVar13 = -1;
          }
          FUN_0044bea0(iVar13);
        }
        uVar6 = FUN_0040ace0(0x474e30);
        if ((short)uVar6 != 0) {
          if (*piVar11 % 0xd == 0xc) {
            iVar13 = -0xc;
          }
          else {
            iVar13 = 1;
          }
          FUN_0044bea0(iVar13);
        }
        if (*(int *)(param_1 + 0x100) != *piVar11) {
          FUN_0043dc90(&DAT_00492590,0);
        }
      }
      iVar13 = DAT_0047783c;
      if ((_DAT_00474e36 & 0x1001) != 0) {
        if (*(int *)(param_1 + 0x1e8) == 0) {
          puVar1 = PTR_s_ABCDEFGHIJKLMNOPQRSTUVWXYZabcdef_004746d8 + 1;
          pcVar7 = PTR_s_ABCDEFGHIJKLMNOPQRSTUVWXYZabcdef_004746d8;
          do {
            cVar3 = *pcVar7;
            pcVar7 = pcVar7 + 1;
          } while (cVar3 != '\0');
          pcVar8 = *(char **)(param_1 + 0xfc);
          if ((int)pcVar8 < (int)(pcVar7 + (-3 - (int)puVar1))) {
            iVar13 = *(int *)(param_1 + 0x1e0);
            if (iVar13 < 8) {
              *(undefined *)(iVar13 + 0x2b4 + param_1) =
                   PTR_s_ABCDEFGHIJKLMNOPQRSTUVWXYZabcdef_004746d8[(int)pcVar8];
LAB_004240ef:
              iVar13 = *(int *)(param_1 + 0x1e0) + 1;
              *(int *)(param_1 + 0x1e0) = iVar13;
              if (7 < iVar13) {
                FUN_0040ad20((uint)(pcVar7 + (-1 - (int)puVar1)),(uint *)(param_1 + 0xfc));
              }
            }
            else {
              *(undefined *)(iVar13 + 0x2b3 + param_1) =
                   PTR_s_ABCDEFGHIJKLMNOPQRSTUVWXYZabcdef_004746d8[(int)pcVar8];
            }
          }
          else if (pcVar8 == pcVar7 + (-3 - (int)puVar1)) {
            iVar13 = *(int *)(param_1 + 0x1e0);
            if (iVar13 < 8) {
              *(undefined1 *)(iVar13 + 0x2b4 + param_1) = 0x20;
              goto LAB_004240ef;
            }
            *(undefined1 *)(iVar13 + 0x2b3 + param_1) = 0x20;
          }
          else if (pcVar8 == pcVar7 + (-2 - (int)puVar1)) {
            iVar13 = *(int *)(param_1 + 0x1e0);
            if (iVar13 == 0) break;
            *(int *)(param_1 + 0x1e0) = iVar13 + -1;
            *(undefined1 *)(iVar13 + 0x2b3 + param_1) = 0x20;
          }
          else if (pcVar8 == pcVar7 + (-1 - (int)puVar1)) {
            pcVar7 = (char *)(param_1 + 0x2b4);
            pcVar8 = (char *)((DAT_00474c6c + DAT_00474c68 * 3) * 0x437c + DAT_0047783c + 0x1e +
                             (*(int *)(param_1 + 0x24) + DAT_00474c74 * 10) * 0x18);
            pcVar9 = pcVar7;
            do {
              cVar3 = *pcVar9;
              pcVar9 = pcVar9 + 1;
              *pcVar8 = cVar3;
              pcVar8 = pcVar8 + 1;
            } while (cVar3 != '\0');
            iVar13 = (iVar13 + 0x1d878) - (int)pcVar7;
            do {
              cVar3 = *pcVar7;
              pcVar7[iVar13] = cVar3;
              pcVar7 = pcVar7 + 1;
            } while (cVar3 != '\0');
            FUN_00449590();
            *(undefined4 *)(param_1 + 4) = 8;
            *(undefined4 *)(param_1 + 0x2c) = 3;
            *(undefined4 *)(param_1 + 0xf4) = 1;
            iVar13 = *(int *)(param_1 + 0x2c);
            if (iVar13 == 0) {
              *(undefined4 *)(param_1 + 0x24) = 0;
            }
            else if (iVar13 < 1) {
              *(int *)(param_1 + 0x24) = iVar13 + -1;
            }
            else {
              *(undefined4 *)(param_1 + 0x24) = 0;
            }
            FUN_0040c4d0(extraout_ECX_08);
            FUN_00449470(extraout_ECX_09);
          }
          FUN_0043dc90(&DAT_00492590,0);
        }
        else {
          FUN_00449590();
          *(undefined4 *)(param_1 + 4) = 8;
          *(undefined4 *)(param_1 + 0x2c) = 3;
          *(undefined4 *)(param_1 + 0xf4) = 1;
          iVar13 = *(int *)(param_1 + 0x2c);
          if (iVar13 == 0) {
            *(undefined4 *)(param_1 + 0x24) = 0;
          }
          else if (iVar13 < 1) {
            *(int *)(param_1 + 0x24) = iVar13 + -1;
          }
          else {
            *(undefined4 *)(param_1 + 0x24) = 0;
          }
          FUN_0040c4d0(extraout_ECX_10);
          FUN_00449470(extraout_ECX_11);
        }
      }
      if ((_DAT_00474e36 & 10) != 0) {
        if (*(int *)(param_1 + 0x24) < 0) {
          *(undefined4 *)(param_1 + 4) = 8;
          *(undefined4 *)(param_1 + 0x2c) = 3;
          iVar13 = *(int *)(param_1 + 0x2c);
          if (iVar13 == 0) {
            *(undefined4 *)(param_1 + 0x24) = 0;
            FUN_00405410(0);
          }
          else if (iVar13 < 1) {
            *(int *)(param_1 + 0x24) = iVar13 + -1;
            FUN_00405410(0);
          }
          else {
            *(undefined4 *)(param_1 + 0x24) = 0;
            FUN_00405410(0);
          }
LAB_00423bfa:
          FUN_0043dc90(&DAT_00492590,0);
          return;
        }
        if (*(int *)(param_1 + 0x1e0) != 0) {
          FUN_0043dc90(&DAT_00492590,0);
          iVar13 = *(int *)(param_1 + 0x1e0);
          *(int *)(param_1 + 0x1e0) = iVar13 + -1;
          *(undefined1 *)(iVar13 + 0x2b3 + param_1) = 0x20;
          return;
        }
      }
    }
    break;
  case 0xd:
    if (0xb < *(int *)(param_1 + 0x14)) {
      FUN_00423510();
      iVar13 = *(int *)(param_1 + 0x24);
      *(undefined4 *)(param_1 + 4) = 0x15;
      if (iVar13 == 0) {
        DAT_00491fb8 = (-(uint)(*(int *)(param_1 + 0x1e4) != 0) & 0xfffffffd) + 0xd;
      }
      else if ((iVar13 == 1) || (iVar13 == 2)) {
        FUN_0040ac90(4);
        return;
      }
    }
    break;
  default:
    goto switchD_00423715_default;
  }
switchD_00423715_default:
  return;
}

