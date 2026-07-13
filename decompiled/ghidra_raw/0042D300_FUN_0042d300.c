/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x0042D300
 * Tracking name: FUN_0042d300
 * Ghidra name: FUN_0042d300
 * Tracked span: 288 bytes
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __fastcall FUN_0042d300(undefined4 param_1)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 extraout_ECX;
  int unaff_EBX;
  
  switch(*(undefined4 *)(unaff_EBX + 0x20)) {
  case 0:
    iVar1 = FUN_004491c0(param_1,(int)g_pGameStateManager,*(int *)(unaff_EBX + 0x424));
    if (iVar1 == 0) {
      FUN_0042c670(unaff_EBX);
      FUN_0042c670(unaff_EBX);
      puVar2 = (undefined4 *)FUN_00448d00(*(undefined4 *)(unaff_EBX + 0x18),0,0xf);
      *(undefined4 *)(unaff_EBX + 0x684) = *puVar2;
    }
    FUN_0042c620(1);
    iVar1 = *(int *)(unaff_EBX + 0x2c);
    if (iVar1 == 0) {
      *(undefined4 *)(unaff_EBX + 0x24) = 0;
    }
    else if (iVar1 < 1) {
      *(int *)(unaff_EBX + 0x24) = iVar1 + -1;
    }
    else {
      *(undefined4 *)(unaff_EBX + 0x24) = 0;
    }
  case 1:
    if (10 < *(int *)(unaff_EBX + 0x2b4)) {
      FUN_0042c620(2);
      return 1;
    }
    break;
  case 2:
    if ((_DAT_00474e36 & 0x160b) != 0) {
      FUN_0042c770(0x5a);
      FUN_0042c620(4);
      FUN_0043dc90(&DAT_00492590,0);
      FUN_00409e50(extraout_ECX);
      return 1;
    }
    break;
  case 3:
    break;
  case 4:
    if (0x1d < *(int *)(unaff_EBX + 0x2b4)) {
      FUN_0042c5c0(2);
    }
    break;
  default:
    goto switchD_0042d30e_default;
  }
switchD_0042d30e_default:
  return 1;
}

