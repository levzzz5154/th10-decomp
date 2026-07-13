/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x0042D420
 * Tracking name: FUN_0042d420
 * Ghidra name: FUN_0042d420
 * Tracked span: 1280 bytes
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __fastcall FUN_0042d420(undefined4 param_1)

{
  int *piVar1;
  uint *puVar2;
  int iVar3;
  undefined4 extraout_ECX;
  undefined4 extraout_ECX_00;
  int unaff_EBX;
  
  switch(*(undefined4 *)(unaff_EBX + 0x20)) {
  case 0:
    *(undefined4 *)(unaff_EBX + 0x2c) = 8;
    iVar3 = FUN_0042c850();
    if (iVar3 == 0) {
      *(undefined4 *)(unaff_EBX + 0xb4 + *(int *)(unaff_EBX + 0xf8) * 4) = 1;
      *(int *)(unaff_EBX + 0xf8) = *(int *)(unaff_EBX + 0xf8) + 1;
    }
    if ((DAT_00474ca0 & 0x10) != 0) {
      iVar3 = *(int *)(unaff_EBX + 0x2c);
      if (iVar3 == 0) {
        *(undefined4 *)(unaff_EBX + 0x24) = 2;
      }
      else if (iVar3 < 3) {
        *(int *)(unaff_EBX + 0x24) = iVar3 + -1;
      }
      else {
        *(undefined4 *)(unaff_EBX + 0x24) = 2;
      }
      DAT_00474ca0 = DAT_00474ca0 & 0xffffffef;
    }
    iVar3 = FUN_004491c0(*(undefined4 *)(unaff_EBX + 0x424),(int)g_pGameStateManager,
                         *(undefined4 *)(unaff_EBX + 0x424));
    if (iVar3 == 0) {
      FUN_0042c670(unaff_EBX);
    }
    FUN_0042c670(unaff_EBX);
    FUN_0042c620(1);
  case 1:
    if (10 < *(int *)(unaff_EBX + 0x2b4)) {
      FUN_0042c620(2);
      FUN_00449250(extraout_ECX,(int)g_pGameStateManager,*(int *)(unaff_EBX + 0x2c4));
      FUN_0042c770(0);
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
      FUN_00449250(extraout_ECX_00,(int)g_pGameStateManager,*(int *)(unaff_EBX + 0x2c4));
      FUN_0042c770(0);
    }
    if ((_DAT_00474e36 & 10) != 0) {
      if (*piVar1 == 7) goto switchD_0042d629_caseD_7;
      FUN_0043dc90(&DAT_00492590,0);
      iVar3 = *(int *)(unaff_EBX + 0x2c);
      if (iVar3 == 0) {
        *piVar1 = 7;
      }
      else if (iVar3 < 8) {
        *piVar1 = iVar3 + -1;
      }
      else {
        *piVar1 = 7;
      }
      FUN_0042c750(0);
      FUN_0042c770(0);
    }
    if ((_DAT_00474e36 & 0x1001) != 0) {
      FUN_0042c770(0);
      switch(*piVar1) {
      case 0:
      case 1:
      case 2:
      case 3:
      case 4:
        FUN_0043dc90(&DAT_00492590,0);
        FUN_0042c770(0x5a);
        FUN_0042c770(0x5b);
        FUN_0042c620(4);
        return 1;
      case 5:
        FUN_0043dc90(&DAT_00492590,0);
        FUN_0042c770(0x5a);
        FUN_0042c770(0x5b);
        FUN_0042c620(4);
        FUN_0043dc90(&DAT_00492590,0);
        return 1;
      case 6:
        FUN_0043dc90(&DAT_00492590,0);
        FUN_0042c620(4);
        FUN_0042c750(0x5a);
        FUN_0042c750(0x5b);
        return 1;
      case 7:
switchD_0042d629_caseD_7:
        FUN_0043dc90(&DAT_00492590,0);
        FUN_0042c620(4);
        return 1;
      }
    }
    break;
  case 3:
    break;
  case 4:
    if (*(int *)(unaff_EBX + 0x2b4) < 0x14) break;
    puVar2 = (uint *)(unaff_EBX + 0x24);
    switch(*(undefined4 *)(unaff_EBX + 0x24)) {
    case 0:
      DAT_00474ca0 = DAT_00474ca0 & 0xffffffef;
      goto LAB_0042d7d7;
    case 1:
      DAT_00474ca0 = DAT_00474ca0 & 0xffffffef;
      FUN_0042c6d0(param_1);
      FUN_0042c5c0(6);
      FUN_0044be20();
      *(uint *)(unaff_EBX + 0x58f0) = DAT_00474c74;
      DAT_00474c74 = 4;
      iVar3 = *(int *)(unaff_EBX + 0x2c);
      if (iVar3 == 0) {
        *puVar2 = 0;
        return 1;
      }
      if (0 < iVar3) {
        *puVar2 = 0;
        return 1;
      }
      *puVar2 = iVar3 - 1;
      return 1;
    case 2:
      DAT_00474ca0 = DAT_00474ca0 | 0x10;
LAB_0042d7d7:
      FUN_0042c6d0(DAT_00474ca0);
      FUN_0042c5c0(6);
      FUN_0044be20();
      if (3 < (int)DAT_00474c74) {
        DAT_00474c74 = 1;
      }
      FUN_0040ad20(DAT_00474c74,puVar2);
      return 1;
    case 3:
      FUN_0042c6d0(param_1);
      FUN_0042c5c0(0xc);
      FUN_0044be20();
      return 1;
    case 4:
      FUN_0042c6d0(param_1);
      FUN_0042c5c0(0xb);
      FUN_0044be20();
      return 1;
    case 5:
      FUN_0042c6d0(param_1);
      FUN_0042c5c0(0xe);
      FUN_0044be20();
      return 1;
    case 6:
      FUN_0042c5c0(4);
      FUN_0044be20();
      return 1;
    case 7:
      FUN_0042c5c0(3);
    }
    break;
  default:
    goto switchD_0042d42f_default;
  }
switchD_0042d42f_default:
  return 1;
}

