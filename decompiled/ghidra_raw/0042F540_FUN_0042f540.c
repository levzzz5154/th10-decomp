/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x0042F540
 * Tracking name: FUN_0042f540
 * Ghidra name: FUN_0042f540
 * Tracked span: 880 bytes
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_0042f540(void)

{
  int *piVar1;
  undefined4 *puVar2;
  undefined2 extraout_var;
  undefined4 uVar3;
  undefined4 extraout_ECX;
  undefined4 extraout_ECX_00;
  int extraout_ECX_01;
  int extraout_ECX_02;
  int iVar4;
  undefined2 uVar5;
  int iVar6;
  int unaff_EBX;
  
  switch(*(undefined4 *)(unaff_EBX + 0x20)) {
  case 0:
    *(undefined4 *)(unaff_EBX + 0x2c) = 7;
    iVar6 = *(int *)(unaff_EBX + 0x2c);
    if (iVar6 == 0) {
      *(undefined4 *)(unaff_EBX + 0x24) = 0;
    }
    else if (iVar6 < 1) {
      *(int *)(unaff_EBX + 0x24) = iVar6 + -1;
    }
    else {
      *(undefined4 *)(unaff_EBX + 0x24) = 0;
    }
    FUN_0042c670(unaff_EBX);
    FUN_0042c620(1);
    *(undefined2 *)(unaff_EBX + 0x59cc) = DAT_00474e88;
    *(undefined2 *)(unaff_EBX + 0x59ce) = DAT_00474e8a;
    *(undefined2 *)(unaff_EBX + 0x59d0) = DAT_00474e8c;
    *(undefined2 *)(unaff_EBX + 0x59d2) = DAT_00474e8e;
    uVar3 = CONCAT22(extraout_var,DAT_00474e98);
    *(undefined2 *)(unaff_EBX + 0x59d4) = DAT_00474e98;
    FUN_0042f8b0(uVar3);
  case 1:
    if (6 < *(int *)(unaff_EBX + 0x2b4)) {
      FUN_0042c620(2);
      FUN_00449250(extraout_ECX,(int)g_pGameStateManager,*(int *)(unaff_EBX + 0x2cc));
      FUN_0042c770(2);
      return 1;
    }
    break;
  case 2:
    piVar1 = (int *)(unaff_EBX + 0x24);
    *(undefined4 *)(unaff_EBX + 0x28) = *(undefined4 *)(unaff_EBX + 0x24);
    if (((_DAT_00474e36 & 0x10) != 0) || ((DAT_00474e34 & 0x10) != 0)) {
      FUN_0044bea0(-1);
    }
    if (((_DAT_00474e36 & 0x20) != 0) || ((DAT_00474e34 & 0x20) != 0)) {
      FUN_0044bea0(1);
    }
    if (*(int *)(unaff_EBX + 0x28) != *piVar1) {
      FUN_0043dc90(&DAT_00492590,0);
      FUN_00449250(extraout_ECX_00,(int)g_pGameStateManager,*(int *)(unaff_EBX + 0x2cc));
      FUN_0042c770(2);
    }
    puVar2 = FUN_0044a4e0(0);
    iVar6 = 0;
    do {
      if (*(char *)(iVar6 + (int)puVar2) < '\0') {
        iVar4 = *piVar1;
        if (iVar4 < 5) {
          FUN_00430250(iVar4,iVar6);
          iVar4 = extraout_ECX_02;
        }
        break;
      }
      iVar6 = iVar6 + 1;
      iVar4 = extraout_ECX_01;
    } while (iVar6 < 0x1f);
    uVar5 = (undefined2)((uint)iVar4 >> 0x10);
    if (((_DAT_00474e36 & 10) != 0) && (*piVar1 == 6)) {
      *(undefined2 *)(unaff_EBX + 0x59cc) = DAT_00474e88;
      *(undefined2 *)(unaff_EBX + 0x59ce) = DAT_00474e8a;
      *(undefined2 *)(unaff_EBX + 0x59d0) = DAT_00474e8c;
      *(undefined2 *)(unaff_EBX + 0x59d2) = DAT_00474e8e;
      uVar3 = CONCAT22(uVar5,DAT_00474e98);
      *(undefined2 *)(unaff_EBX + 0x59d4) = DAT_00474e98;
      FUN_0042f8b0(uVar3);
LAB_0042f7d9:
      FUN_0043dc90(&DAT_00492590,0);
      FUN_0042c770(2);
      FUN_0042c620(4);
      return 1;
    }
    if ((_DAT_00474e36 & 0x1001) != 0) {
      if (*piVar1 == 5) {
        *(undefined2 *)(unaff_EBX + 0x59cc) = DAT_00474e88;
        *(undefined2 *)(unaff_EBX + 0x59ce) = DAT_00474e8a;
        *(undefined2 *)(unaff_EBX + 0x59d0) = DAT_00474e8c;
        *(undefined2 *)(unaff_EBX + 0x59d2) = DAT_00474e8e;
        uVar3 = CONCAT22(uVar5,DAT_00474e98);
        *(undefined2 *)(unaff_EBX + 0x59d4) = DAT_00474e98;
        FUN_0042f8b0(uVar3);
        FUN_0043dc90(&DAT_00492590,0);
        return 1;
      }
      if (*piVar1 == 6) {
        _DAT_00474e88 = *(undefined4 *)(unaff_EBX + 0x59cc);
        _DAT_00474e8c = *(undefined4 *)(unaff_EBX + 0x59d0);
        DAT_00474e98 = *(undefined2 *)(unaff_EBX + 0x59d4);
        DAT_00491d54 = DAT_00474e90;
        DAT_00491d58 = DAT_00474e94;
        DAT_00491d4c = _DAT_00474e88;
        DAT_00491d50 = _DAT_00474e8c;
        DAT_00491d5c = DAT_00474e98;
        goto LAB_0042f7d9;
      }
    }
    break;
  case 3:
    break;
  case 4:
    if (9 < *(int *)(unaff_EBX + 0x2b4)) {
      FUN_0042c5c0(4);
      FUN_0044be70();
    }
    break;
  default:
    goto switchD_0042f54f_default;
  }
switchD_0042f54f_default:
  return 1;
}

