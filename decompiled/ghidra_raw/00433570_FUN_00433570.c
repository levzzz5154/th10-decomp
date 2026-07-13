/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x00433570
 * Tracking name: FUN_00433570
 * Ghidra name: FUN_00433570
 * Tracked span: 1472 bytes
 */


/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __thiscall FUN_00433570(void *this,int param_1)

{
  undefined *puVar1;
  int *piVar2;
  uint *puVar3;
  char cVar4;
  void *pvVar5;
  undefined4 *puVar6;
  char *pcVar7;
  undefined4 *puVar8;
  undefined4 extraout_ECX;
  undefined4 extraout_ECX_00;
  void *this_00;
  int iVar9;
  char *pcVar10;
  int iVar11;
  bool bVar12;
  char local_44 [64];
  uint local_4;
  
  local_4 = DAT_00473660 ^ (uint)local_44;
  switch(*(undefined4 *)(param_1 + 0x20)) {
  case 0:
    *(undefined4 *)(param_1 + 0x2c) = 0x19;
    *(undefined4 *)(param_1 + 0xf4) = 1;
    iVar11 = *(int *)(param_1 + 0x2c);
    if (iVar11 == 0) {
      *(undefined4 *)(param_1 + 0x24) = 0;
    }
    else if (iVar11 < 1) {
      *(int *)(param_1 + 0x24) = iVar11 + -1;
    }
    else {
      *(undefined4 *)(param_1 + 0x24) = 0;
    }
    DAT_00477848 = &PTR_DAT_00474908;
    DAT_00474c7c = 8;
    DAT_00474c80 = 8;
    iVar11 = 1;
    puVar8 = (undefined4 *)(param_1 + 0x59e4);
    do {
      _sprintf(local_44,"th10_%.2d.rpy",iVar11);
      puVar6 = FUN_004296f0(local_44);
      *puVar8 = puVar6;
      iVar11 = iVar11 + 1;
      puVar8 = puVar8 + 1;
    } while (iVar11 < 0x1a);
    FUN_0042c670(param_1);
    FUN_0042c620(1);
  case 1:
    if (6 < *(int *)(param_1 + 0x2b4)) {
LAB_0043363c:
      FUN_0042c620(2);
    }
    break;
  case 2:
    *(undefined4 *)(param_1 + 0x28) = *(undefined4 *)(param_1 + 0x24);
    if (((_DAT_00474e36 & 0x10) != 0) || ((DAT_00474e34 & 0x10) != 0)) {
      FUN_0044bea0(-1);
    }
    if (((_DAT_00474e36 & 0x20) != 0) || ((DAT_00474e34 & 0x20) != 0)) {
      FUN_0044bea0(1);
    }
    if (*(int *)(param_1 + 0x28) != *(int *)(param_1 + 0x24)) {
      FUN_0043dc90(&DAT_00492590,0);
    }
    if ((_DAT_00474e36 & 10) == 0) {
      if ((_DAT_00474e36 & 0x1001) != 0) {
        piVar2 = (int *)(param_1 + 0x58f4);
        *(int *)(param_1 + 0x59dc) = *(int *)(param_1 + 0x24);
        iVar11 = *(int *)(param_1 + 0x58fc);
        if (iVar11 == 0) {
          *piVar2 = 0;
        }
        else if (iVar11 < 1) {
          *piVar2 = iVar11 + -1;
        }
        else {
          *piVar2 = 0;
        }
        pvVar5 = DAT_00477838;
        pcVar7 = PTR_s_ABCDEFGHIJKLMNOPQRSTUVWXYZabcdef_004746d8;
        do {
          cVar4 = *pcVar7;
          pcVar7 = pcVar7 + 1;
        } while (cVar4 != '\0');
        *(int *)(param_1 + 0x58fc) =
             (int)pcVar7 - (int)(PTR_s_ABCDEFGHIJKLMNOPQRSTUVWXYZabcdef_004746d8 + 1);
        *(undefined4 *)(param_1 + 0x59c4) = 1;
        FID_conflict___time32((__time32_t *)(*(int *)((int)pvVar5 + 0x18) + 0xc));
        *(undefined4 *)(*(int *)((int)pvVar5 + 0x18) + 0x5c) = 8;
        pcVar7 = (char *)(DAT_0047783c + 0x1d878);
        iVar11 = (param_1 + 0x58dc) - (int)pcVar7;
        do {
          cVar4 = *pcVar7;
          pcVar7[iVar11] = cVar4;
          pcVar7 = pcVar7 + 1;
        } while (cVar4 != '\0');
        iVar11 = 9;
        bVar12 = true;
        *(undefined4 *)(param_1 + 0x58e8) = 0;
        pcVar7 = (char *)(param_1 + 0x58dc);
        pcVar10 = "        ";
        do {
          if (iVar11 == 0) break;
          iVar11 = iVar11 + -1;
          bVar12 = *pcVar7 == *pcVar10;
          pcVar7 = pcVar7 + 1;
          pcVar10 = pcVar10 + 1;
        } while (bVar12);
        if (!bVar12) {
          FUN_0044bea0(-1);
        }
        iVar11 = 8;
        do {
          if (*(char *)(iVar11 + 0x58db + param_1) != ' ') break;
          iVar11 = iVar11 + -1;
        } while (0 < iVar11);
        *(int *)(param_1 + 0x58e8) = iVar11;
        FUN_0043dc90(&DAT_00492590,0);
        FUN_0042c620(3);
      }
    }
    else {
      FUN_0042c620(4);
      FUN_0043dc90(&DAT_00492590,0);
    }
    break;
  case 3:
    puVar3 = (uint *)(param_1 + 0x58f4);
    *(undefined4 *)(param_1 + 0x58f8) = *(undefined4 *)(param_1 + 0x58f4);
    if (((_DAT_00474e36 & 0x10) != 0) || ((DAT_00474e34 & 0x10) != 0)) {
      FUN_0044bea0(-0xd);
    }
    if (((_DAT_00474e36 & 0x20) != 0) || ((DAT_00474e34 & 0x20) != 0)) {
      FUN_0044bea0(0xd);
    }
    if (((_DAT_00474e36 & 0x40) != 0) || ((DAT_00474e34 & 0x40) != 0)) {
      if ((int)*puVar3 % 0xd == 0) {
        iVar11 = 0xc;
      }
      else {
        iVar11 = -1;
      }
      FUN_0044bea0(iVar11);
    }
    if (((_DAT_00474e36 & 0x80) != 0) || ((DAT_00474e34 & 0x80) != 0)) {
      if ((int)*puVar3 % 0xd == 0xc) {
        iVar11 = -0xc;
      }
      else {
        iVar11 = 1;
      }
      FUN_0044bea0(iVar11);
    }
    if (*(uint *)(param_1 + 0x58f8) != *puVar3) {
      FUN_0043dc90(&DAT_00492590,0);
    }
    if ((_DAT_00474e36 & 0x1001) != 0) {
      puVar1 = PTR_s_ABCDEFGHIJKLMNOPQRSTUVWXYZabcdef_004746d8 + 1;
      pcVar7 = PTR_s_ABCDEFGHIJKLMNOPQRSTUVWXYZabcdef_004746d8;
      do {
        cVar4 = *pcVar7;
        pcVar7 = pcVar7 + 1;
      } while (cVar4 != '\0');
      pcVar10 = (char *)*puVar3;
      if ((int)pcVar10 < (int)(pcVar7 + (-3 - (int)puVar1))) {
        iVar11 = *(int *)(param_1 + 0x58e8);
        if (iVar11 < 8) {
          *(undefined *)(iVar11 + 0x58dc + param_1) =
               PTR_s_ABCDEFGHIJKLMNOPQRSTUVWXYZabcdef_004746d8[(int)pcVar10];
LAB_004338ef:
          iVar11 = *(int *)(param_1 + 0x58e8) + 1;
          *(int *)(param_1 + 0x58e8) = iVar11;
          if (7 < iVar11) {
            FUN_0040ad20((uint)(pcVar7 + (-1 - (int)puVar1)),puVar3);
          }
        }
        else {
          *(undefined *)(iVar11 + 0x58db + param_1) =
               PTR_s_ABCDEFGHIJKLMNOPQRSTUVWXYZabcdef_004746d8[(int)pcVar10];
        }
      }
      else if (pcVar10 == pcVar7 + (-3 - (int)puVar1)) {
        iVar11 = *(int *)(param_1 + 0x58e8);
        if (iVar11 < 8) {
          *(undefined1 *)(iVar11 + 0x58dc + param_1) = 0x20;
          goto LAB_004338ef;
        }
        *(undefined1 *)(iVar11 + 0x58db + param_1) = 0x20;
      }
      else if (pcVar10 == pcVar7 + (-2 - (int)puVar1)) {
        iVar11 = *(int *)(param_1 + 0x58e8);
        if (iVar11 == 0) {
          return 1;
        }
        *(int *)(param_1 + 0x58e8) = iVar11 + -1;
        *(undefined1 *)(iVar11 + 0x58db + param_1) = 0x20;
      }
      else if (pcVar10 == pcVar7 + (-1 - (int)puVar1)) {
        FUN_0043dc90(&DAT_00492590,0);
        _sprintf(local_44,"th10_%.2d.rpy",*(int *)(param_1 + 0x24) + 1);
        FUN_004297b0();
        pcVar7 = (char *)(param_1 + 0x58dc);
        FUN_00429b60((int)DAT_00477838,local_44,pcVar7);
        iVar11 = *(int *)(param_1 + 0x24);
        puVar8 = FUN_004296f0(local_44);
        iVar9 = DAT_0047783c + 0x1d878;
        *(undefined4 **)(param_1 + 0x59e4 + iVar11 * 4) = puVar8;
        iVar9 = iVar9 - (int)pcVar7;
        do {
          cVar4 = *pcVar7;
          pcVar7[iVar9] = cVar4;
          pcVar7 = pcVar7 + 1;
        } while (cVar4 != '\0');
        FUN_0042c620(2);
      }
      FUN_0043dc90(&DAT_00492590,0);
    }
    if ((_DAT_00474e36 & 10) == 0) {
      return 1;
    }
    if (*(int *)(param_1 + 0x58e8) != 0) {
      FUN_0043dc90(&DAT_00492590,0);
      iVar11 = *(int *)(param_1 + 0x58e8);
      *(int *)(param_1 + 0x58e8) = iVar11 + -1;
      *(undefined1 *)(iVar11 + 0x58db + param_1) = 0x20;
      return 1;
    }
    goto LAB_0043363c;
  case 4:
    if (5 < *(int *)(param_1 + 0x2b4)) {
      FUN_0042c6d0(this);
      FUN_0042c770(0x5a);
      FUN_0042c770(0x5b);
      FUN_0042c6d0(extraout_ECX);
      FUN_00409e50(extraout_ECX_00);
      FUN_0042c5c0(2);
      FUN_0044be70();
      pvVar5 = DAT_00477838;
      if (DAT_00477838 != (void *)0x0) {
        FUN_004294a0((int)DAT_00477838);
        _free(pvVar5);
      }
      FUN_00420a90(0,"bgm/th10_02.wav");
      FUN_00420b10(this_00,0,0);
      iVar11 = 0x19;
      puVar8 = (undefined4 *)(param_1 + 0x59e4);
      do {
        pvVar5 = (void *)*puVar8;
        if (pvVar5 != (void *)0x0) {
          FUN_004294a0((int)pvVar5);
          _free(pvVar5);
        }
        puVar8 = puVar8 + 1;
        iVar11 = iVar11 + -1;
      } while (iVar11 != 0);
      puVar8 = (undefined4 *)(param_1 + 0x59e4);
      for (iVar11 = 0x32; iVar11 != 0; iVar11 = iVar11 + -1) {
        *puVar8 = 0;
        puVar8 = puVar8 + 1;
      }
    }
  }
  return 1;
}

