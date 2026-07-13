/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x00430320
 * Tracking name: FUN_00430320
 * Ghidra name: FUN_00430320
 * Tracked span: 896 bytes
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __thiscall FUN_00430320(void *this,int param_1)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  int iVar4;
  int *piVar5;
  uint *puVar6;
  undefined4 extraout_ECX;
  undefined4 extraout_ECX_00;
  undefined4 extraout_ECX_01;
  undefined4 extraout_ECX_02;
  undefined4 extraout_ECX_03;
  undefined4 extraout_ECX_04;
  undefined4 extraout_ECX_05;
  undefined4 extraout_ECX_06;
  int iVar7;
  
  iVar4 = DAT_00474c74;
  iVar7 = (3 < DAT_00474c74) + 0x77;
  switch(*(undefined4 *)(param_1 + 0x20)) {
  case 0:
    iVar1 = FUN_004491c0(this,(int)g_pGameStateManager,*(int *)(param_1 + 0x43c));
    uVar3 = extraout_ECX;
    if (iVar1 == 0) {
      FUN_0042c670(param_1);
      puVar2 = (undefined4 *)FUN_00448d00(*(undefined4 *)((int)g_pGameThread + 0x8994),8,0xf);
      *(undefined4 *)(param_1 + 0x5d0) = *puVar2;
      uVar3 = extraout_ECX_00;
      iVar4 = DAT_00474c74;
    }
    *(uint *)(param_1 + 0x2c) = ((3 < iVar4) - 1 & 3) + 1;
    FUN_0042c6d0(uVar3);
    FUN_0042c670(param_1);
    uVar3 = *(undefined4 *)(param_1 + 0x2c4 + iVar7 * 4);
    FUN_00449250(uVar3,(int)g_pGameStateManager,uVar3);
    FUN_0042c770(iVar7);
    FUN_0042c670(param_1);
    FUN_0042c620(1);
  case 1:
    if (6 < *(int *)(param_1 + 0x2b4)) {
      FUN_0042c620(2);
      return 1;
    }
    break;
  case 2:
    if (DAT_00474c74 < 4) {
      *(undefined4 *)(param_1 + 0x28) = *(undefined4 *)(param_1 + 0x24);
      uVar3 = FUN_0040ace0(0x474e30);
      if ((short)uVar3 != 0) {
        FUN_0044bea0(-1);
      }
      uVar3 = FUN_0040ace0(0x474e30);
      if ((short)uVar3 != 0) {
        FUN_0044bea0(1);
      }
      if (*(int *)(param_1 + 0x28) != *(int *)(param_1 + 0x24)) {
        FUN_0043dc90(&DAT_00492590,0);
        FUN_0042c750(iVar7);
        FUN_0042c770(iVar7);
      }
    }
    if ((_DAT_00474e36 & 10) != 0) {
      FUN_0042c620(4);
      FUN_0043dc90(&DAT_00492590,0);
      FUN_0042c6d0(extraout_ECX_01);
      return 1;
    }
    if ((_DAT_00474e36 & 0x1001) != 0) {
      FUN_0042c770(iVar7);
      if (DAT_00474c74 < 4) {
        FUN_004497d0(iVar7);
        uVar3 = extraout_ECX_03;
      }
      else {
        iVar4 = FUN_004491c0(extraout_ECX_02,(int)g_pGameStateManager,
                             *(int *)(param_1 + 0x2c4 + iVar7 * 4));
        if (iVar4 == 0) {
          *(undefined4 *)(param_1 + 0x2c4 + iVar7 * 4) = 0;
        }
        piVar5 = (int *)(iVar4 + 0x10);
        uVar3 = extraout_ECX_04;
        if (piVar5 != (int *)0x0) {
          uVar3 = 0x71;
          do {
            if (*(short *)(*piVar5 + 0x38a) == 0x71) {
              uVar3 = *(undefined4 *)*piVar5;
              break;
            }
            piVar5 = (int *)piVar5[1];
          } while (piVar5 != (int *)0x0);
        }
      }
      FUN_00449470(uVar3);
      FUN_0042c620(3);
      FUN_0043dc90(&DAT_00492590,0);
      return 1;
    }
    break;
  case 3:
    if (0xd < *(int *)(param_1 + 0x2b4)) {
      FUN_0042c6d0(this);
      FUN_0042c5c0(7);
      if (DAT_00474c74 < 4) {
        DAT_00474c74 = *(int *)(param_1 + 0x24);
      }
      puVar6 = (uint *)FUN_0044be20();
      *(undefined4 *)(param_1 + 0x2c) = 2;
      FUN_0040ad20(DAT_00474c68,puVar6);
      return 1;
    }
    break;
  case 4:
    if (5 < *(int *)(param_1 + 0x2b4)) {
      FUN_0042c6d0(this);
      FUN_0042c770(0x5a);
      FUN_0042c770(0x5b);
      FUN_0042c6d0(extraout_ECX_05);
      FUN_00409e50(extraout_ECX_06);
      FUN_0042c5c0(2);
      if (DAT_00474c74 < 4) {
        DAT_00474c74 = *(int *)(param_1 + 0x24);
      }
      else {
        DAT_00474c74 = *(int *)(param_1 + 0x58f0);
      }
      FUN_0044be70();
    }
  }
  return 1;
}

