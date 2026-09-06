/* Raw Ghidra reference; not compilable reconstruction. Address: 004306A0 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __thiscall FUN_004306a0(void *this,int param_1)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  uint *puVar4;
  undefined4 extraout_ECX;
  undefined4 extraout_ECX_00;
  undefined3 uVar6;
  undefined3 extraout_var;
  undefined4 uVar5;
  undefined4 extraout_ECX_01;
  undefined4 extraout_ECX_02;
  undefined4 extraout_ECX_03;
  undefined4 extraout_ECX_04;
  undefined4 extraout_ECX_05;
  undefined4 extraout_ECX_06;
  undefined4 extraout_ECX_07;
  undefined4 extraout_ECX_08;
  undefined4 extraout_ECX_09;
  
  switch(*(undefined4 *)(param_1 + 0x20)) {
  case 0:
    *(undefined4 *)(param_1 + 0x2c) = 2;
    iVar2 = DAT_0047783c;
    if (DAT_00474c74 == 4) {
      if (((*(char *)(DAT_0047783c + 0x1d888) == '\0') &&
          (*(char *)(DAT_0047783c + 0x1d889) == '\0')) &&
         (*(char *)(DAT_0047783c + 0x1d88a) == '\0')) {
        if (*(int *)(param_1 + 0x24) == 0) {
          iVar1 = *(int *)(param_1 + 0x2c);
          if (iVar1 == 0) {
            *(undefined4 *)(param_1 + 0x24) = 1;
          }
          else if (iVar1 < 2) {
            *(int *)(param_1 + 0x24) = iVar1 + -1;
          }
          else {
            *(undefined4 *)(param_1 + 0x24) = 1;
          }
        }
        *(undefined4 *)(param_1 + 0xb4 + *(int *)(param_1 + 0xf8) * 4) = 0;
        *(int *)(param_1 + 0xf8) = *(int *)(param_1 + 0xf8) + 1;
      }
      if (((*(char *)(iVar2 + 0x1d88b) == '\0') && (*(char *)(iVar2 + 0x1d88c) == '\0')) &&
         (*(char *)(iVar2 + 0x1d88d) == '\0')) {
        if (*(int *)(param_1 + 0x24) == 1) {
          iVar2 = *(int *)(param_1 + 0x2c);
          if (iVar2 == 0) {
            *(undefined4 *)(param_1 + 0x24) = 0;
          }
          else if (iVar2 < 1) {
            *(int *)(param_1 + 0x24) = iVar2 + -1;
          }
          else {
            *(undefined4 *)(param_1 + 0x24) = 0;
          }
        }
        *(undefined4 *)(param_1 + 0xb4 + *(int *)(param_1 + 0xf8) * 4) = 1;
        *(int *)(param_1 + 0xf8) = *(int *)(param_1 + 0xf8) + 1;
      }
    }
    FUN_0042c670(param_1);
    FUN_0042c6d0(extraout_ECX);
    FUN_0042c670(param_1);
    FUN_00449250(extraout_ECX_00,(int)g_pGameStateManager,*(int *)(param_1 + 0x4b8));
    FUN_0042c770(0x7d);
    FUN_0042c620(1);
  case 1:
    if (6 < *(int *)(param_1 + 0x2b4)) {
      FUN_0042c620(2);
      return 1;
    }
    break;
  case 2:
    *(undefined4 *)(param_1 + 0x28) = *(undefined4 *)(param_1 + 0x24);
    uVar6 = (undefined3)((uint)*(undefined4 *)(param_1 + 0x24) >> 8);
    if (((_DAT_00474e36 & 0x40) != 0) || ((DAT_00474e34 & 0x40) != 0)) {
      FUN_0044bea0(-1);
      uVar6 = extraout_var;
    }
    uVar5 = CONCAT31(uVar6,DAT_00474e36);
    if (((_DAT_00474e36 & 0x80) != 0) || ((DAT_00474e34 & 0x80) != 0)) {
      FUN_0044bea0(1);
      uVar5 = extraout_ECX_01;
    }
    if (*(int *)(param_1 + 0x28) != *(int *)(param_1 + 0x24)) {
      FUN_0043dc90(&DAT_00492590,0);
      FUN_0042c750(0x7d);
      FUN_0042c770(0x7d);
      uVar5 = extraout_ECX_02;
    }
    if ((_DAT_00474e36 & 10) != 0) {
      FUN_0042c620(4);
      FUN_0043dc90(&DAT_00492590,0);
      return 1;
    }
    if ((_DAT_00474e36 & 0x1001) != 0) {
      FUN_004497d0(uVar5);
      FUN_00449470(extraout_ECX_03);
      FUN_004497d0(extraout_ECX_04);
      FUN_00449470(extraout_ECX_05);
      FUN_004497d0(extraout_ECX_06);
      FUN_00449470(extraout_ECX_07);
      FUN_004497d0(*(undefined4 *)(param_1 + 0x24));
      FUN_00449470(extraout_ECX_08);
      FUN_0043dc90(&DAT_00492590,0);
      FUN_0042c620(3);
      return 1;
    }
    break;
  case 3:
    if (0xd < *(int *)(param_1 + 0x2b4)) {
      FUN_0042c6d0(this);
      FUN_0042c5c0(8);
      iVar1 = DAT_00474c68;
      iVar2 = *(int *)(param_1 + 0x24);
      DAT_00474c68 = iVar2;
      puVar4 = (uint *)FUN_0044be20();
      *(undefined4 *)(param_1 + 0x2c) = 3;
      if (iVar1 == iVar2) {
        FUN_0040ad20(DAT_00474c6c,puVar4);
        return 1;
      }
      uVar3 = puVar4[2];
      if (uVar3 == 0) {
        *puVar4 = 0;
        return 1;
      }
      if (0 < (int)uVar3) {
        *puVar4 = 0;
        return 1;
      }
      *puVar4 = uVar3 - 1;
      return 1;
    }
    break;
  case 4:
    if (5 < *(int *)(param_1 + 0x2b4)) {
      FUN_0042c6d0(this);
      FUN_0042c6d0(extraout_ECX_09);
      FUN_0042c5c0(6);
      DAT_00474c68 = *(int *)(param_1 + 0x24);
      FUN_0044be70();
    }
  }
  return 1;
}

